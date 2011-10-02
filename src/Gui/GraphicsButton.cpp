#include "GraphicsButton.hpp"

GraphicsButton::GraphicsButton(QString name, QString caption, sf::Sprite sprite, bool show_background)
    : Button(name, caption) {
    mSprite = sprite;
    mShowBackground = show_background;
}

void GraphicsButton::Render(sf::RenderTarget& target) {
    if(mShowBackground) {
        mBackground.SetPosition(GetAbsolutePosition().x, GetAbsolutePosition().y);
        mBackground.SetScale(Size.x, Size.y);
        mBackground.SetSubRect(sf::IntRect(0, (HasFocus() ? 40 : 0), 200, 40));
        target.Draw(mBackground);
    }

    // draw the sprite
    mSprite.SetPosition(GetAbsolutePosition().x, GetAbsolutePosition().y);
    mSprite.SetScale(Size.x / mSprite.GetSubRect().Width, Size.y / mSprite.GetSubRect().Height);
    target.Draw(mSprite);

    // draw the text
    mText.SetColor(sf::Color::White);
    mText.SetPosition(round(GetAbsolutePosition().x + Size.x / 2 - mText.GetRect().Width / 2), round(GetAbsolutePosition().y + Size.y / 2 - mText.GetRect().Height / 2));
    target.Draw(mText);

    if(!mShowBackground && IsHover()) {
       sf::Shape highlight = sf::Shape::Rectangle(GetAbsolutePosition().x, GetAbsolutePosition().y, Size.x, Size.y, sf::Color(255,255,255,100));
       target.Draw(highlight);
   }
}

void GraphicsButton::SetSprite(const sf::Sprite& sprite) {
    mSprite = sprite;
}

void GraphicsButton::SetShowBackground(bool show) {
    mShowBackground = show;
}
