#ifndef _RANDOM
#define _RANDOM

#include <random>

class Random {
public:
    static void Initialize();

    static int Get(int min, int max);
    static float Get(float min, float max);

private:
    static std::mt19937 Generator;
};

#endif
