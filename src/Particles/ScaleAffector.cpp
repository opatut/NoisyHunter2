#include "ScaleAffector.hpp"

ScaleAffector::ScaleAffector(float start_scale, float end_scale) {
    mStartScale = start_scale;
    mEndScale = end_scale;
}

void ScaleAffector::ApplyToSprite(sf::Sprite& sprite, Particle* particle) {
    float s = mStartScale + (mEndScale - mStartScale) * particle->GetProgress();
    sprite.Scale(s, s);
}
