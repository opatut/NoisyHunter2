#ifndef _SUBMARINE
#define _SUBMARINE

#include "Core/Entity.hpp"

#include "Particles/ParticleSystem.hpp"

class Submarine : public Entity {
public:
    Submarine(QString name);

    virtual void OnUpdate(float time_diff);
    virtual void OnDraw(sf::RenderTarget& target);

private:
    sf::Sprite mSprite;

    float mTargetAngle;
    ParticleSystem* mBubbles;
};

#endif
