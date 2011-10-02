#ifndef _TORPEDO
#define _TORPEDO

#include "Core/Entity.hpp"

class Torpedo : public Entity {
public:
    Torpedo(QString name, Vector2D position, Vector2D speed, float rotation);

    virtual uint32_t GetTypeId() const;
    virtual Serializable* CreateInstance() const;

    virtual void OnUpdate(float time_diff);
    virtual void OnDraw(sf::RenderTarget& target);

private:
    sf::Sprite mSprite;
};

#endif
