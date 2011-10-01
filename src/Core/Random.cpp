#include "Random.hpp"

std::mt19937 Random::Generator;

void Random::Initialize() {
    Generator.seed(time(0));
}

int Random::Get(int min, int max) {
    return std::uniform_int_distribution<int>(min, max)(Generator);
}

float Random::Get(float min, float max) {
    return std::uniform_real_distribution<float>(min, max)(Generator);
}

bool Random::GetBool() {
    return Get(0, 1) == 1;
}
