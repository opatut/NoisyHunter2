#include "MenuState.hpp"

#include "Entities/Narwhal.hpp"
#include "Core/Resources.hpp"
#include "Core/StateManager.hpp"
#include "Gui/Button.hpp"
#include "States/GameState.hpp"
#include "States/EditorState.hpp"
#include "Hud/Text.hpp"

MenuState::MenuState()
    : mScene("scene"),
      mGui("gui") {
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

    /* ======== GUI ======== */
    mGui.Position = Vector2D(290, 215);
    mGui.Size = Vector2D(220, 170);
    mGui.SetCaption("Test Panel");

    Button* b;

    b = new Button("campaign-button", "Campaign");
    b->Position = Vector2D(10, 10);
    b->Size = Vector2D(200, 30);
    b->ClickEvent = new ClassCallback<MenuState, sf::Mouse::Button>(this, &MenuState::CampaignButtonClick);
    mGui.AddChild(b);

    b = new Button("editor-button", "Editor");
    b->Position = Vector2D(10, 50);
    b->Size = Vector2D(200, 30);
    b->ClickEvent = new ClassCallback<MenuState, sf::Mouse::Button>(this, &MenuState::EditorButtonClick);
    mGui.AddChild(b);


    b = new Button("options-button", "Options");
    b->Position = Vector2D(10, 90);
    b->Size = Vector2D(200, 30);
    // b->ClickEvent = new ClassCallback<MenuState, sf::Mouse::Button>(this, &MenuState::OptionsButtonClick);
    mGui.AddChild(b);

    b = new Button("button3", "Quit");
    b->Position = Vector2D(10, 130);
    b->Size = Vector2D(200, 30);
    b->ClickEvent = new ClassCallback<MenuState, sf::Mouse::Button>(this, &MenuState::CloseButtonClick);
    mGui.AddChild(b);
}

MenuState::~MenuState() {
    mScene.RemoveAllChildren();
}

void MenuState::OnUpdate(float time_diff) {
    if(IsActive()) {
        mScene.Update(time_diff);
        mGui.Update(time_diff);
    }
}

void MenuState::OnDraw(sf::RenderTarget& target) {
    if(IsActive()) {
        mScene.Draw(target);
        mGui.Draw(target);
    }
}

void MenuState::OnHandleEvent(sf::Event& event) {
    if(!mGui.HandleEvent(event))
        return;

    if(event.Type == sf::Event::KeyPressed) {
        if(event.Key.Code == sf::Keyboard::Escape) {
            StartTransitionOut(1.0);
        }
    }
}

void MenuState::CloseButtonClick(sf::Mouse::Button button) {
    StartTransitionOut(1.f);
}

void MenuState::CampaignButtonClick(sf::Mouse::Button button) {
    StateManager::GetInstance().AddState(new GameState());
}

void MenuState::EditorButtonClick(sf::Mouse::Button button) {
    StateManager::GetInstance().AddState(new EditorState());
}
