#ifndef _COLOR_FADE_AFFECTOR
#define _COLOR_FADE_AFFECTOR

#include "ParticleAffector.hpp"

class ColorFadeAffector : public ParticleAffector {
public:
    ColorFadeAffector(sf::Color start_color, sf::Color end_color);
    virtual void ApplyToSprite(sf::Sprite& sprite, Particle* particle);

private:
    sf::Color mStartColor;
    sf::Color mEndColor;
};

#endif
