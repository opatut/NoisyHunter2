#ifndef _STATE_MANAGER
#define _STATE_MANAGER

#include "Core/State.hpp"

class StateManager {
public:
    ~StateManager();
    static StateManager& GetInstance();

    void AddState(State* state, float transition = 0.f);
    State* GetCurrentState();
    void PopState(int count = 1);

    void PushStates();

    void HandleEvent(sf::Event& event);
    void Update(float time_diff);
    void Draw(sf::RenderTarget& target);

private:
    StateManager();

    std::vector<State*> mStates; // used as a stack --> back = current state
    State* mNextState;
    sf::RenderTexture mRenderTexture;
};

#endif
