#ifndef _CALLBACK
#define _CALLBACK

#include <iostream>

template <typename... Args>
class Callback {
public:
    Callback() {
        Function = nullptr;
    }

    Callback(void (*function)(Args...)) {
        Function = function;
    }

    virtual void Call(Args... args) {
        if(Function != nullptr) {
            (*Function)(args...);
        }
    }

    void (*Function)(Args...);
};

template <typename OBJ, typename... Args>
class ClassCallback : public Callback<Args...> {
public:
    ClassCallback() {
        mFunction = nullptr;
        mObject = nullptr;
    }

    ClassCallback(OBJ* object, void (OBJ::*function)(Args...)) {
        mFunction = function;
        mObject = object;
    }

    virtual void Call(Args... args) {
        if(mFunction != nullptr && mObject != nullptr) {
            // mObject->*mFunction(args...);
            (mObject->*((ClassCallback<OBJ, Args...>*)this)->ClassCallback<OBJ, Args...>::mFunction)(args...);
        }
    }

private:
    OBJ* mObject;
    void (OBJ::*mFunction)(Args...);
};

#endif
