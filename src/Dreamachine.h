#ifndef _DREAMACHINE_H
#define _DREAMACHINE_H

class Dreamachine
{
public:
    Dreamachine();

private:
    int brightness = 0;
    int light_balance = 50;
    float frequency = 10;
    int waveshape = 0;
    int light_phase = 0;

    int volume = 0;
    int audio_balance = 50;
    int sound_type = 0;
    int audio_phase = 0;
    /*
    Brightness : 0-100%
Light Balance : L% : R%
Frequency : 1-50 Hz
Wave : sine/square
Light Phase : 0-359°

Volume : 0-100%
Audio Balance : L% : R%
Noise : white/pink
Audio Phase : 0-359°
*/
};

#endif
