#include "GameState.hpp"

#include <iostream>

#include "Resources.hpp"
#include "Text.hpp"
#include "Level.hpp"
#include "Narwhal.hpp"
#include "BackgroundGradient.hpp"
#include "Torpedo.hpp"

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

    mScene.AddChild(new Level("level"));
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
        }
    }
}
