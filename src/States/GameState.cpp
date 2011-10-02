#include "GameState.hpp"

#include <iostream>

#include "Core/Resources.hpp"
#include "Core/Input.hpp"
#include "Core/Serializer.hpp"
#include "Hud/Text.hpp"
#include "Entities/Level.hpp"
#include "Entities/Narwhal.hpp"
#include "Hud/BackgroundGradient.hpp"
#include "Entities/Torpedo.hpp"

GameState::GameState() {
    mScene = new Entity("scene");
    mScene->AddChild(new BackgroundGradient("background"));
    mSubmarine = new Submarine("submarine");
    mScene->AddChild(mSubmarine);

    mScene->AddChild(new Narwhal("narwhal-01"));

    Level* l = new Level("level");

    l->SetTile(1, 1, 0);
    l->SetTile(2, 1, 1);
    l->SetTile(3, 1, 2);

    l->SetTile(1, 2, 16);
    l->SetTile(2, 2, 3);
    l->SetTile(3, 2, 34);

    l->SetTile(1, 3, 32);
    l->SetTile(2, 3, 34);
    mScene->AddChild(l);

}

GameState::~GameState() {
    mScene->RemoveAllChildren();
    delete mSubmarine;
}

void GameState::OnUpdate(float time_diff) {
    if(IsActive()) {
        Vector2D speed = mSubmarine->GetAbsoluteSpeed();
        speed.Rotate(mSubmarine->GetAbsoluteRotation());
        float x = 3.f; // move view to where we'll be in x seconds
        Vector2D target = Vector2D(Input::GetInstance().GetDefaultWindow().GetWidth() / 2, Input::GetInstance().GetDefaultWindow().GetHeight() / 2) - mSubmarine->Position - speed * x;
        Vector2D diff = target - mScene->Position;
        mScene->Move(diff * time_diff);

        mScene->Update(time_diff);
    }
}

void GameState::OnDraw(sf::RenderTarget& target) {
    if(IsActive()) {
        mScene->Draw(target);
    }
}

void GameState::OnHandleEvent(sf::Event& event) {
    if(event.Type == sf::Event::KeyPressed) {
        if(event.Key.Code == sf::Keyboard::Space) {
            mScene->AddChild(new Torpedo("torpedo-" + Resources::GetInstance().GetNextID(),
                                        mSubmarine->Position,
                                        mSubmarine->Speed,
                                        mSubmarine->Rotation + (mSubmarine->Speed.x < 0 ? PI : 0)));
        } else if(event.Type == sf::Event::KeyPressed) {
            if(event.Key.Code == sf::Keyboard::Escape) {
                StartTransitionOut(0.2f);
            } else if(event.Key.Code == sf::Keyboard::F4) {
                sf::Packet data;
                Serializer::Write(data, mScene);
                Serializer::WriteFileContents("scene", data);
            } else if(event.Key.Code == sf::Keyboard::F5) {
                delete mScene;
                sf::Packet p = Serializer::ReadFileContents("scene");
                mScene = (Entity*)Serializer::Load(p);
            }
        }
    }
}
