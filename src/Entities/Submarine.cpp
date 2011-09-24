#include "Submarine.hpp"

#include "Core/Resources.hpp"

#include <iostream>

Submarine::Submarine(QString name)
    : Entity(name) {
    mSprite.SetTexture(Resources::GetInstance().GetTexture("gfx/submarine.png"));
    mSprite.SetOrigin(mSprite.GetSize().x / 2, mSprite.GetSize().y / 2);
    Position = Vector2D(400, 300);
    mTargetAngle = 0;
    Scale(0.3);
}

void Submarine::OnUpdate(float time_diff) {
    int rot_inv = (Speed.x < 0 ? -1 : 1);
    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::W)) {
        mTargetAngle -= time_diff * 1 * rot_inv;
    }
    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::S)) {
        mTargetAngle += time_diff * 1 * rot_inv;
    }
    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::D)) {
        Accelerate(Vector2D(1, 0));
    }
    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::A)) {
        Accelerate(Vector2D(-1, 0));
    }

    /* if((rot_inv == -1 && Speed.x > 0) || (rot_inv == 1 && Speed.x < 0)) {
        // we turned around
        mTargetAngle *= -1;
        Rotation *= -1;
    } */

    if(mTargetAngle > 0.5) mTargetAngle = 0.5;
    if(mTargetAngle < -0.5) mTargetAngle = -0.5;

    float diff = mTargetAngle - Rotation;
    Rotation += diff * time_diff;

    mSprite.FlipX(Speed.x < 0);

    Speed *= (1.f - 0.5 * time_diff);

    mSprite.SetPosition(GetAbsolutePosition().x, GetAbsolutePosition().y);
    mSprite.SetRotation(Vector2D::rad2Deg(GetAbsoluteRotation()));
    mSprite.SetScale(GetAbsoluteSize().x, GetAbsoluteSize().y);
}

void Submarine::OnDraw(sf::RenderTarget& target) {
    target.Draw(mSprite);
}
