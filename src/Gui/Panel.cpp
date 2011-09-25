#include "Panel.hpp"

Panel::Panel(QString name, sf::Color background)
    : Widget(name),
      mBackground(background) {}

void Panel::Render() {
    mRenderTexture.Clear(mBackground);
}

