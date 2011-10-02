#include "Serializer.hpp"

#include <iostream>
#include <QFile>
#include <QDataStream>

#include "Globals.hpp"

Serializable* Serializer::Load(sf::Packet& data) {
    uint32_t id;
    data >> id;

    std::cout << "Loading ... " << id << std::endl;

    Serializable* s = _CreateSerializableForId(id);
    if(s != nullptr) {
        IOPacket p(&data, IOPacket::DESERIALIZE);
        s->Serialize(p);
    }

    return s;
}

void Serializer::Write(sf::Packet& data, Serializable* serializable) {
    // performs the following:
    // - writes the ID into data
    // - serializes the serializable's data into data
    //   - if the serializable has children, this will be called again

    if(serializable->GetTypeId() != ET_UNKNOWN) {
        data << serializable->GetTypeId();
        IOPacket p(&data, IOPacket::SERIALIZE);
        serializable->Serialize(p);
    }
}

void Serializer::AddPrototype(Serializable* prototype) {
    uint32_t id = prototype->GetTypeId();
    if(_GetPrototypes().count(id) > 0) {

        std::cerr << "Warning: cannot add prototype of already registered ID " << id << "." << std::endl;
    } else {
        _GetPrototypes().insert(std::pair<uint32_t, Serializable*>(prototype->GetTypeId(), prototype));
    }
}

std::map<uint32_t, Serializable*>& Serializer::_GetPrototypes() {
    static std::map<uint32_t, Serializable*> instance;
    return instance;
}

Serializable* Serializer::_CreateSerializableForId(uint32_t id) {
    if(_GetPrototypes().count(id) == 0) {
        std::cerr << "Error: cannot find prototype of ID " << id << "." << std::endl;
        return nullptr;
    }

    return _GetPrototypes().find(id)->second->CreateInstance();
}

sf::Packet Serializer::ReadFileContents(QString filename) {
    sf::Packet p;

    QFile file(filename);
    file.open(QFile::ReadOnly);
    p << file.readAll().data();
    std::cout << "length: " << p.GetDataSize() << std::endl;
    file.close();
    return p;
}

void Serializer::WriteFileContents(QString filename, sf::Packet& data) {
    QFile file(filename);
    file.open(QFile::WriteOnly);
    file.write(data.GetData(), data.GetDataSize());
    file.close();
}
