#ifndef _RANGE
#define _RANGE

#include "Random.hpp"

template <typename T>
class Range {
public:
    Range() {}

    Range(T both) {
        mMinimum = both;
        mMaximum = both;
    }

    Range(T minimum, T maximum) {
        mMinimum = minimum;
        mMaximum = maximum;
    }

    T GetMinimum() {
        return mMinimum;
    }

    T GetMaximum() {
        return mMaximum;
    }

    void SetMinimum(T minimum) {
        mMinimum = minimum;
    }

    void SetMaximum(T maximum) {
        mMaximum = maximum;
    }

    void Set(T minimum, T maximum) {
        mMinimum = minimum;
        mMaximum = maximum;
    }

    void Set(T both) {
        mMinimum = both;
        mMaximum = both;
    }

    virtual T GetRandom() {
        if(mMinimum == mMaximum)
            return mMinimum;
        return Random::Get(mMinimum, mMaximum);
    }

private:
    T mMinimum;
    T mMaximum;
};

#endif
