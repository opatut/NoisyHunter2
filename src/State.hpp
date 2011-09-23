#ifndef _STATE
#define _STATE

#include "TransitionState.hpp"

#include <SFML/Graphics.hpp>

class State {
public:
    State();

    void Activate();
    virtual void OnActivate();

    void Deactivate();
    virtual void OnDeactivate();

    void Update(float time_diff);
    virtual void OnUpdate(float time_diff);

    void Draw(sf::RenderTarget& target);
    virtual void OnDraw(sf::RenderTarget& target);

    void HandleEvent(sf::Event& event);
    virtual void OnHandleEvent(sf::Event& event);

    void StartTransitionIn(float duration);
    void StartTransitionOut(float duration);
    TransitionState GetTransitionState();

    bool IsActive();

private:
    TransitionState mTransitionState;
    bool mActive;


};

#endif
