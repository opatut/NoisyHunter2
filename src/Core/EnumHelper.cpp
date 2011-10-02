#include "EnumHelper.hpp"

EnumHelper::EnumHelper(void* e)
    : mEnumObj(e) {}

uint32_t EnumHelper::Get() {
    return (uint32_t)(*((uint32_t*)mEnumObj));
}

void EnumHelper::Set(uint32_t i) {
   *((uint32_t*)mEnumObj) = i;
}

sf::Packet& operator << (sf::Packet& p, EnumHelper e) {
    uint32_t i = e.Get();
    p << i;
    return p;
}

sf::Packet& operator >> (sf::Packet& p, EnumHelper e) {
    uint32_t i;
    p >> i;
    e.Set(i);
    return p;
}
