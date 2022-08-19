#include <State.h>
#include <Context.h>
#include <ConcreteStateA.h>
#include <ConcreteStateB.h>

/**
 * The Context allows changing the State object at runtime.
 */
void Context::TransitionTo(State *state)
{
    Serial.print("Context: Transition to ");
    Serial.println(typeid(*state).name());
    if (this->state_ != nullptr)
        delete this->state_;
    this->state_ = state;
    this->state_->set_context(this);
}