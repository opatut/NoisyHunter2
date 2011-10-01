#ifndef _PARTICLE_SYSTEM
#define _PARTICLE_SYSTEM

#include <QString>
#include <SFML/Graphics.hpp>
#include "Core/Entity.hpp"
#include "Core/Range.hpp"

class ParticleAffector;
class Particle;

class ParticleSystem: public Entity {
public:
    ParticleSystem(QString name, Vector2D position = Vector2D(), float rate = 1.f, Range<float> particle_lifetime = 1.f);

    virtual void OnUpdate(float time_diff);

    void AddAffector(ParticleAffector* affector);

    // to modify particle settings
    sf::Sprite& GetParticleSprite();
    sf::Sprite GetSpriteForParticle(Particle* particle);
    void UpdateParticle(float time_diff, Particle* particle);

    void SetRate(float rate);
    float GetRate();

    void SetParticleLifetime(Range<float> particle_lifetime);
    Range<float> GetParticleLifetime();

    Range<float> InitialParticleSpeed;
    Range<float> InitialParticleAngle;

private:
    void _SpawnParticle();

    // bool mKeepRelative;
    float mRate;
    Range<float> mParticleLifetime;

    float mTimeSinceLastParticle;

    std::vector<ParticleAffector*> mParticleAffectors;

    sf::Sprite mParticleSprite;
};

#endif
