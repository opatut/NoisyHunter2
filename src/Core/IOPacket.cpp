#include "IOPacket.hpp"

IOPacket::IOPacket(sf::Packet* packet, Mode mode)
    : mPacket(packet),
      mMode(mode) {}

IOPacket::Mode IOPacket::GetMode() const {
    return mMode;
}

IOPacket& IOPacket::operator & (EnumHelper h) {
    if(mMode == DESERIALIZE)
        *mPacket >> h;
    else
        *mPacket << h;
    return *this;
}

IOPacket& IOPacket::operator & (QString& s) {
    if(mMode == DESERIALIZE) {
        std::string stdstr;
        *mPacket >> stdstr;
        s = QString(stdstr.c_str());
    } else {
        *mPacket << s.toStdString();
    }
    return *this;
}

sf::Packet& IOPacket::GetPacket() {
    return *mPacket;
}
