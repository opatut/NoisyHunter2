#ifndef _SERIALIZABLE
#define _SERIALIZABLE

#include <SFML/Network/Packet.hpp>

class Serializable {
public:
    enum SerializableType {
        ST_LEVEL = 0x01
    };

    virtual void Serialize(sf::Packet& packet) = 0;
    virtual void Deserialize(sf::Packet& packet) = 0;
    virtual SerializableType GetType() const = 0;
};

#endif
