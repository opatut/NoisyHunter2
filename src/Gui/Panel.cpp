#include "Panel.hpp"

Panel::Panel(QString name)
    : Widget(name) {}

void Panel::Render() {
    mRenderTexture.Clear(sf::Color(120, 120, 120, 230));
}

