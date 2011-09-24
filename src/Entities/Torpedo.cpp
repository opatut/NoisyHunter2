#include "Torpedo.hpp"

#include "Core/Resources.hpp"

Torpedo::Torpedo(QString name, Vector2D position, Vector2D speed, float rotation)
    : Entity(name) {
    mSprite.SetTexture(Resources::GetInstance().GetTexture("gfx/torpedo.png"));
    mSprite.SetOrigin(mSprite.GetSize().x / 2, mSprite.GetSize().y / 2);
    Vector2D shift(0, 20);
    shift.Rotate(rotation);
    Position = position + shift;
    Rotation = rotation;
    Speed = Vector2D(40, 0) + speed;
    Scale(0.3);
}

void Torpedo::OnUpdate(float time_diff) {
    /*if(mLifetime > 0.5) {
        Speed.y = 0;
        Speed.x += 200 * time_diff;
    } else {
        Speed.y *= (1.f - 0.5 * time_diff);
    }*/
    Speed.x += 200 * time_diff;

    if(mLifetime > 2) {
        GetParent()->RemoveChild(this);
        return;
    }


    mSprite.SetPosition(GetAbsolutePosition().x, GetAbsolutePosition().y);
    mSprite.SetRotation(Vector2D::rad2Deg(GetAbsoluteRotation()));
    mSprite.SetScale(GetAbsoluteSize().x, GetAbsoluteSize().y);
}

void Torpedo::OnDraw(sf::RenderTarget& target) {
    target.Draw(mSprite);
}
