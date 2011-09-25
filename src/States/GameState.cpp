#include "GameState.hpp"

#include <iostream>

#include "Core/Resources.hpp"
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

    Text* name = new Text("name", "opatut");
    name->Position.x = 0;
    name->Position.y = -24;
    name->SetAlign(Text::TA_BOTTOM);
    name->SetSize(9);
    mSubmarine->AddChild(name);

    mScene.AddChild(new Narwhal("narwhal-01"));

    // mScene.AddChild(new Level("level"));

    Tile* t;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            t = new Tile(i + j * 16);
            t->Position.x = i * 32 + 100;
            t->Position.y = j * 32 + 100;
            mScene.AddChild(t);
        }
    }

    for(int i = 0; i < 800; i += 32) {
        t = new Tile(1);
        t->Position.x = i;
        t->Position.y = 600 - 32;
        mScene.AddChild(t);
    }
}

GameState::~GameState() {
    mScene.RemoveAllChildren();
    delete mSubmarine;
}

void GameState::OnUpdate(float time_diff) {
    if(IsActive()) {
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
