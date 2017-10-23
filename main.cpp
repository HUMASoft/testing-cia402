#include <iostream>

using namespace std;

#include "CiA402DeviceICanbus.h"

int main(int argc, char *argv[])
{
    //cambios
    CiA402DeviceICanbus com;//0x40,0x41,0x60,0x00,0x00,0x00,0x00,0x00}
    can_msg can_in,can;
    co_msg input, output;

    //prepare the board (reset)
    uint8_t msg_start1[]={0x81,0x01};//={0x81,0x00};
    vector<uint8_t> co_data_frame(msg_start1,msg_start1+2);
    com.SendMessage(com.SetCanOpenMsg(0x00,0,co_data_frame),0);
    com.WaitForReadMessage(output,0);
    sleep(1);

    //prepare the board (go to sod (T2))
    uint8_t msg_start2[]={0x01,0x01};
    co_data_frame = vector<uint8_t>(msg_start2,msg_start2+2);
    com.SendMessage(com.SetCanOpenMsg(0x00,0,co_data_frame),0);
    com.WaitForReadMessage(output,0);
    com.WaitForReadMessage(output,0);
    //com.WaitForReadMessage(output,0);

    sleep(1);

    //Get status word
    uint8_t msg_start3[]={0x40,0x41,0x60,0x00};
    co_data_frame = vector<uint8_t>(msg_start3,msg_start3+4);
    com.SendMessage(com.SetCanOpenMsg(0x601,0,co_data_frame),0);
    com.WaitForReadMessage(output,0);
    //com.WaitForReadMessage(output,0);

    sleep(1);

    uint8_t msg_start[]={0x2B,0x40,0x60,0x00,0x06,0x00,0x00,0x00};//={0x81,0x00};
    co_data_frame = vector<uint8_t>(msg_start,msg_start+8);
    //com.SetCanMsg(can,msg_start);
    input=com.SetCanOpenMsg(0x601,0,co_data_frame);//0xE05
    //com.SetCanMsg(can,msg_start);
    //com.co2c(input,can);

    if (com.SendMessage(input,0)<0){
        cout<<"error al enviar el mensaje"<<endl;
    }
    else{
        for(int i=0; i<10; i++){
            cout<<"el : " << i <<endl;
            if (com.WaitForReadMessage(output,0)<0){
                cout<<"error al recibir el mensaje"<<endl;
            }
        }
    }

    return 0;
}
