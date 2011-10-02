#ifndef _GAME_STATE
#define _GAME_STATE

#include "Core/State.hpp"
#include "Core/Entity.hpp"
#include "Entities/Submarine.hpp"

class GameState : public State {
public:
    GameState();
    ~GameState();

    virtual void OnUpdate(float time_diff);
    virtual void OnDraw(sf::RenderTarget& target);
    virtual void OnHandleEvent(sf::Event& event);

private:
    Entity* mScene;
    Submarine* mSubmarine;

};

#endif
