#ifndef _CALLBACK
#define _CALLBACK

#include <iostream>

template <typename... Args>
class Callback {
public:
    Callback() {
        Function = nullptr;
    }

    Callback(void (*function)(void* sender, Args...)) {
        Function = function;
    }

    virtual void Call(void* sender, Args... args) {
        if(Function != nullptr) {
            (*Function)(sender, args...);
        }
    }

    void (*Function)(void* sender, Args...);
};

template <typename OBJ, typename... Args>
class ClassCallback : public Callback<Args...> {
public:
    ClassCallback() {
        mFunction = nullptr;
        mObject = nullptr;
    }

    ClassCallback(OBJ* object, void (OBJ::*function)(void* sender, Args...)) {
        mFunction = function;
        mObject = object;
    }

    virtual void Call(void* sender, Args... args) {
        if(mFunction != nullptr && mObject != nullptr) {
            // mObject->*mFunction(args...);
            (mObject->*((ClassCallback<OBJ, Args...>*)this)->ClassCallback<OBJ, Args...>::mFunction)(sender, args...);
        }
    }

private:
    OBJ* mObject;
    void (OBJ::*mFunction)(void* sender, Args...);
};

#endif
