#ifndef _STATE_MANAGER
#define _STATE_MANAGER

#include "State.hpp"

class StateManager {
public:
    StateManager();
    ~StateManager();

    void AddState(State* state, float transition = 0.f);
    State* GetCurrentState();
    void PopState(int count = 1);

    void HandleEvent(sf::Event& event);
    void Update(float time_diff);
    void Draw(sf::RenderTarget& target);

private:
    std::vector<State*> mStates; // used as a stack --> back = current state
};

#endif
