#include <State.h>

#ifndef Context_h
#define Context_h

class Context
{
    /**
     * @var State A reference to the current state of the Context.
     */
private:
    State *state_;

public:
    Context(State *state) : state_(nullptr)
    {
        this->TransitionTo(state);
    }
    ~Context()
    {
        delete state_;
    }

    void TransitionTo(State *state);

    /**
     * The Context delegates part of its behavior to the current State object.
     */
    void Request1()
    {
        this->state_->Handle1();
    }
    void Request2()
    {
        this->state_->Handle2();
    }
};
#endif