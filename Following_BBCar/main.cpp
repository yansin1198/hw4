#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;

PwmOut pin5(D5), pin6(D6);

BufferedSerial pc(D1, D0);
BufferedSerial xbee(USBTX, USBRX);
BufferedSerial uart(D10, D9); //tx,rx
BBCar car(pin5, pin6, servo_ticker);

void linefollow(Arguments *in, Reply *out);
RPCFunction rpclinefollow(&linefollow, "linefollow");
double state = 0;
double x, y, m;

int point[5];

void compare(int x1, int x2) {
   
   if((x1 - x2 >= -2 && x1 - x2 <= 2)) { //|| (x2 - x1 >= 0 && x2 - x1 <= 2)
      car.goStraight(50);
      printf("goStraight\r\n");
      ThisThread::sleep_for(1500ms);
   }
   else if(x1 > x2) { //&& (x1 - x2 <= 5) && (x1 - x2 > 2)) {
      car.turn(-35, -0.2); 
      printf("turn left\r\n");
      ThisThread::sleep_for(500ms);
   }
   else if(x1 < x2) {// && (x2 - x1 <= 5) && (x2 - x1 > 2)) { 
      car.turn(-40, 0.1);
      printf("turn right\r\n");
      ThisThread::sleep_for(500ms);
   }
    car.stop();
    ThisThread::sleep_for(500ms);
}

void linefollow(Arguments *in, Reply *out) {

    uart.set_baud(9600);
    state = in->getArg<double>();
    printf("get\r\n");

    while (state) {
        if(uart.readable()) {
           for(int i = 0;;i++) {
                char recv[1];
                uart.read(recv, sizeof(recv));
                pc.write(recv, sizeof(recv));
                point[i] = (int)recv[0];
                if(recv[0] =='\n') {
                    break;
                }
            }

            printf("x1, x2, y1, y2: %d, %d, %d, %d \r\n", point[0], point[1], point[2], point[3]);

            compare(point[0], point[1]);
        } 
    }
}


int main() {
   char buf[256], outbuf[256];
   FILE *devin = fdopen(&xbee, "r");
   FILE *devout = fdopen(&xbee, "w");
   while (1) {
      memset(buf, 0, 256);
      for( int i = 0; ; i++ ) {
         char recv = fgetc(devin);
         if(recv == '\n') {
            printf("\r\n");
            break;
         }
         buf[i] = fputc(recv, devout);
      }
   RPC::call(buf, outbuf);
   }
}
