#include "ParticleSystem.hpp"

#include "Core/Resources.hpp"
#include "Particle.hpp"

ParticleSystem::ParticleSystem(QString name, Vector2D position, float rate, float particle_lifetime)
    : Entity(name, position) {
    SetRate(rate);
    SetParticleLifetime(particle_lifetime);
}

void ParticleSystem::OnUpdate(float time_diff) {
    mTimeUntilNextParticle -= time_diff;

    while(mTimeUntilNextParticle <= 0) {
        _SpawnParticle();
        mTimeUntilNextParticle += 1 / mRate;
    }
}

sf::Sprite& ParticleSystem::GetParticleSprite() {
    return mParticleSprite;
}

void ParticleSystem::SetRate(float rate) {
    mRate = rate;
}

float ParticleSystem::GetRate() {
    return mRate;
}

void ParticleSystem::SetParticleLifetime(float particle_lifetime) {
    mParticleLifetime = particle_lifetime;
}

float ParticleSystem::GetParticleLifetime() {
    return mParticleLifetime;
}

void ParticleSystem::_SpawnParticle() {
    // get topmost parent
    Entity* p = this;
    while(p->GetParent() != nullptr)
        p = p->GetParent();

    p->AddChild(new Particle(GetName() + "-particle-" + Resources::GetInstance().GetNextID(), this, mParticleLifetime, GetAbsolutePosition() - p->GetAbsolutePosition()));
}
