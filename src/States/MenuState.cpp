#include "MenuState.hpp"

#include "Entities/Narwhal.hpp"
#include "Core/Resources.hpp"
#include "Core/StateManager.hpp"
#include "Gui/Button.hpp"
#include "States/GameState.hpp"
#include "States/EditorState.hpp"

MenuState::MenuState()
    : mScene("scene"),
      mGui("gui", sf::Color(255,255,255,0)) {
    mScene.AddChild(new Narwhal("narwhal" + Resources::GetInstance().GetNextID()));

    mHeadline2 = new Text("menu-headline", "Noisy Hunter");
    mHeadline2->Position.x = 400;
    mHeadline2->Position.y = 100;
    mHeadline2->SetSize(36);
    mHeadline2->SetAlign(Text::TA_TOP);
    mHeadline2->SetAlignToPixel(false);
    mScene.AddChild(mHeadline2);

    mHeadline1 = new Text("menu-headline2", "Welcome to");
    mHeadline1->Position.x = 400;
    mHeadline1->Position.y = 80;
    mHeadline1->SetSize(18);
    mHeadline1->SetAlign(Text::TA_TOP);
    mHeadline1->SetAlignToPixel(false);
    mScene.AddChild(mHeadline1);

    /* ======== GUI ======== */
    mGui.Position = Vector2D(290, 215);
    mGui.Size = Vector2D(220, 170);
    mGui.SetCaption("Test Panel");

    Button* b;

    int bh = 40;

    b = new Button("campaign-button", "Campaign");
    b->Position = Vector2D(0, 0);
    b->Size = Vector2D(200, bh);
    b->EventClick = new ClassCallback<MenuState, sf::Mouse::Button>(this, &MenuState::MenuButtonClick);
    mGui.AddChild(b);

    b = new Button("editor-button", "Editor");
    b->Position = Vector2D(0, 1 * bh + 1 * 10);
    b->Size = Vector2D(200, bh);
    b->EventClick = new ClassCallback<MenuState, sf::Mouse::Button>(this, &MenuState::MenuButtonClick);
    mGui.AddChild(b);


    b = new Button("options-button", "Options");
    b->Position = Vector2D(0, 2 * bh + 2 * 10);
    b->Size = Vector2D(200, bh);
    b->EventClick = new ClassCallback<MenuState, sf::Mouse::Button>(this, &MenuState::MenuButtonClick);
    mGui.AddChild(b);

    b = new Button("quit-button", "Quit");
    b->Position = Vector2D(0, 3 * bh + 3 * 10);
    b->Size = Vector2D(200, bh);
    b->EventClick = new ClassCallback<MenuState, sf::Mouse::Button>(this, &MenuState::MenuButtonClick);
    mGui.AddChild(b);
}

MenuState::~MenuState() {
    mScene.RemoveAllChildren();
}

void MenuState::OnUpdate(float time_diff) {
    if(IsActive()) {
        mLifetime += time_diff;

        if(mLifetime < 2.5 * PI) {
            mHeadline2->Position.x = sin(mLifetime * 0.2) * 50 + 350;
            mHeadline1->Position.x = -sin(mLifetime * 0.2) * 50 + 450;
        }

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

void MenuState::MenuButtonClick(void* sender, sf::Mouse::Button button) {
    Button* b = (Button*)sender;
    if(b->GetName() == "campaign-button") {
        StateManager::GetInstance().AddState(new GameState());
    } else if(b->GetName() == "editor-button") {
        StateManager::GetInstance().AddState(new EditorState());
    } else if(b->GetName() == "quit-button") {
        StartTransitionOut(1.f);
    }
}
