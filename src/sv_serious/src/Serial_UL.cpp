#include "Serial_UL.hpp"

Serial_UL serUL;
serial::Serial ser;
void Serial_UL::Serial_init(){
    ser.setPort(serUL.port);//串口设备
    ser.setBaudrate(serUL.Baudrate);//设置波特率
    serial::Timeout to = serial::Timeout::simpleTimeout(serUL.Timeout);
    ser.setTimeout(to);
}

bool Serial_UL::Serial_Open(){
    try
    {

        ser.open();//打开串口
        serUL.flag = 1;
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        printf("ERROR!!! Serial Open Fail!!!/n");
        return false;
    }
}
 
void Serial_UL::Serial_Write(char array[]){
    try
    {
        if (serUL.flag == 1)
        {
            ser.write(array);
        }
        else{
            printf("Serial Write is not  Fail!!!/n");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

// std::string Serial_readData(serial::Serial ser, std::string str){
//     ser.available();//读取到缓存区数据的字节数
//     ser.read(ser.available());//读出缓存区缓存的数据

// }

bool Serial_UL::Serial_Close(serial::Serial ser){
    try
    {
        if(serUL.flag == 1){
            ser.close();
        }
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        printf("Serial Close Fail!!!/\n");
        return false;
    }
}
