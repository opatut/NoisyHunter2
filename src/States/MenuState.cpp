#include "MenuState.hpp"

#include "Entities/Narwhal.hpp"
#include "Core/Input.hpp"
#include "Core/Resources.hpp"
#include "Core/StateManager.hpp"
#include "Gui/Button.hpp"
#include "States/GameState.hpp"
#include "States/EditorState.hpp"
#include "States/OptionsState.hpp"
#include "Gui/FocusManager.hpp"

MenuState::MenuState()
    : mScene("scene"),
      mGui("gui", sf::Color(255,255,255,0)) {

    for(int i = 0; i < Random::Get(10, 20); ++i) {
        mScene.AddChild(new Narwhal("narwhal" + Resources::GetInstance().GetNextID()));
    }

    mHeadline2 = new Text("menu-headline", "Noisy Hunter");
    mHeadline2->Position.x = Input::GetInstance().GetDefaultWindow().GetWidth() / 2;
    mHeadline2->Position.y = 100;
    mHeadline2->SetSize(36);
    mHeadline2->SetAlign(Text::TA_TOP);
    mHeadline2->SetAlignToPixel(false);
    mScene.AddChild(mHeadline2);

    mHeadline1 = new Text("menu-headline2", "Welcome to");
    mHeadline1->Position.x = Input::GetInstance().GetDefaultWindow().GetWidth() / 2;
    mHeadline1->Position.y = 80;
    mHeadline1->SetSize(18);
    mHeadline1->SetAlign(Text::TA_TOP);
    mHeadline1->SetAlignToPixel(false);
    mScene.AddChild(mHeadline1);

    /* ======== GUI ======== */
    mGui.Position = Vector2D(Input::GetInstance().GetDefaultWindow().GetWidth() / 2 - 100, Input::GetInstance().GetDefaultWindow().GetHeight() / 2  - 75);
    mGui.Size = Vector2D(200, 150);
    mGui.SetCaption("Test Panel");

    Button* b;

    int bh = 40;

    b = new Button("campaign-button", "Campaign");
    b->Position = Vector2D(0, 0);
    b->Size = Vector2D(200, bh);
    b->EventClick = new ClassCallback<MenuState, sf::Mouse::Button>(this, &MenuState::MenuButtonClick);
    mGui.AddChild(b);
    FocusManager::GetInstance().SetFocusWidget(b);

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
            mHeadline2->Position.x = sin(mLifetime * 0.2) * 50 + Input::GetInstance().GetDefaultWindow().GetWidth() / 2 - 50;
            mHeadline1->Position.x = -sin(mLifetime * 0.2) * 50 + Input::GetInstance().GetDefaultWindow().GetWidth() / 2 + 50;
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
            StartTransitionOut(0.2f);
        } else if(event.Key.Code == sf::Keyboard::E) {
            StateManager::GetInstance().AddState(new EditorState());
        }
    }
}

void MenuState::MenuButtonClick(void* sender, sf::Mouse::Button button) {
    Button* b = (Button*)sender;
    if(b->GetName() == "campaign-button") {
        StateManager::GetInstance().AddState(new GameState());
    } else if(b->GetName() == "editor-button") {
        StateManager::GetInstance().AddState(new EditorState());
    } else if(b->GetName() == "options-button") {
        StateManager::GetInstance().AddState(new OptionsState());
    } else if(b->GetName() == "quit-button") {
        StartTransitionOut(0.2f);
    }
}
