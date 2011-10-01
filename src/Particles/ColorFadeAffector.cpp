#include "ColorFadeAffector.hpp"

ColorFadeAffector::ColorFadeAffector(sf::Color start_color, sf::Color end_color) {
    mStartColor = start_color;
    mEndColor = end_color;
}

void ColorFadeAffector::ApplyToSprite(sf::Sprite& sprite, Particle* particle) {
    sprite.SetColor(sf::Color(
                        mStartColor.r + (mEndColor.r - mStartColor.r) * particle->GetProgress(),
                        mStartColor.g + (mEndColor.g - mStartColor.g) * particle->GetProgress(),
                        mStartColor.b + (mEndColor.b - mStartColor.b) * particle->GetProgress(),
                        mStartColor.a + (mEndColor.a - mStartColor.a) * particle->GetProgress()));
}
