#include "Particle.hpp"

Particle::Particle(QString name, ParticleSystem* particle_system, float particle_lifetime, Vector2D position, float angle, float speed)
    : Entity(name, position) {
    mParticleSystem = particle_system;
    mParticleLifetime = particle_lifetime;

    Speed = Vector2D(speed, 0);
    Speed.Rotate(angle);
}

uint32_t Particle::GetTypeId() const {
    return ET_UNKNOWN;
}

Serializable* Particle::CreateInstance() const {
    return nullptr;
}

void Particle::OnUpdate(float time_diff) {
    mParticleSystem->UpdateParticle(time_diff, this);

    if(GetProgress() > 1.f) {
        // destroy self
        GetParent()->RemoveChild(this);
    }
}

void Particle::OnDraw(sf::RenderTarget& target) {
    sf::Sprite s = mParticleSystem->GetSpriteForParticle(this);
    s.SetOrigin(s.GetSize().x / s.GetScale().x / 2, s.GetSize().y / s.GetScale().y / 2);
    s.SetPosition(GetAbsolutePosition().x, GetAbsolutePosition().y);
    target.Draw(s);
}

float Particle::GetProgress() {
    return mLifetime / mParticleLifetime;
}
