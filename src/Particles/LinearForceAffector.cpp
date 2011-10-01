#include "LinearForceAffector.hpp"

LinearForceAffector::LinearForceAffector(Vector2D force) {
    mForce = force;
}

void LinearForceAffector::ApplyToParticle(float time_diff, Particle* particle) {
    particle->Accelerate(mForce * time_diff);
}
