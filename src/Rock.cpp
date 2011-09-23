#include "Rock.hpp"

#include "Resources.hpp"
#include "Torpedo.hpp"

Rock::Rock(QString name, QString type)
    : Entity(name) {
    mType = type;
    // load image
    mSprite.SetTexture(Resources::GetInstance().GetTexture("gfx/rocks-" + type + ".png"));
    mSprite.SetOrigin(mSprite.GetTexture()->GetWidth() / 2, mSprite.GetTexture()->GetHeight() / 2);
    Scale(0.3);
}

void Rock::OnUpdate(float time_diff) {
    mSprite.SetPosition(GetAbsolutePosition().x, GetAbsolutePosition().y);
    mSprite.SetRotation(Vector2D::rad2Deg(GetAbsoluteRotation()));
    mSprite.SetScale(GetAbsoluteSize().x, GetAbsoluteSize().y);
}

void Rock::OnDraw(sf::RenderTarget& target) {
    target.Draw(mSprite);
}

void Rock::Explode() {
    // add "test particle"
    GetParent()->AddChild(new Torpedo("torpedo-lol", Position, Vector2D(100,0), 5));

    // kill yourself !
    GetParent()->RemoveChild(this);
}
