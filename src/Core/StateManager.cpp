#include "StateManager.hpp"

StateManager::StateManager() {
    mNextState = nullptr;
}

StateManager::~StateManager() {
    // pop all states
    PopState(mStates.size());
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
}

void StateManager::PushStates() {
    if(mNextState != nullptr) {
        if(GetCurrentState() != nullptr) {
            GetCurrentState()->Deactivate();
        }

        mStates.push_back(mNextState);
        mNextState->Activate();
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
}

void StateManager::Draw(sf::RenderTarget& target) {
    // draw in reverse order (in vector order) to draw current state *last*
    for(std::vector<State*>::iterator iter = mStates.begin(); iter != mStates.end(); ++iter) {
        // only draw if state above is transitioning or current state is topmost state
        if(iter == mStates.end() - 1 || (*(iter + 1))->GetTransitionState().IsTransitioning()) {
            (*iter)->Draw(target);
        }
    }
}
