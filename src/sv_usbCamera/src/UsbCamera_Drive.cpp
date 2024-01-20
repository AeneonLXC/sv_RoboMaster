#include "UsbCamera_Drive.hpp"

void UsbCamera_Drive::USB_GetImage(cv::Mat frame, int cameraNum){
    cv::VideoCapture cap(cameraNum);
    do
    {

    // 在这里可以对每一帧进行处理（如人脸识别、目标检测等）
    while (1)
    {
        if (!cap.isOpened()) {
        std::cout << "无法打开视频文件" << std::endl;
        break;
        }
        // 从视频源中获取当前帧图像
        bool success = cap.read(frame); 
        
        if (!success || frame.empty()) {
            break;
        }
        
        
        // 在这里可以对每一帧进行处理（如人脸识别、目标检测等）
        
        // 显示当前帧图像
        cv::imshow("Frame", frame);
        
        // 按下ESC键退出循环
        int keyCode = cv::waitKey(30);
        if (keyCode == 27) {
            break;
        }
    }
    cap.release();
    // 关闭视频源并释放内存
    cv::destroyAllWindows();
    }while (0);

    
}
