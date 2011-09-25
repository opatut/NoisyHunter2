#include "StateManager.hpp"

#include <iostream>

StateManager::StateManager() {
    mNextState = nullptr;
    mRenderTexture.Create(800, 600);
}

StateManager::~StateManager() {
    // pop all states
    PopState(mStates.size());
}

StateManager& StateManager::GetInstance() {
    static StateManager instance;
    return instance;
}

void StateManager::AddState(State* state, float transition) {
    mNextState = state;
}

State* StateManager::GetCurrentState() {
    if(mStates.size() > 0) {
        return mStates.back();
    } else {
        return nullptr;
    }
}

void StateManager::PopState(int count) {
    for(int i = 0; i < count; ++i) {
        if(mStates.size() > 0) {
            // delete it before popping
            mStates.back()->Deactivate();
            delete mStates.back();
            mStates.pop_back();
        }
    }
    if(count > 0) {
        mStates.back()->Activate();
    }
}

void StateManager::PushStates() {
    if(mNextState != nullptr) {
        if(GetCurrentState() != nullptr) {
            // GetCurrentState()->Deactivate();
        }

        mStates.push_back(mNextState);
        mNextState->Activate();
        mNextState->StartTransitionIn(1.f);
        mNextState = nullptr;
    }
}

void StateManager::HandleEvent(sf::Event& event) {
    if(mStates.size() > 0) {
        mStates.back()->HandleEvent(event);
    }
}

void StateManager::Update(float time_diff) {
    // update in reverse order (in vector order)
    for(std::vector<State*>::iterator iter = mStates.begin(); iter != mStates.end(); ++iter) {
        mStates.back()->Update(time_diff);
    }

    if(GetCurrentState()->GetTransitionState().State == TransitionState::WHILE && mStates.size() >= 2) {
        State* second_last = (*(mStates.end() - 2));
        if(second_last->IsActive())
            second_last->Deactivate();
    }

    if(GetCurrentState()->GetTransitionState().State == TransitionState::OUT && mStates.size() >= 2) {
        State* second_last = (*(mStates.end() - 2));
        if(!second_last->IsActive())
            second_last->Activate();
    }

    while(GetCurrentState()->GetTransitionState().State == TransitionState::AFTER) {
        PopState(1);
    }
}

void StateManager::Draw(sf::RenderTarget& target) {
    // draw in reverse order (in vector order) to draw current state *last*
    for(std::vector<State*>::iterator iter = mStates.begin(); iter != mStates.end(); ++iter) {
        // only draw if state above is transitioning or current state is topmost state
        if(iter == mStates.end() - 1 || (*(iter + 1))->GetTransitionState().IsTransitioning()) {
            TransitionState ts = (*iter)->GetTransitionState();
            if(ts.IsTransitioning()) {
                mRenderTexture.Clear(sf::Color(0,0,0,0));
                (*iter)->Draw(mRenderTexture);
                mRenderTexture.Display();
                sf::Sprite sprite(mRenderTexture.GetTexture());
                float c = ts.GetProgress();
                if(ts.State == TransitionState::OUT) c = 1 - c;
                sprite.SetColor(sf::Color(255, 255, 255, 255 * c));
                target.Draw(sprite);
            } else {
                // draw directly
                (*iter)->Draw(target);
            }
        }
    }
}
