#ifndef _BACKGROUND_GRADIENT
#define _BACKGROUND_GRADIENT

#include "Core/Entity.hpp"

class BackgroundGradient : public Entity {
public:
    BackgroundGradient(QString name);

    virtual uint32_t GetTypeId() const;
    virtual Serializable* CreateInstance() const;

    void SetColors(sf::Color top, sf::Color bottom);
    void OnDraw(sf::RenderTarget& target);

private:
    sf::Shape mShape;
};

#endif
