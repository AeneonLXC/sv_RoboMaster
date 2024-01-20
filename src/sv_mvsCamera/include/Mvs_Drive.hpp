#include <iostream>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <pthread.h>

#include "MvCameraControl.h"

#ifndef MVS
#define MVS

class Mvs_Drive{
private:
    /* data */
    int mvsImageWidth;
    int mvsImageHeight;
public:
    // Mvs_Drive(/* args */);
    // ~Mvs_Drive();
    bool flag = false;
    int nRet = MV_OK;
    void* handle = NULL;
	unsigned char * pData = NULL;        
    unsigned char *pDataForRGB = NULL;

    //打印设备信息
    bool PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo);
    
    //初始化设备参数
    MV_CC_DEVICE_INFO_LIST MVS_InitMvsParameter();

    //枚举设备
    MV_CC_DEVICE_INFO_LIST MVS_EnumDevices(MV_CC_DEVICE_INFO_LIST stDeviceList);

    //创建句柄
    void* MVS_CreateHandle(MV_CC_DEVICE_INFO_LIST stDeviceList);

    //启动设备
    void* MVS_StartDvices(void *handle, unsigned int nIndex, MV_CC_DEVICE_INFO_LIST stDeviceList);

    //获取数据包
    MVCC_INTVALUE MVS_GetPayloadSize(void *handle);

    //开始取流
    void MVS_StartGrabbing();

    //采集图像并显示 OpenCV
    void MVS_Starting_Imshow(void* handle, int nRet, unsigned char *pDataForRGB , unsigned char *pData, MVCC_INTVALUE stParam);

    //停止取流
    void MVS_EndGrabbing(void *handle);

    //销毁句柄
    void MVS_DestoryHandle(void *handle);

    //释放内存 结束程序
    int Mvs_EndALL(void *handle);

    //启动所有程序
    void MVS_StartALLProgress(Mvs_Drive Mvs);

};


#endif