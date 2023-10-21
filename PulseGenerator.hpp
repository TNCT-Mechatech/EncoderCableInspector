#ifndef _PULSE_GENERATOR_HPP_
#define _PULSE_GENERATOR_HPP_

#include <mbed.h>

class PulseGenerator
{
public:
    PulseGenerator(PinName channel_a, PinName channel_b, int revolution);

    void setRPS(float rps);
    
private:
    void generatePulse();

    //  pin
    DigitalOut _A, _B;
    //  ticker
    Ticker _ticker;

    //  revolution
    int _revolution;
    //  target pulse per second
    int _pps;
    //  private variables
    int _state;
};

#endif