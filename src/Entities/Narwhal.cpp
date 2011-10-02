#include "Narwhal.hpp"

#include "Core/Resources.hpp"
#include "Core/Random.hpp"
#include "Core/Input.hpp"

Narwhal::Narwhal(QString name)
    : Entity(name) {

    mSprite.SetTexture(Resources::GetInstance().GetTexture("gfx/narwhal.png"));
    mSprite.SetOrigin(mSprite.GetSize().x / 2, mSprite.GetSize().y / 2);

    _PlaceRandom();

    Scale(Random::Get(0.3f, 0.5f));

    mLifetime += Random::Get(0.f, 2 * PI);
}

uint32_t Narwhal::GetTypeId() const {
    return ET_NARWHAL;
}

Serializable* Narwhal::CreateInstance() const {
    return new Narwhal(GetName());
}

void Narwhal::OnUpdate(float time_diff) {

    if(Speed.x > 0 && Position.x > Input::GetInstance().GetDefaultWindow().GetWidth() + 100) {
        _PlaceRandom();
    } else if(Speed.x < 0 && Position.x < - 100) {
        _PlaceRandom();
    }

    // Rotation = (mTarget - Position).Rotation();
    // if(Rotation > PI) Rotation = 2 * PI - Rotation;

    Rotation = Vector2D::deg2Rad(sin(mLifetime * Size.x) * 30);

    mSprite.FlipX(Speed.x < 0);

    mSprite.SetPosition(GetAbsolutePosition().x, GetAbsolutePosition().y);
    mSprite.SetRotation(Vector2D::rad2Deg(GetAbsoluteRotation()));
    mSprite.SetScale(GetAbsoluteSize().x, GetAbsoluteSize().y);
}

void Narwhal::OnDraw(sf::RenderTarget& target) {
    target.Draw(mSprite);
}

void Narwhal::_PlaceRandom() {
    Position.x = - Random::Get(100.f, Input::GetInstance().GetDefaultWindow().GetWidth());
    Position.y = Random::Get(20.f, Input::GetInstance().GetDefaultWindow().GetHeight() - 20);
    Speed = Random::Get(10.f, 30.f);
    if(Random::GetBool()) {
        Position.x = Input::GetInstance().GetDefaultWindow().GetWidth() - Position.x;
        Speed *= -1;
    }
}
