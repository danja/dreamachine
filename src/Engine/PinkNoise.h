#ifndef _PinkNoise_H
#define _PinkNoise_H

// derived from https://music-dsp.music.columbia.narkive.com/0LpD0W4l/pink-noise-algorithm-posted

#include <cstdlib>
#include <ctime>

#define PINK_NOISE_NUM_STAGES 3

class PinkNoise
{
public:
    PinkNoise(){

    };
    //  int srand(time(NULL)); // initialize random generator
    void clear();
    float tick();
    float rand1();

protected:
    float state[PINK_NOISE_NUM_STAGES];
    static const float A[PINK_NOISE_NUM_STAGES];
    static const float P[PINK_NOISE_NUM_STAGES];
};
#endif
