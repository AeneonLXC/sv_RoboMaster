#include <iostream>
#include "math.h"
#include "serial.h"
#include "string.h"

#ifndef SERIAL_UL
#define SERIAL_UL
//install serial https://gitcode.com/wjwwood/serial/overview?utm_source=csdn_github_accelerator&isLogin=1
//sudo make install
//sudo chmod 777 /dev/ttyUSB0
class Serial_UL
{
private:
    /* data */
public:
    std::string port = "/dev/ttyUSB0";//串口的设备号
    int Baudrate = 115200;//波特率
    int Timeout = 1000;//每次读取串口数据到缓存区的时间，时间越大，读取到缓存区数据量越大
    int flag = 0;//串口标识位 0代表未打开茶串口  1代表串口已打开
    char stack[1000] = {};
    
    void Serial_init();//初始化串口

    bool Serial_Open(); //打开串口

    void Serial_Write(char array[]);//发送数据

    // std::string Serial_readData(serial::Serial ser, char array[]);//读取数据

    bool Serial_Close(serial::Serial ser);//关闭串口
};



#endif