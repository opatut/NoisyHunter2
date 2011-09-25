#include "Panel.hpp"

Panel::Panel(QString name, sf::Color background)
    : Widget(name),
      mBackground(background) {
    SetBorder(0.f);
}

void Panel::SetBorder(float size, sf::Color color) {
    mBorderSize = size;
    mBorderColor = color;
}

void Panel::Render() {
    mRenderTexture.Clear(mBackground);
    if(mBorderSize > 0) {
        sf::Shape s = sf::Shape::Rectangle(
                    mBorderSize, mBorderSize,
                    mRenderTexture.GetWidth() - 2 * mBorderSize,
                    mRenderTexture.GetHeight() - 2 * mBorderSize,
                    sf::Color(0,0,0,0), mBorderSize, mBorderColor);
        mRenderTexture.Draw(s);
    }
}

