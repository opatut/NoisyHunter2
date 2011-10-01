#include "LoadingState.hpp"

#include "Hud/Text.hpp"
#include "Core/StateManager.hpp"
#include "Core/Input.hpp"
#include "Core/Resources.hpp"
#include "MenuState.hpp"

LoadingState::LoadingState()
    : mGui("gui"),
      mProgressBarOuter("progress-outer"),
      mProgressBarInner("progress-inner") {

    float w = Input::GetInstance().GetDefaultWindow().GetWidth();
    float h = Input::GetInstance().GetDefaultWindow().GetHeight();

    mProgressBarOuter.SetBackground(sf::Color(0, 0, 0));
    mProgressBarOuter.SetBorder(1.f, sf::Color::White);
    mProgressBarOuter.Size = Vector2D(300, 10);
    mProgressBarOuter.Position = Vector2D( w / 2 - mProgressBarOuter.Size.x / 2, h - 50);

    mProgressBarInner.SetBackground(sf::Color::White);
    mProgressBarInner.Position = Vector2D(2, 2);
    mProgressBarInner.Size = Vector2D(0, mProgressBarOuter.Size.y - 4);
    mProgressBarOuter.AddChild(&mProgressBarInner);

    mGui.AddChild(&mProgressBarOuter);

    mLoadingText = new Text("loading", "Loading ...", Vector2D(w / 2, h - 30), 12, Text::TA_TOP);
    mGui.AddChild(mLoadingText);

    mLogoTexture.LoadFromFile("../data/logo.png");
    mLogo.SetTexture(mLogoTexture);
    mLogo.SetOrigin(mLogoTexture.GetWidth() / 2, mLogoTexture.GetHeight() / 2);
    mLogo.SetPosition(w / 2, h / 2);

    mLoadingDone = false;
    mLifetime = 0;
}

LoadingState::~LoadingState() {}

void LoadingState::OnActivate() {
    if(mLoadingDone) {
        StartTransitionOut(0.f);
    }
}

float mod(float a, float b) {
    float quot = a / b;
    int quot_int = (int)floor(quot);
    float diff = b * quot_int;
    return a - diff;
}

float rect(float x, float f) {
    float m = mod(x, f);
    if(m < f / 2)
        return -1.f;
    else
        return 1.f;
}

void LoadingState::OnUpdate(float time_diff) {
    if(IsActive()) {
        mLifetime += time_diff;

        float a = mLifetime * 2.f - 0.5;
        if(a < 0.f) a = 0;
        if(a > 1.f) a = 1.f;

        mLogo.SetColor(sf::Color(255, 255, 255, 255 * a));

        mGui.Update(time_diff);

        mProgressBarInner.SetBackground(sf::Color(255, 255, 255, 200 + sin(mLifetime * 5) * 55));

        int i = Resources::GetInstance().GetQueueItem();
        int s = Resources::GetInstance().GetQueueSize();
        float p = i * 1.f / s;

        mProgressBarInner.Size.x = (mProgressBarOuter.Size.x - 4) * p;

        mLoadingDone = (i >= s);
        if(mLoadingDone) {
            mLoadingText->SetCaption("Loading done. Press any key to continue.");
        } else {
            mLoadingText->SetCaption("Loading ...  " + QString::number(round(p * 100)) + "%");
        }

#ifdef _DEBUG
        if(mLoadingDone && StateManager::GetInstance().GetCurrentState() == this) {
            StateManager::GetInstance().AddState(new MenuState());
            StartTransitionOut(0.f);
        }
#endif
    }
}

void LoadingState::OnDraw(sf::RenderTarget& target) {
    target.Draw(mLogo);
    mGui.Draw(target);
}

void LoadingState::OnHandleEvent(sf::Event& event) {
    if(event.Type == sf::Event::KeyPressed || event.Type == sf::Event::MouseButtonPressed) {
        if(mLoadingDone && StateManager::GetInstance().GetCurrentState() == this) {
            // continue
            StateManager::GetInstance().AddState(new MenuState());
        }
    }
}
