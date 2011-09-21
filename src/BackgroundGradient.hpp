#ifndef _BACKGROUND_GRADIENT
#define _BACKGROUND_GRADIENT

#include "Entity.hpp"

class BackgroundGradient : public Entity {
public:
    BackgroundGradient(QString name);
    void SetColors(sf::Color top, sf::Color bottom);
    void OnDraw(sf::RenderTarget& target);

private:
    sf::Shape mShape;
};

#endif
