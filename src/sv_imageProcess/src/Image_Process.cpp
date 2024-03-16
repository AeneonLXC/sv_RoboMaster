#include "Image_Process.hpp"
#include "Serial_UL.hpp"

Serial_UL serUL_Image;

cv::Ptr<cv::ml::SVM> svm = cv::ml::StatModel::load<cv::ml::SVM>("svm_data_red.yml");
// 创建HSV图像容器
cv::Mat Image_Process::Image_HsvImage(cv::Mat frame, cv::Mat hsvImage){
        // 将BGR图像转换为HSV图像
    cv::cvtColor(frame, hsvImage, cv::COLOR_BGR2HSV);
    
    int lowerRed[] = {0, 0, 200}; // HSV中低于此值的颜色会被认为是红色
    int upperRed[] = {216, 73, 255}; // HSV中高于此值的颜色也会被认为是红色
    
    // 创建颜色范围数组
    cv::Scalar lowerBound(lowerRed[0], lowerRed[1], lowerRed[2]);
    cv::Scalar upperBound(upperRed[0], upperRed[1], upperRed[2]);
    
    // 创建二值化图像容器
    cv::Mat binaryImage;
    
    // 应用阈值操作，将符合条件的区域设置为白色，其他部分设置为黑色
    cv::inRange(hsvImage, lowerBound, upperBound, binaryImage);
    return binaryImage;
}

// 查找轮廓
std::vector<std::vector<cv::Point>> Image_Process::Image_FindContours(cv::Mat binaryImage){
    std::vector<std::vector<cv::Point>> contours;  
    std::vector<cv::Vec4i> hierarchy;  
      
    cv::findContours(binaryImage, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);  
    return contours;  

}

std::vector<std::vector<cv::Point>> Image_Process::Image_GetContours(std::vector<std::vector<cv::Point>> contours, Image_Process image_G) {  

    std::vector<cv::Point> boxPoints;  
    std::vector<std::vector<cv::Point>> allArmours; // 存储所有armour_list的集合  
    // 遍历轮廓并绘制边界框  
    for (const auto& contour : contours) {  
        cv::Rect boundingBox = cv::boundingRect(contour);  
        cv::RotatedRect rect = cv::minAreaRect(contour);  
        boxPoints = image_G.Image_GetBoundingBoxPoints(boundingBox, rect);
        //cv::rectangle(frame, boundingBox, (0, 1, 0), 2); 
        image_G.rect_center_point.x = boxPoints[4].x;
        image_G.rect_center_point.y = boxPoints[4].y;
        image_G.rect_wh.x = boundingBox.width;
        image_G.rect_wh.y = boundingBox.height;
        image_G.rect_area_angle.x = boxPoints[5].y;
        
        if (image_G.rect_wh.x < image_G.rect_wh.y)
        {
            std::swap(image_G.rect_wh.y, image_G.rect_wh.x);
            image_G.rect_area_angle.x = image_G.rect_area_angle.x + 90;
        }
        boundingBox.width, boundingBox.height = image_G.rect_wh.x, image_G.rect_wh.y;

        std::vector<cv::Point> armour_list = image_G.Image_GetArmour(image_G.rect_center_point, image_G.rect_wh, image_G.rect_area_angle);
        allArmours.push_back(armour_list);
    }
    
    return allArmours;  
}    

std::vector<cv::Point> Image_Process::Image_GetBoundingBoxPoints(cv::Rect boundingBox, cv::RotatedRect rect) {  
    // 创建存储四个点的向量  

    std::vector<cv::Point> boxPoints;  

    boxPoints.push_back(cv::Point(boundingBox.x, boundingBox.y));  // 左上角  

    boxPoints.push_back(cv::Point(boundingBox.x + boundingBox.width, boundingBox.y));  // 右上角  

    boxPoints.push_back(cv::Point(boundingBox.x + boundingBox.width, boundingBox.y + boundingBox.height));  // 右下角  

    boxPoints.push_back(cv::Point(boundingBox.x, boundingBox.y + boundingBox.height));  // 左下角  

    boxPoints.push_back(cv::Point(boundingBox.x + boundingBox.width / 2, boundingBox.y + boundingBox.height / 2)); // 中心点坐标

    boxPoints.push_back(cv::Point(boundingBox.width * boundingBox.height, rect.angle)); //旋转角度
    
    return boxPoints;  

}    

std::vector<cv::Point> Image_Process::Image_GetArmour(cv::Point rect_center_point, cv::Point rect_wh, cv::Point rect_area_angle) {  
    // 创建装甲板 包含装甲板的中心点坐标 宽、高、旋转角度  

    std::vector<cv::Point> armour_list;  

    armour_list.push_back(cv::Point(rect_center_point.x - rect_wh.y / 2, rect_center_point.y - rect_wh.x / 2)); //左上角坐标

    armour_list.push_back(cv::Point(rect_center_point.x + rect_wh.y / 2, rect_center_point.y - rect_wh.x / 2)); //右上角坐标

    armour_list.push_back(cv::Point(rect_center_point.x + rect_wh.y / 2, rect_center_point.y + rect_wh.x / 2)); //右下角坐标

    armour_list.push_back(cv::Point(rect_center_point.x - rect_wh.y / 2, rect_center_point.y + rect_wh.x / 2)); //左下角坐标

    armour_list.push_back(rect_center_point); //中心坐标

    armour_list.push_back(rect_wh); //灯条的宽、高

    armour_list.push_back(rect_area_angle); //水平线逆时针碰上的第一条线形成的夹角

    return armour_list;  

}    

std::vector<cv::Point> Image_Process::Image_Armour(cv::Point armour_s0, cv::Point armour_s1, cv::Point armour_s2, cv::Point armour_s3, cv::Point armour_center, cv::Point armour_wh) {  
    // 创建装甲板 包含装甲板的中心点坐标 宽、高、旋转角度、数字

    std::vector<cv::Point> armour_new;  
    cv::Point armour_num;
    armour_num.x = 0;//默认装甲板数字为0
    armour_new.push_back(armour_s0);
    armour_new.push_back(armour_s1);
    armour_new.push_back(armour_s2);
    armour_new.push_back(armour_s3);
    armour_new.push_back(armour_center);
    armour_new.push_back(armour_wh);
    armour_new.push_back(armour_num);

    return armour_new;  

}    

std::vector<std::vector<cv::Point>> Image_Process::Image_SelectArmour(std::vector<std::vector<cv::Point>> armours, cv::Mat frame){  
    std::vector<std::vector<cv::Point>> frist_armours; // 存储第一次筛选过armours的集合  
    std::vector<std::vector<cv::Point>> second_armours; // 存储第二次筛选过armours的集合  
    std::vector<cv::Point> armour_new;  // 存储筛选的装甲板的集合
    cv::Point armour_s0, armour_s1, armour_s2, armour_s3, armour_center, armour_wh, armour_area_angle;
    
    cv::Mat gray, img;
    //第一次筛选装甲板
    // 判断allArmours集合的数量是否大于0 
    if (armours.size() > 0) {  
        for(const auto& armour : armours){
            if((armour[5].x >= armour[5].y ) && \
            (armour[5].x / armour[5].y > 1.1) && \
            (armour[5].x * armour[5].y > 200 && armour[5].x * armour[5].y < 1200) && \
            (armour[6].x > 45. && armour[6].x < 135.)){
                frist_armours.push_back(armour);
            }
        }
    }
     else {  
        // std::cout << "集合的数量为0" << std::endl;  
        return {};
    }
    
    //第二次筛选装甲板
    //将两个灯条匹配为一个装甲板
    int n = frist_armours.size();
    if (n > 0)
    {
        for (int _ = 0; _ < n; _++)
        {
            for (int i = _+1; i < n; i++)
            {
                armour_s0.x = frist_armours[_][0].x;
                armour_s0.y = frist_armours[_][0].y;

                armour_s1.x = frist_armours[i][1].x;
                armour_s1.y = frist_armours[i][1].y;

                armour_s2.x = frist_armours[i][2].x;
                armour_s2.y = frist_armours[i][2].y;

                armour_s3.x = frist_armours[_][3].x;
                armour_s3.y = frist_armours[_][3].y;

                armour_center.x = (frist_armours[_][4].x + frist_armours[i][4].x) / 2;
                armour_center.y = (frist_armours[_][4].y + frist_armours[i][4].y) / 2;

                armour_wh.x = std::sqrt(std::pow((frist_armours[i][1].x - frist_armours[_][0].x), 2) + std::pow((frist_armours[i][1].y - frist_armours[_][0].y),2 )); //装甲板的宽
                armour_wh.y = std::sqrt(std::pow((frist_armours[_][3].x - frist_armours[_][0].x), 2) + std::pow((frist_armours[_][3].y - frist_armours[_][0].y),2 )); //装甲板的高

                armour_new = Image_Process::Image_Armour(armour_s0, armour_s1, armour_s2, armour_s3, armour_center, armour_wh);
                
                // SVM
                float result = 4.0;
                if (armour_s0.x >0 && armour_s0.y >0 && armour_wh.x >0 && armour_wh.y >0 && armour_s0.x + armour_wh.x  < frame.cols && armour_s0.y  + armour_wh.y < frame.rows)
                {
                    cv::Rect roi(armour_s0.x, armour_s0.y, armour_wh.x, armour_wh.y);
                    cv::Mat roiImage = frame(roi);
                    
                    cv::cvtColor(roiImage, gray, cv::COLOR_BGR2GRAY);
                    cv::resize(gray, gray, cv::Size(224, 112));
                    img = gray.reshape(1, 1);
                    img.convertTo(img, CV_32F);
                    result = svm->predict(img);
                    printf("%f\n", result);

                    //串口测试
                    if (serUL_Image.flag == 0)
                    {
                        serUL_Image.Serial_init();
                        serUL_Image.Serial_Open();
                        serUL_Image.flag = 1;
                    }
                    
                    char array[1000] = {4,5,6,7};
                    serUL_Image.Serial_Write(array);
                    
                }
 
                if((std::abs(frist_armours[_][6].y - frist_armours[i][6].y) < 45.) && (armour_wh.x * armour_wh.y > 3000 && armour_wh.x * armour_wh.y < 8000) && (result != 2.0)){
                    second_armours.push_back(armour_new);
                } 
            }
        }
    }
    else{
        return {};
    }
    
    return second_armours; 
} 

// 提取ROI
cv::Mat Image_Process::Image_GetImageROI(cv::Mat frame, cv::Point point_xy, cv::Point point_wh){

    // cv::Rect roi(100, 100, 200, 200); // 从(100, 100)开始，宽度和高度都为200的矩形区域  

    cv::Rect roi(point_xy.x, point_xy.y, point_wh.x, point_wh.y);
    cv::Mat roiImage = frame(roi); 

    return roiImage;
}