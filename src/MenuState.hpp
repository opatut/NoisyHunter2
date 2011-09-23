#ifndef _MENU_STATE
#define _MENU_STATE

#include "State.hpp"

#include "Entity.hpp"

class MenuState : public State {
public:
    MenuState();
    ~MenuState();

    virtual void OnUpdate(float time_diff);
    virtual void OnDraw(sf::RenderTarget& target);
    virtual void OnHandleEvent(sf::Event& event);

private:
    Entity mScene;

};

#endif
