#include "Tile.hpp"

#include "Core/Resources.hpp"

Tile::Tile(int id)
    : Entity("tile-" + Resources::GetInstance().GetNextID()) {
    mTileId = id;
    mSprite.SetTexture(Resources::GetInstance().GetTexture("gfx/tiles.png"));
    int tx = id % 16;
    int ty = id / 16;
    mSprite.SetSubRect(sf::IntRect(tx * 64, ty * 64, 64, 64));
    mSprite.SetScale(0.5, 0.5);
}


void Tile::OnUpdate(float time_diff) {
    mSprite.SetPosition(Position.x, Position.y);
}

void Tile::OnDraw(sf::RenderTarget& target) {
    target.Draw(mSprite);
}
