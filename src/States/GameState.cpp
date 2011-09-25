#include "GameState.hpp"

#include <iostream>

#include "Core/Resources.hpp"
#include "Core/Input.hpp"
#include "Hud/Text.hpp"
#include "Entities/Level.hpp"
#include "Entities/Narwhal.hpp"
#include "Entities/Tile.hpp"
#include "Hud/BackgroundGradient.hpp"
#include "Entities/Torpedo.hpp"

GameState::GameState()
    : mScene("scene") {
    mScene.AddChild(new BackgroundGradient("background"));
    mSubmarine = new Submarine("submarine");
    mScene.AddChild(mSubmarine);

    mScene.AddChild(new Narwhal("narwhal-01"));

    // mScene.AddChild(new Level("level"));

    /*Tile* t;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            t = new Tile(i + j * 16);
            t->Position.x = i * 32 + 100;
            t->Position.y = j * 32 + 100;
            mScene.AddChild(t);
        }
    }*/

    Level* l = new Level("level");

    l->SetTile(1, 1, 0);
    l->SetTile(2, 1, 1);
    l->SetTile(3, 1, 2);

    l->SetTile(1, 2, 16);
    l->SetTile(2, 2, 3);
    l->SetTile(3, 2, 34);

    l->SetTile(1, 3, 32);
    l->SetTile(2, 3, 34);
    mScene.AddChild(l);

}

GameState::~GameState() {
    mScene.RemoveAllChildren();
    delete mSubmarine;
}

void GameState::OnUpdate(float time_diff) {
    if(IsActive()) {

        // Vector2D v(mScene.Position + Vector2D(400, 300));
        Vector2D speed = mSubmarine->GetAbsoluteSpeed();
        speed.Rotate(mSubmarine->GetAbsoluteRotation());
        float x = 3.f; // move view to where we'll be in x seconds
        Vector2D target = Vector2D(400,300) - mSubmarine->Position - speed * x;

        Vector2D diff = target - mScene.Position;
        mScene.Move(diff * time_diff);

        // mScene.Position = ;

        mScene.Update(time_diff);
    }
}

void GameState::OnDraw(sf::RenderTarget& target) {
    if(IsActive()) {
        mScene.Draw(target);
    }
}

void GameState::OnHandleEvent(sf::Event& event) {
    if(event.Type == sf::Event::KeyPressed) {
        if(event.Key.Code == sf::Keyboard::Space) {
            mScene.AddChild(new Torpedo("torpedo-" + Resources::GetInstance().GetNextID(),
                                        mSubmarine->Position,
                                        mSubmarine->Speed,
                                        mSubmarine->Rotation + (mSubmarine->Speed.x < 0 ? PI : 0)));
        } else if(event.Type == sf::Event::KeyPressed) {
            if(event.Key.Code == sf::Keyboard::Escape) {
                StartTransitionOut(1.f);
            }
        }
    }
}
