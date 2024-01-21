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
    cv::Point rect_center_point, rect_wh, rect_area_angle;

    cv::Mat Image_HsvImage(cv::Mat frame, cv::Mat hsvImage);

    std::vector<std::vector<cv::Point>> Image_FindContours(cv::Mat frame);

    std::vector<std::vector<cv::Point>> Image_GetContours(std::vector<std::vector<cv::Point>> contours, Image_Process image_p);

    std::vector<cv::Point> Image_GetBoundingBoxPoints(cv::Rect boundingBox, cv::RotatedRect rect);

    std::vector<cv::Point> Image_GetArmour(cv::Point rect_center_point, cv::Point rect_wh, cv::Point rect_area_angle);

    std::vector<std::vector<cv::Point>> Image_SelectArmour(std::vector<std::vector<cv::Point>> armours);

    std::vector<cv::Point> Image_Armour(cv::Point armour_s0, cv::Point armour_s1, cv::Point armour_s2, cv::Point armour_s3, cv::Point armour_center, cv::Point armour_wh);
};


#endif