#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;

PwmOut pin5(D5), pin6(D6);

BufferedSerial pc(STDIO_UART_TX, STDIO_UART_RX);
BufferedSerial xbee(D1, D0);
//BufferedSerial uart(D10, D9); //tx,rx

DigitalInOut ping(D11);
parallax_ping ping1(ping);

BBCar car(pin5, pin6, servo_ticker);

/*void linefollow(Arguments *in, Reply *out);
RPCFunction rpclinefollow(&linefollow, "linefollow");*/
int state = 0;
int rest = 0;
int turnNext = 0;
int finish = 0;
int nextTask = 0;
int curTask = 0;
int step = 0;



int point[3] = {0};


/*void linefollow(Arguments *in, Reply *out) {

    
    state = in->getArg<double>();
    printf("Detect Start\r\n");

    
    
}*/

int main() {
    pc.set_baud(9600);
    int index = 0;
    /*char buf[256], outbuf[256];
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
    }*/

    while(1) {
        float distance = 0;
        distance = (float)ping1;

        if (state == 0) {
            car.goStraight(80);
            ThisThread::sleep_for(20ms);
            step++;
            //printf("step: %d\r\n", step);
            
            if (distance < 10) {
                nextTask = 2;
                rest = 1;
            } 
        } else if (state == 1) {

            /*nextTask = 3;
            car.stop();
            break;*/

            car.goStraight(80);
            ThisThread::sleep_for(20ms);
            step++;
            //printf("step: %d\r\n", step);
            
            if (distance < 10) {
                nextTask = 3;
                rest = 1;
            } 


        } else if (state == 2) {
            
            /*nextTask = -1;
            car.stop();
            break;*/

            car.goStraight(80);
            ThisThread::sleep_for(20ms);
            step++;
            //printf("step: %d\r\n", step);
            
            if (distance < 10) {
                nextTask = -1;
                rest = 1;
            } 
        
        } 

        
        
        if (rest == 1) {
            point[index] = step;
            for (int i = step; i >= 0; i--) {
                car.goStraight(-80);
                ThisThread::sleep_for(30ms);
                //ThisThread::sleep_for(40ms);
                //printf("last step: %d\r\n", i);
            }
            step = 0;
            index++;
            if (nextTask == 2) {
                car.turn(30, 0.2); //turn left
                ThisThread::sleep_for(2000ms);
                state = 1;
                printf("It is task %d\r\n", state);
                printf("\r\n");
            }
            else if (nextTask == 3) {
                //car.goStraight(-80);
                //ThisThread::sleep_for(650ms);
                car.turn(20, -0.1); //turn right
                ThisThread::sleep_for(1400ms);
                car.turn(30, 0.2); //turn left
                ThisThread::sleep_for(2400ms);
                //ThisThread::sleep_for(2900ms);
                state = 2;
                printf("It is task %d\r\n", state);
                printf("\r\n");
            }
            else if (nextTask == -1) {
                //car.goStraight(-80);
                //ThisThread::sleep_for(650ms);
                car.turn(20, -0.1); //turn right
                ThisThread::sleep_for(2400ms);
                state = 3;
                printf("It is task %d\r\n", state);
                int temp = 0;
                printf("Finish Mission\r\n");
                printf("Task 1 step: %d, Task 2 step: %d, Task 3 step: %d\r\n", point[0], point[1], point[2]);
                for (int j = 0; j < 3; j++) {
                    for (int k = j+1; k < 3; k++) {
                        if (point[j] < point[k]) {
                            temp = point[j];
                            point[j] = point[k];
                            point[k] = temp;
                        }
                    }
                }
                printf("Order step: %d, %d, %d\r\n", point[0], point[1], point[2]);
                int p = 3;
                for (int j = 0; j < 3; j++) {
                    point[j] = p;
                    p--;
                }

                printf("Task 1 item: %d, Task 2 item: %d, Task 3 item: %d\r\n", point[0], point[1], point[2]);
                car.stop();
                break;
            }
            rest = 0;
        }
        //printf("distance: %.1f\r\n", distance);
    }
}
