#ifndef _TORPEDO
#define _TORPEDO

#include "Entity.hpp"

class Torpedo : public Entity {
public:
    Torpedo(QString name, Vector2D position, Vector2D speed, float rotation);

    virtual void OnUpdate(float time_diff);
    virtual void OnDraw(sf::RenderTarget& target);

private:
    sf::Sprite mSprite;
};

#endif
