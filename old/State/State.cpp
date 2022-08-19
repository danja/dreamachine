#include <typeinfo>
#include <Arduino.h>
#include <State.h>
#include <Context.h>

/**
 * The base State class declares methods that all Concrete State should
 * implement and also provides a backreference to the Context object, associated
 * with the State. This backreference can be used by States to transition the
 * Context to another State.
 */

void State::set_context(Context *context)
{
    this->context_ = context;
}

#endif