#include <iostream>
#include "math.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <pthread.h>

#ifndef ARMOR
#define ARMOR

class Armour
{
private:
    /* data */
public:
    // Armour(/* args */);
    // ~Armour();
    short int armour_color;//定义当前自身装甲版的颜色: 0->red; 1->blue;
    short int armour_type;//定义装甲版的类型: 0->小装甲版； 1->大装甲版； 2->哨兵装甲版； 3->基地装甲版
    float armour_point_x1, armour_point_x2, armour_point_x3, armour_point_x4; //定义当前自身装甲版的四点坐标: 左上为x1,y1，顺时针编号
    float armour_point_y1, armour_point_y2, armour_point_y3, armour_point_y4;     
    float armour_point_center_x1, armour_point_center_y1; //定义当前自身装甲版的中心坐标
};

#endif