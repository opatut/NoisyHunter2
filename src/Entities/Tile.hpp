#ifndef _TILE
#define _TILE

#include "Core/Entity.hpp"

class Tile : public Entity {
public:
    Tile(int id);

    virtual void OnUpdate(float time_diff);
    virtual void OnDraw(sf::RenderTarget& target);

private:
    int mTileId;
    sf::Sprite mSprite;

};

#endif
