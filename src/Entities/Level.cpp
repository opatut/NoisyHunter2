#include "Level.hpp"

#include <iostream>
#include "Core/Resources.hpp"
#include "Entities/Rock.hpp"

Level::Level(QString name)
    : Entity(name) {
    Generate();
    mInfo = sf::Text("Level 01", Resources::GetInstance().GetDefaultFont());
    mInfo.SetPosition(10, 10);
    mInfo.SetCharacterSize(10);

    Resources::GetInstance().SetTextureSmooth("gfx/tiles.png", false);
    mSprite.SetTexture(Resources::GetInstance().GetTexture("gfx/tiles.png"));
    mTextureTileSize = 64;
    mTextureGridSize = 16;

    SetTileSize(32.f);
    SetGridSize(10, 10);
}

void Level::Serialize(sf::Packet& packet) {
    packet << mGridColumns << mGridRows << mTileSize << mTextureTileSize << mTextureGridSize;
    for(int x = 0; x < mGridColumns; ++x) {
        for(int y = 0; y < mGridColumns; ++y) {
            packet << GetTile(x, y);
        }
    }
}

void Level::Deserialize(sf::Packet& packet) {
    packet >> mGridColumns >> mGridRows >> mTileSize >> mTextureTileSize >> mTextureGridSize;
    for(int x = 0; x < mGridColumns; ++x) {
        for(int y = 0; y < mGridColumns; ++y) {
            int id;
            packet >> id;
            SetTile(x, y, id);
        }
    }
}

Serializable::SerializableType Level::GetType() const {
    return ST_LEVEL;
}

void Level::OnDraw(sf::RenderTarget& target) {
    _RenderTiles(target);
    target.Draw(mInfo);
}

void Level::Generate() {
}

void Level::SetGridSize(int columns, int rows) {
    mGridColumns = columns;
    mGridRows = rows;
    mTiles.resize(columns);
    for(int i = 0; i < columns; ++i) {
        mTiles[i].resize(rows, -1);
    }
}

void Level::SetTileSize(float tile_size) {
    mTileSize = tile_size;
}

void Level::SetTile(int x, int y, int id) {
    if(x >= 0 && x < mGridColumns && y >= 0 && y < mGridRows)
        mTiles[x][y] = id;
    else
        std::cerr << "Cannot set tile " << x << " | " << y << " to " << id << ": position out of grid" << std::endl;
}

int Level::GetTile(int x, int y) {
    return mTiles[x][y];
}

Vector2D Level::GetTileCoordinate(Vector2D window_coordinate) {
    window_coordinate -= GetAbsolutePosition();
    int x = floor(window_coordinate.x / mTileSize);
    int y = floor(window_coordinate.y / mTileSize);
    return Vector2D(x,y);
}

void Level::_RenderTiles(sf::RenderTarget& target) {
    for(int x = 0; x < mGridColumns; ++x) {
        for(int y = 0; y < mGridRows; ++y) {
            _RenderTile(target, x, y, GetTile(x, y));
        }
    }
}

void Level::_RenderTile(sf::RenderTarget& target, int x, int y, int id) {
    if(id == -1)
        return;

    int tx = id % mTextureGridSize;
    int ty = id / mTextureGridSize;

    mSprite.SetScale(mTileSize / mTextureTileSize, mTileSize / mTextureTileSize);
    mSprite.SetPosition(GetAbsolutePosition().x + x * mTileSize, GetAbsolutePosition().y + y * mTileSize);
    mSprite.SetSubRect(sf::IntRect(tx * mTextureTileSize, ty * mTextureTileSize, mTextureTileSize, mTextureTileSize));

    target.Draw(mSprite);
}

