#include <iostream>

using namespace std;

#include "CiA402DeviceICanbus.h"

int main(int argc, char *argv[])
{
    CiA402DeviceICanbus com;
    can_msg can_in,can;
    co_msg input, output;
    uint8_t msg_start[]={};//={0x81,0x00};
    vector<uint8_t> co_data_frame(msg_start,msg_start);
    //com.SetCanMsg(can,msg_start);
    input=com.SetCanOpenMsg(0x702,1,co_data_frame);//0xE05
    //com.SetCanMsg(can,msg_start);
    //com.co2c(input,can);

    if (com.SendMessage(input,0)<0){
        cout<<"error al enviar el mensaje"<<endl;
    }
    else{
        for(int i=0; i<100; i++){
            if (com.WaitForReadMessage(output,0)<0){
                cout<<"error al recibir el mensaje"<<endl;
            }
        }
    }

    return 0;
}
