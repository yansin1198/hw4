#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;
Ticker encoder_ticker;

PwmOut pin5(D5), pin6(D6);
DigitalIn encoder(D11);
volatile int steps;
volatile int last;

BufferedSerial pc(D1, D0);
BufferedSerial xbee(USBTX, USBRX);
BBCar car(pin5, pin6, servo_ticker);

void parking(Arguments *in, Reply *out);
RPCFunction rpcparking(&parking, "parking");
double d1, d2;
char dir;
int waitTime;

void servo_control(int r_speed, int l_speed);

void encoder_control() {
   int value = encoder;
   if (!last && value) steps++;
   last = value;
}

void parking(Arguments *in, Reply *out) {

    d1 = in->getArg<double>();
    d2 = in->getArg<double>();
    dir = in->getArg<char>();


    if (dir == 'W') {
        car.goStraight(-200);
        waitTime = int(1000*(d2+4)/20);
        ThisThread::sleep_for(waitTime);
        car.turn(-40, -0.1);
        ThisThread::sleep_for(2950ms);
        car.goStraight(-200);
        waitTime =  int(1000*(d1)/20);
        ThisThread::sleep_for(waitTime);
        car.stop();
    } else if (dir == 'E') {
        car.goStraight(-200);
        waitTime = int(1000*(d2+4)/20);
        ThisThread::sleep_for(waitTime);
        car.turn(-35, 0.2);
        ThisThread::sleep_for(2900ms);
        car.goStraight(-200);
        waitTime =  int(1000*(d1)/20);
        ThisThread::sleep_for(waitTime);
        car.stop();
    }

    /*if (dir == 'W') {
        car.goStraight(-200);
        waitTime = int(1000*(d2+10.5)/33);
        ThisThread::sleep_for(waitTime);
        car.turn(-80, -0.1);
        ThisThread::sleep_for(1910ms);
        car.goStraight(-200);
        waitTime =  int(1000*(d1+5.5)/36);
        ThisThread::sleep_for(waitTime);
        car.stop();
    } else if (dir == 'E') {
        car.goStraight(-200);
        waitTime = int(1000*(d2+10.5)/15);
        ThisThread::sleep_for(waitTime);
        car.turn(80, -0.1);
        ThisThread::sleep_for(1550ms);
        car.goStraight(-200);
        waitTime =  int(1000*(d1+5.5)/14);
        ThisThread::sleep_for(waitTime);
        car.stop();
    }*/
    

    /*pc.set_baud(9600);
    encoder_ticker.attach(&encoder_control, 10ms);
    steps = 0;
    last = 0;

    car.goStraight(-68);
    while(steps*6.5*3.14/32 < d2 + 8 + 6.5) {  
        ThisThread::sleep_for(100ms);
    }

    car.stop();

    
    if(dir == 'W') { // if at west, turn left
        car.turn(80, 0.3);
        ThisThread::sleep_for(2050ms);
    } else if(dir == 'E') { // if at east, turn right
        car.turn(88, -0.3);
        ThisThread::sleep_for(2600ms);
    }  

    steps = 0;              
    last = 0;

    car.goStraight(-120);
    while(steps*6.5*3.14/32 < 0.2*(d1 + 5.5 + 8.5)) {
        ThisThread::sleep_for(1450ms);
    }

    car.stop();*/

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