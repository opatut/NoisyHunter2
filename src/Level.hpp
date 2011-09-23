#ifndef _LEVEL
#define _LEVEL

#include "Entity.hpp"

class Level : public Entity {
public:
    Level(QString name);

    virtual void OnDraw(sf::RenderTarget& target);

    void Generate();

private:
    sf::Text mInfo;
    sf::Sprite mSprite;

};

#endif
