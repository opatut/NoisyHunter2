#ifndef _LEVEL
#define _LEVEL

#include "Core/Entity.hpp"
#include "Core/Serializable.hpp"
#include <map>

class Level : public Entity, public Serializable {
public:
    Level(QString name);

    virtual void Serialize(sf::Packet& packet);
    virtual void Deserialize(sf::Packet& packet);
    virtual SerializableType GetType() const;

    virtual void OnDraw(sf::RenderTarget& target);

    void Generate();

    void SetGridSize(int columns, int rows);
    void SetTileSize(float tile_size);

    void SetTile(int x, int y, int id);
    int GetTile(int x, int y);

    Vector2D GetTileCoordinate(Vector2D window_coordinate);


private:
    void _RenderTiles(sf::RenderTarget& target);
    void _RenderTile(sf::RenderTarget& target, int x, int y, int id);

    sf::Sprite mSprite;
    sf::Text mInfo;

    int mGridColumns;
    int mGridRows;
    float mTileSize;

    float mTextureTileSize;
    int mTextureGridSize;

    std::vector<std::vector<int> > mTiles;
};

#endif
