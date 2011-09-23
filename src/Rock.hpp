#ifndef _ROCK
#define _ROCK

#include "Entity.hpp"

class Rock : public Entity {
public:
    Rock(QString name, QString type = "01");

    virtual void OnUpdate(float time_diff);
    virtual void OnDraw(sf::RenderTarget& target);

    void Explode();

private:
    QString mType;
    sf::Sprite mSprite;

};

#endif
