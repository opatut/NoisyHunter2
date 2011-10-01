#ifndef _RANDOM
#define _RANDOM

#include <random>

class Random {
public:
    static void Initialize();

    static int Get(int min, int max);
    static float Get(float min, float max);
    static bool GetBool();

    template <typename T>
    static T PickOne(T a, T b) {
        int n = Get(0, 1);
        if(n == 0) return a;
        else return b;
    }

private:
    static std::mt19937 Generator;
};

#endif
