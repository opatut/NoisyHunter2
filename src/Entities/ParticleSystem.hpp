#ifndef _PARTICLE_SYSTEM
#define _PARTICLE_SYSTEM

#include <QString>
#include <SFML/Graphics.hpp>
#include "Core/Entity.hpp"

class ParticleSystem: public Entity {
public:
    ParticleSystem(QString name, Vector2D position = Vector2D(), float rate = 1.f, float particle_lifetime = 1.f);

    virtual void OnUpdate(float time_diff);

    // to modify particle settings
    sf::Sprite& GetParticleSprite();

    void SetRate(float rate);
    float GetRate();

    void SetParticleLifetime(float particle_lifetime);
    float GetParticleLifetime();

private:
    void _SpawnParticle();

    // bool mKeepRelative;
    float mRate;
    float mParticleLifetime;

    float mTimeUntilNextParticle;

    sf::Sprite mParticleSprite;
};

#endif
