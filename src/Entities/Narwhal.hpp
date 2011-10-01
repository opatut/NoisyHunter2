#ifndef _NARWHAL
#define _NARWHAL

#include "Core/Entity.hpp"

class Narwhal : public Entity {
public:
    Narwhal(QString name);

    virtual void OnUpdate(float time_diff);
    virtual void OnDraw(sf::RenderTarget& target);

private:
    void _PlaceRandom();
    sf::Sprite mSprite;
};

#endif
