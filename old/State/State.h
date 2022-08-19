#include <typeinfo>
#include <Arduino.h>
#include <Context.h>

#ifndef State_h
#define State_h

/**
 * The base State class declares methods that all Concrete State should
 * implement and also provides a backreference to the Context object, associated
 * with the State. This backreference can be used by States to transition the
 * Context to another State.
 */

class State
{
    /**
     * @var Context
     */
protected:
    Context *context_;

public:
    virtual ~State()
    {
    }

    void set_context(Context *context)
    {
        this->context_ = context;
    }

    virtual void Handle1() = 0;
    virtual void Handle2() = 0;
};

#endif