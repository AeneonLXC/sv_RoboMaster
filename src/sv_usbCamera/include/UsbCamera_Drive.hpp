#include <iostream>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#ifndef USB_CAMERA
#define USB_CAMERA

class UsbCamera_Drive
{
private:
    /* data */
public:
    int cameraNum = 0; //USB相机的编号 通常是0

    void USB_GetImage(cv::Mat frame, int cameraNum);
    
};



#endif