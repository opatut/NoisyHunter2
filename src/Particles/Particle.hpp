#ifndef _PARTICLE
#define _PARTICLE

#include <QString>
#include <SFML/Graphics.hpp>
#include "Core/Entity.hpp"
#include "ParticleSystem.hpp"

class Particle : public Entity {
public:
    Particle(QString name, ParticleSystem* particle_system, float particle_lifetime, Vector2D position = Vector2D(), float angle = 0.f, float speed = 0.f);

    virtual uint32_t GetTypeId() const;
    virtual Serializable* CreateInstance() const;

    virtual void OnUpdate(float time_diff);
    virtual void OnDraw(sf::RenderTarget& target);

    float GetProgress();

private:
    ParticleSystem* mParticleSystem;
    float mParticleLifetime;

};

#endif
