#ifndef _LEDDRIVER_h
#define _LEDDRIVER_h

#include <Dispatcher.hpp>
#include <iostream>

using namespace std;

class LedDriver
{
public:
    LedDriver();
    void setLevel(float level);
    void registerCallback(Dispatcher<float> &dispatcher)
    {
        using namespace std::placeholders;
        dispatcher.addCallback(std::bind(&LedDriver::setLevel, this, _1));
    }

private:
};
#endif
