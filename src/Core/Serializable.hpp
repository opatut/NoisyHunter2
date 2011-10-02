#ifndef _SERIALIZABLE
#define _SERIALIZABLE

#include <SFML/Network/Packet.hpp>
#include "IOPacket.hpp"

class Serializable {
public:
    virtual void Serialize(IOPacket& packet) = 0;
    virtual uint32_t GetTypeId() const = 0;
    virtual Serializable* CreateInstance() const = 0;
};

#endif
