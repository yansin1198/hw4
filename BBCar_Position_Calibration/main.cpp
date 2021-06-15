#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;

PwmOut pin5(D5), pin6(D6);

BufferedSerial pc(USBTX, USBRX);
//BufferedSerial xbee(USBTX, USBRX);
BufferedSerial uart(D10, D9); //tx,rx
BBCar car(pin5, pin6, servo_ticker);
DigitalInOut ping(D12);
DigitalOut led1(LED1);

/*void parking(Arguments *in, Reply *out);
RPCFunction rpcparking(&parking, "parking");
double d1, d2;
char dir;
int waitTime;*/


int main(){
   uart.set_baud(9600);
   parallax_ping  ping1(ping);
   while(1){
      if(uart.readable()){
            char recv[1];
            uart.read(recv, sizeof(recv));
            pc.write(recv, sizeof(recv));
            printf("\r\n");

        if((float)ping1 > 25) led1 = 1;
        else {
            led1 = 0;
            car.stop();
            break;
        }
        
        if (recv[0] == 'S') {

            
        } else if (recv[0] == 'R') {   // turn right
            


        } else if (recv[0] == 'L') {   // turn left
            
            
        } 
        ThisThread::sleep_for(500ms);
      }
   }
}