#ifndef _PARTICLE_AFFECTOR
#define _PARTICLE_AFFECTOR

#include "Particle.hpp"

class ParticleAffector {
public:
    ParticleAffector();
    virtual void ApplyToParticle(float time_diff, Particle* particle);
    virtual void ApplyToSprite(sf::Sprite& sprite, Particle* particle);

};

#endif
