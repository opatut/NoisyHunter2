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

void Panel::Render(sf::RenderTarget& target) {
    sf::Shape s = sf::Shape::Rectangle(
        mBorderSize, mBorderSize,
        Size.x - 2 * mBorderSize,
        Size.y - 2 * mBorderSize,
        mBackground, mBorderSize, mBorderColor);
    target.Draw(s);
}

void Panel::SetBackground(sf::Color background) {
    mBackground = background;
}
