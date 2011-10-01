#ifndef _GRAPHICS_BUTTON
#define _GRAPHICS_BUTTON

#include "Gui/Button.hpp"

class GraphicsButton : public Button {
public:
    GraphicsButton(QString name, QString caption = "", sf::Sprite sprite = sf::Sprite(), bool show_background = false);
    virtual void Render(sf::RenderTarget& target);

    void SetSprite(const sf::Sprite& sprite);
    void SetShowBackground(bool show);

private:
    sf::Sprite mSprite;
    bool mShowBackground;

};

#endif
