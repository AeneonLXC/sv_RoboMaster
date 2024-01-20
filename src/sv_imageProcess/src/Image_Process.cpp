#include "Image_Process.hpp"

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

std::vector<std::vector<cv::Point>> Image_Process::Image_FindContours(cv::Mat binaryImage){
    std::vector<std::vector<cv::Point>> contours;  
    std::vector<cv::Vec4i> hierarchy;  
    // 查找轮廓  
    cv::findContours(binaryImage, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);  
    return contours;  

}

    
