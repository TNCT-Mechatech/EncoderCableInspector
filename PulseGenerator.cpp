#include <PulseGenerator.hpp>

PulseGenerator::PulseGenerator(PinName channel_a, PinName channel_b, int revolution)
    :_A(channel_a,PullDown), _B(channel_b,PullDown)
{
    _revolution = revolution;
    _pps = 0;

    setRPS(0.0);
}

void PulseGenerator::setRPS(float rps)
{
    _pps = (int) (rps * (float)_revolution);
    
    //  detach and attach
    _ticker.detach();
    float interval = 1.0 / (abs(_pps) * 4);
    _ticker.attach(this, &PulseGenerator::generatePulse, interval);
}

void PulseGenerator::generatePulse() {
    switch (_state) {
        case 0:
            _A = _pps > 0 ? 1 : 0;
            _B = _pps > 0 ? 0 : 1;
            break;
        case 1:
            _A = 1;
            _B = 1;
            break;
        case 2:
            _A = _pps > 0 ? 0 : 1;
            _B = _pps > 0 ? 1 : 0;
            break;
        case 3:
            _A = 0;
            _B = 0;
            break;
    }
    
    _state = (_state + 1) % 4;
}