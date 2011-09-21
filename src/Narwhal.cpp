#include "Narwhal.hpp"

#include "Resources.hpp"

Narwhal::Narwhal(QString name)
    : Entity(name) {
    mSprite.SetTexture(Resources::GetInstance().GetTexture("gfx/narwhal.png"));
    mSprite.SetOrigin(mSprite.GetSize().x / 2, mSprite.GetSize().y / 2);
    Position.y = 500;
    Position.x = 700;
    Speed.x = 30;
    Scale(0.3);
}

void Narwhal::OnUpdate(float time_diff) {
    Rotation = sin(mLifetime) * 0.3;

    if(Speed.x > 0 && Position.x > 800)
        Speed.x *= -1;

    if(Speed.x < 0 && Position.x < 0)
        Speed.x *= -1;

    mSprite.FlipX(Speed.x < 0);

    mSprite.SetPosition(GetAbsolutePosition().x, GetAbsolutePosition().y);
    mSprite.SetRotation(Vector2D::rad2Deg(GetAbsoluteRotation()));
    mSprite.SetScale(GetAbsoluteSize().x, GetAbsoluteSize().y);
}

void Narwhal::OnDraw(sf::RenderTarget& target) {
    target.Draw(mSprite);
}
