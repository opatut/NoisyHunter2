#ifndef _ROCK
#define _ROCK

#include "Core/Entity.hpp"

class Rock : public Entity {
public:
    Rock(QString name, QString type = "01");

    virtual void Serialize(IOPacket& packet);
    virtual uint32_t GetTypeId() const;
    virtual Serializable* CreateInstance() const;

    virtual void OnUpdate(float time_diff);
    virtual void OnDraw(sf::RenderTarget& target);

    void Explode();

private:
    QString mType;
    sf::Sprite mSprite;

};

#endif
