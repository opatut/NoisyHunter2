#include "State.hpp"

State::State() {}

void State::Activate() {
    mActive = true;
    OnActivate();
}

void State::OnActivate() {}

void State::Deactivate() {
    mActive = false;
    OnDeactivate();
}

void State::OnDeactivate() {}

void State::Update(float time_diff) {
    if(mTransitionState.IsTransitioning()) {
        mTransitionState.AddTime(time_diff);
    }

    OnUpdate(time_diff);
}

void State::OnUpdate(float time_diff) {}

void State::Draw(sf::RenderTarget& target) {
    // only draw if visible
    if(!mTransitionState.IsInactive()) {
        OnDraw(target);
    }
}

void State::OnDraw(sf::RenderTarget& target) {}

void State::HandleEvent(sf::Event& event) {
    OnHandleEvent(event);
}

void State::OnHandleEvent(sf::Event& event) {}

void State::StartTransitionIn(float duration) {
    mTransitionState = TransitionState(TransitionState::INTO, duration, 0.f);
}

void State::StartTransitionOut(float duration) {
    mTransitionState = TransitionState(TransitionState::OUT, duration, 0.f);
}

TransitionState State::GetTransitionState() {
    return mTransitionState;
}

bool State::IsActive() {
    return mActive;
}
