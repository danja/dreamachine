#include <ConcreteStateA.h>

void ConcreteStateA::Handle1()
{
    {
        Serial.println("ConcreteStateA handles request1.");
        Serial.println("ConcreteStateA wants to change the state of the context.");

        this->context_->TransitionTo(new ConcreteStateB);
    }
}