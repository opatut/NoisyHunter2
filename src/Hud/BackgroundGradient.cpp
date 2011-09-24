#include "BackgroundGradient.hpp"

BackgroundGradient::BackgroundGradient(QString name)
    : Entity(name) {
    SetColors(sf::Color(10, 70, 130), sf::Color(4, 20, 50));
    // SetColors(sf::Color(30, 90, 170), sf::Color(0, 10, 20));
}

void BackgroundGradient::SetColors(sf::Color top, sf::Color bottom) {
    mShape = sf::Shape();
    mShape.AddPoint(0, 0, top);
    mShape.AddPoint(800, 0, top);
    mShape.AddPoint(800, 600, bottom);
    mShape.AddPoint(0, 600, bottom);
    mShape.SetOutlineThickness(0.f);
}

void BackgroundGradient::OnDraw(sf::RenderTarget& target) {
    target.Draw(mShape);
}
