#include <State.h>

#ifndef ConcreteStateA_h
#define ConcreteStateA_h

class ConcreteStateA : public State
{
public:
    void Handle1() override;

    void Handle2() override;
};
#endif