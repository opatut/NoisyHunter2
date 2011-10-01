#ifndef _SCALE_AFFECTOR
#define _SCALE_AFFECTOR

#include "ParticleAffector.hpp"

class ScaleAffector : public ParticleAffector {
public:
    ScaleAffector(float start_scale, float end_scale);
    virtual void ApplyToSprite(sf::Sprite& sprite, Particle* particle);

private:
    float mStartScale;
    float mEndScale;
};

#endif
