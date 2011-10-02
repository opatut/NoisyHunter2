#ifndef _IOPACKET
#define _IOPACKET

#include "EnumHelper.hpp"

#include <QString>

#include <SFML/Network/Packet.hpp>

class IOPacket {
public:
    enum Mode {
        DESERIALIZE,
        SERIALIZE
    };

    IOPacket(sf::Packet* packet = new sf::Packet(), Mode mode = DESERIALIZE);
    Mode GetMode() const;

    template <typename T> IOPacket& operator & (T& t) {
        if(mMode == DESERIALIZE)
            *mPacket >> t;
        else
            *mPacket << t;
        return *this;
    }

    IOPacket& operator & (EnumHelper h);
    IOPacket& operator & (QString& s);

    sf::Packet& GetPacket();

private:
    sf::Packet* mPacket;
    Mode mMode;
};

#endif
