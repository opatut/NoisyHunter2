#ifndef _SERIALIZER
#define _SERIALIZER

#include <QString>
#include <map>
#include <cstdint>
#include "Core/Serializable.hpp"

class Serializer {
public:
    // performs the following:
    // - read ID from data
    // - create Serializable from that ID
    // - let the Serializable read itself
    //   - if the serializable has children, this will be called again
    // - returns the Serializable, leaves the rest of binary data in the packet
    static Serializable* Load(sf::Packet& data);

    // performs the following:
    // - writes the ID into data
    // - serializes the serializable's data into data
    //   - if the serializable has children, this will be called again
    static void Write(sf::Packet& data, Serializable* serializable);

    static void AddPrototype(Serializable* prototype);

    static sf::Packet ReadFileContents(QString filename);
    static void WriteFileContents(QString filename, sf::Packet& data);
private:
    static std::map<uint32_t, Serializable*>& _GetPrototypes();

    static Serializable* _CreateSerializableForId(uint32_t id);

};

#endif
