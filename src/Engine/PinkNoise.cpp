#include <PinkNoise.h>

// http://home.earthlink.net/~ltrammell/tech/pinkalg.htm

#include <cstdlib>
#include <ctime>

// A = [ 0.01089, 0.00899, 0.01359 ];
const float PinkNoise::A[] = {0.02109238, 0.07113478,
                              0.68873558}; // rescaled by (1+P)/(1-P)
const float PinkNoise::P[] = {0.3190, 0.7756, 0.9613};

void PinkNoise::clear()
{
    for (size_t i = 0; i < PINK_NOISE_NUM_STAGES; i++)
        state[i] = 0.0;
}

float PinkNoise::tick()
{
    static const float RMI2 = 2.0 / float(RAND_MAX);
    static const float offset = A[0] + A[1] + A[2];

    float temp = float(rand());
    state[0] = P[0] * (state[0] - temp) + temp;
    temp = float(rand());
    state[1] = P[1] * (state[1] - temp) + temp;
    temp = float(rand());
    state[2] = P[2] * (state[2] - temp) + temp;
    float total = (A[0] * state[0] + A[1] * state[1] + A[2] * state[2]) * RMI2 -
                  offset;
    return total * 256;
}

float PinkNoise::rand1()
{
    static const float RMI2 = 2.0 / float(RAND_MAX);
    return float(rand()) * RMI2 - 1.0;
}
