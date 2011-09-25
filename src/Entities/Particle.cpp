#include "Particle.hpp"

Particle::Particle(QString name, ParticleSystem* particle_system, float particle_lifetime, Vector2D position)
    : Entity(name, position) {
    mParticleSystem = particle_system;
    mParticleLifetime = particle_lifetime;
}

void Particle::OnUpdate(float time_diff) {
    if(mLifetime > mParticleLifetime) {
        // destroy self
        GetParent()->RemoveChild(this);
    }
}

void Particle::OnDraw(sf::RenderTarget& target) {
    sf::Sprite& s = mParticleSystem->GetParticleSprite();
    s.SetPosition(GetAbsolutePosition().x, GetAbsolutePosition().y);
    target.Draw(s);
}
