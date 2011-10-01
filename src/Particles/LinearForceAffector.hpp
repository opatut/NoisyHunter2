#ifndef _LINEAR_FORCE_AFFECTOR
#define _LINEAR_FORCE_AFFECTOR

#include "ParticleAffector.hpp"

class LinearForceAffector : public ParticleAffector {
public:
    LinearForceAffector(Vector2D force);
    virtual void ApplyToParticle(float time_diff, Particle* particle);

private:
    Vector2D mForce;
};

#endif
