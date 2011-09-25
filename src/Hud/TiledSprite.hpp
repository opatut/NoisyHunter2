#ifndef _TILED_SPRITE
#define _TILED_SPRITE

#include <SFML/Graphics.hpp>
#include <SFML/System/Resource.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>

class TiledSprite : public sf::Sprite {
public:
    TiledSprite();

    explicit TiledSprite(const sf::Texture& texture,
                         const sf::Vector2f& position = sf::Vector2f(0, 0),
                         const sf::Vector2f& scale = sf::Vector2f(1, 1),
                         const float rotation = 0.f,
                         const sf::Color& color = sf::Color(255, 255, 255, 255));
protected:
    void Render(sf::RenderTarget&, sf::Renderer& renderer) const;
};

#endif
