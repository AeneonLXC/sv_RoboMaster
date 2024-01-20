#include <iostream>
#include "math.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <pthread.h>

#ifndef IMAGE_PROCESS
#define IMAGE_PROCESS

class Image_Process
{
private:
    /* data */
public:
    cv::Mat Image_HsvImage(cv::Mat frame, cv::Mat hsvImage);
    std::vector<std::vector<cv::Point>> Image_FindContours(cv::Mat frame);
};


#endif