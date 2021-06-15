#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;

PwmOut pin5(D5), pin6(D6);

BufferedSerial pc(USBTX, USBRX);
//BufferedSerial xbee(USBTX, USBRX);
BufferedSerial uart(D10, D9); //tx,rx
BBCar car(pin5, pin6, servo_ticker);

/*void parking(Arguments *in, Reply *out);
RPCFunction rpcparking(&parking, "parking");
double d1, d2;
char dir;
int waitTime;*/


int main(){
   uart.set_baud(9600);
   while(1){
      if(uart.readable()){
            char recv[1];
            uart.read(recv, sizeof(recv));
            pc.write(recv, sizeof(recv));
            printf("\r\n");

        if (recv[0] == '1') {
                printf("go straight\r\n");
                car.goStraight(50);
                ThisThread::sleep_for(500ms);
                car.stop();

        } else { 
            printf("stop\r\n");
            car.stop();
        } 
        ThisThread::sleep_for(500ms);
      }
   }
}