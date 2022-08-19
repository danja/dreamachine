#include <State.h>

#ifndef ConcreteStateB_h
#define ConcreteStateB_h

class ConcreteStateB : public State
{
public:
    void Handle1() override
    {
        Serial.println("ConcreteStateB handles request1.");
    }
    void Handle2() override
    {
        Serial.println("ConcreteStateB handles request2.");
        Serial.println("ConcreteStateB wants to change the state of the context.");
        this->context_->TransitionTo(new ConcreteStateA);
    }
};
#endif