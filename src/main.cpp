#include <main.h>

#include "Mvs_Drive.hpp"
#include "UsbCamera_Drive.hpp"

#define DEBUG_CAMERA 1 //用于debug 0 代表使用USB相机; 1 代表使用工业相机
using namespace std;

int main(){
    Mvs_Drive Mvs;
    UsbCamera_Drive Usb;
    cv::Mat frame; 
    int cameraNum = 0;

    if(DEBUG_CAMERA){
        Mvs.MVS_StartALLProgress(Mvs);
    }
    else{
        Usb.USB_GetImage(frame, cameraNum);
    }

    return 0;
}