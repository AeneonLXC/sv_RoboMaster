// #include <iostream>
// #include <opencv2/core.hpp>
// #include <opencv2/highgui.hpp>
// #include <opencv2/imgproc.hpp>
 
// int main() {
//     // 打开视频文件或者从摄像头中读取视频流
//     cv::VideoCapture cap(0);
    
//     if (!cap.isOpened()) {
//         std::cout << "无法打开视频文件" << std::endl;
//         return -1;
//     }
    
//     while (true) {
//         cv::Mat frame;
        
//         // 从视频源中获取当前帧图像
//         bool success = cap.read(frame); 
        
//         if (!success || frame.empty()) {
//             break;
//         }
        
//         // 在这里可以对每一帧进行处理（如人脸识别、目标检测等）
//             // 2. 定义ROI的矩形区域 (left, top, width, height)  

//         cv::Rect roi(100, 100, 200, 200); // 从(100,100)开始，宽度和高度都为200的矩形区域  
//         // 3. 提取ROI  
//         cv::Mat roiImage = frame(roi);  
//         // 4. 显示或保存ROI  
//         cv::imshow("ROI", roiImage);   
//         // 显示当前帧图像
//         cv::imshow("Frame", frame);
        
//         // 按下ESC键退出循环
//         int keyCode = cv::waitKey(30);
//         if (keyCode == 27) {
//             break;
//         }
//     }
    
//     // 关闭视频源并释放内存
//     cap.release();
//     cv::destroyAllWindows();
    
//     return 0;
// }