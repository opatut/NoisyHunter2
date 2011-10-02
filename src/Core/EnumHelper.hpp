#ifndef _ENUM_HELPER
#define _ENUM_HELPER

#include <SFML/Network/Packet.hpp>

#include <cstdint>

class EnumHelper {
public:
    EnumHelper(void* e);
    uint32_t Get();
    void Set(uint32_t i);

private:
    void* mEnumObj;
};

sf::Packet& operator << (sf::Packet& p, EnumHelper e);
sf::Packet& operator >> (sf::Packet& p, EnumHelper e);

#endif
