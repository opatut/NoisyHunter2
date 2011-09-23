#include "MenuState.hpp"

#include "Narwhal.hpp"
#include "Resources.hpp"
#include "Text.hpp"

MenuState::MenuState()
    : mScene("scene") {
    mScene.AddChild(new Narwhal("narwhal" + Resources::GetInstance().GetNextID()));

    Text* t = new Text("menu-headline", "Noisy Hunter");
    t->Position.x = 400;
    t->Position.y = 100;
    t->SetSize(28);
    t->SetAlign(Text::TA_TOP);
    mScene.AddChild(t);

    t = new Text("menu-headline2", "Welcome to");
    t->Position.x = 400;
    t->Position.y = 80;
    t->SetSize(14);
    t->SetAlign(Text::TA_TOP);
    mScene.AddChild(t);
}

MenuState::~MenuState() {
    mScene.RemoveAllChildren();
}

void MenuState::OnUpdate(float time_diff) {
    if(IsActive()) {
        mScene.Update(time_diff);
    }
}

void MenuState::OnDraw(sf::RenderTarget& target) {
    if(IsActive()) {
        mScene.Draw(target);
    }
}

void MenuState::OnHandleEvent(sf::Event& event) {
    if(event.Type == sf::Event::KeyPressed) {
        if(event.Key.Code == sf::Keyboard::Escape) {
            StartTransitionOut(1.0);
        }
    }
}
