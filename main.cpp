#include "mbed.h"
#include <Encoder.hpp>
#include <PulseGenerator.hpp>
#include <cstdio>

#define ENCODER_CHANNEL_A PA_0  //  A0
#define ENCODER_CHANNEL_B PA_1  //  A1
#define PULSE_CHANNLE_A PC_1    //  A4
#define PULSE_CHANNLE_B PC_0    //  A5

#define ENCODER_REVOLUTION 2048

Encoder encoder(ENCODER_CHANNEL_A, ENCODER_CHANNEL_B, ENCODER_REVOLUTION);
PulseGenerator generator(PULSE_CHANNLE_A, PULSE_CHANNLE_B, ENCODER_REVOLUTION);
Timer timer;


float getDt() {
    float last = 0;
    float present = 0;

    last = present;
    present = timer.read();

    return present - last;
}

int state = 0;
float rps = 10;

int main()
{
    timer.start();

    while (true) {
        if (state % 40 == 0) {
            generator.setRPS(rps);
            rps *= -1;
        }

        printf("t:%f o:%f\n\r", rps, encoder.get_rps(getDt()));

        wait_ms(250);
        state++;
    }
}
