#include "Submarine.hpp"

#include "Core/Resources.hpp"
#include "Core/Input.hpp"
#include "Particles/ScaleAffector.hpp"
#include "Particles/ColorFadeAffector.hpp"
#include "Particles/LinearForceAffector.hpp"
#include <iostream>

Submarine::Submarine(QString name)
    : Entity(name) {
    mSprite.SetTexture(Resources::GetInstance().GetTexture("gfx/submarine.png"));
    mSprite.SetOrigin(mSprite.GetSize().x / 2, mSprite.GetSize().y / 2);
    Position = Vector2D(Input::GetInstance().GetDefaultWindow().GetWidth() / 2, Input::GetInstance().GetDefaultWindow().GetHeight() / 2);
    mTargetAngle = 0;
    Scale(0.3);

    // add particle system at rear
    mBubbles = new ParticleSystem("rear-bubbles", Vector2D(-50, 0), 20.f, 10.f);
    mBubbles->GetParticleSprite().SetTexture(Resources::GetInstance().GetTexture("gfx/bubbles-01.png"));
    mBubbles->AddAffector(new ScaleAffector(0.1, 2.f));
    mBubbles->AddAffector(new ColorFadeAffector(sf::Color(255, 255, 255, 100), sf::Color(200, 200, 255, 0)));
    mBubbles->AddAffector(new LinearForceAffector(Vector2D(0, -5.f)));
    mBubbles->InitialParticleAngle.Set(Vector2D::deg2Rad(-180), Vector2D::deg2Rad(180));
    mBubbles->InitialParticleSpeed.Set(0, 5);
    mBubbles->SetRate(0.f);
    AddChild(mBubbles);
}

void Submarine::OnUpdate(float time_diff) {
    mBubbles->SetRate(abs(Speed.x) * 0.1);

    int rot_inv = (Speed.x < 0 ? -1 : 1);
    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::W)) {
        mTargetAngle -= time_diff * 0.8 * rot_inv;
    } else if(sf::Keyboard::IsKeyPressed(sf::Keyboard::S)) {
        mTargetAngle += time_diff * 0.8 * rot_inv;
    } else {
        mTargetAngle *= (1 - 0.8 * time_diff);
    }
    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::D)) {
        Accelerate(Vector2D(40 * time_diff, 0));
    }
    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::A)) {
        Accelerate(Vector2D(-40 * time_diff, 0));
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

    Speed *= (1.f - 0.4 * time_diff);

    mSprite.SetPosition(GetAbsolutePosition().x, GetAbsolutePosition().y);
    mSprite.SetRotation(Vector2D::rad2Deg(GetAbsoluteRotation()));
    mSprite.SetScale(GetAbsoluteSize().x, GetAbsoluteSize().y);
}

void Submarine::OnDraw(sf::RenderTarget& target) {
    target.Draw(mSprite);
}
