#include "TiledSprite.hpp"

#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>

TiledSprite::TiledSprite() {
    SetSubRect(sf::IntRect(0,0,1,1));
}

TiledSprite::TiledSprite(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& scale,
                         const float rotation, const sf::Color& color) {
    SetTexture(texture);
    SetPosition(position);
    SetScale(scale);
    SetRotation(rotation);
    SetColor(color);
    SetSubRect(sf::IntRect(0,0,1,1));
}

void TiledSprite::Render(sf::RenderTarget&, sf::Renderer& renderer) const {
    const sf::Texture* texture = GetTexture();
    const sf::IntRect& sub_rect = GetSubRect();

    // Get the sprite size
    float width  = static_cast<float>(sub_rect.Width);
    float height = static_cast<float>(sub_rect.Height);
    float tex_x= static_cast<float>(sub_rect.Left);
    float tex_y = static_cast<float>(sub_rect.Top);
    float subw = width / 3;  // 8
    float subh = height / 3; // 8
    float sw = GetScale().x; // 200
    float sh = GetScale().y; // 30

    // Check if the image is valid
    if(texture) {
        // Bind the texture
        renderer.SetTexture(texture);

        // 9 subrects
        for(int x = 0; x < 3; x++) {
            for(int y = 0; y < 3; y++) {
                // Calculate the texture coordinates
                sf::FloatRect tc = texture->GetTexCoords(sf::IntRect(x * subw + tex_x, y * subh + tex_y, subw, subh));

                float left = 0, top = 0, right = 0, bottom = 0;
                float hp = subw/sw;
                float vp = subh/sh;

                if(x == 0)      { left = 0;     right = hp;     }
                else if(x == 1) { left = hp;    right = 1-hp;   }
                else if(x == 2) { left = 1-hp;  right = 1;      }

                if(y == 0)      { top = 0;      bottom = vp;    }
                else if(y == 1) { top = vp;     bottom = 1-vp;  }
                else if(y == 2) { top = 1-vp;   bottom = 1;     }

                // Draw the sprite's geometry
                renderer.Begin(sf::Renderer::TriangleStrip);
                renderer.AddVertex(left,    top,      tc.Left,              tc.Top);
                renderer.AddVertex(right,   top,      tc.Left + tc.Width,   tc.Top);
                renderer.AddVertex(left,    bottom,   tc.Left,              tc.Top + tc.Height);
                renderer.AddVertex(right,   bottom,   tc.Left + tc.Width,   tc.Top + tc.Height);
                renderer.End();
            }
        }
    }
}
