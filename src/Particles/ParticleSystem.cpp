#include "ParticleSystem.hpp"

#include "Core/Resources.hpp"
#include "Particle.hpp"
#include "ParticleAffector.hpp"

ParticleSystem::ParticleSystem(QString name, Vector2D position, float rate, Range<float> particle_lifetime)
    : Entity(name, position) {
    SetRate(rate);
    SetParticleLifetime(particle_lifetime);
}

void ParticleSystem::OnUpdate(float time_diff) {
    if(mRate > 0) {
        mTimeSinceLastParticle += time_diff;

        while(mTimeSinceLastParticle > 1 / mRate) {
            _SpawnParticle();
            mTimeSinceLastParticle -= 1 / mRate;
        }
    }
}

void ParticleSystem::AddAffector(ParticleAffector* affector) {
    mParticleAffectors.push_back(affector);
}

sf::Sprite& ParticleSystem::GetParticleSprite() {
    return mParticleSprite;
}

sf::Sprite ParticleSystem::GetSpriteForParticle(Particle* particle) {
    sf::Sprite sprite(mParticleSprite);
    for(auto iter = mParticleAffectors.begin(); iter != mParticleAffectors.end(); ++iter) {
        (*iter)->ApplyToSprite(sprite, particle);
    }
    return sprite;
}

void ParticleSystem::UpdateParticle(float time_diff, Particle* particle) {
    for(auto iter = mParticleAffectors.begin(); iter != mParticleAffectors.end(); ++iter) {
        (*iter)->ApplyToParticle(time_diff, particle);
    }
}

void ParticleSystem::SetRate(float rate) {
    mRate = rate;
}

float ParticleSystem::GetRate() {
    return mRate;
}

void ParticleSystem::SetParticleLifetime(Range<float> particle_lifetime) {
    mParticleLifetime = particle_lifetime;
}

Range<float> ParticleSystem::GetParticleLifetime() {
    return mParticleLifetime;
}

void ParticleSystem::_SpawnParticle() {
    // get topmost parent
    Entity* p = this;
    while(p->GetParent() != nullptr)
        p = p->GetParent();

    p->AddChild(new Particle(GetName() + "-particle-" + Resources::GetInstance().GetNextID(), this, mParticleLifetime.GetRandom(),
                             GetAbsolutePosition() - p->GetAbsolutePosition(), InitialParticleAngle.GetRandom(), InitialParticleSpeed.GetRandom()));
}
