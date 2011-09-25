#ifndef _PARTICLE
#define _PARTICLE

#include <QString>
#include <SFML/Graphics.hpp>
#include "Core/Entity.hpp"
#include "Entities/ParticleSystem.hpp"

class Particle : public Entity {
public:
    Particle(QString name, ParticleSystem* particle_system, float particle_lifetime, Vector2D position = Vector2D());

    virtual void OnUpdate(float time_diff);
    virtual void OnDraw(sf::RenderTarget& target);

private:
    ParticleSystem* mParticleSystem;
    float mParticleLifetime;

};

#endif
