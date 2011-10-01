#ifndef _OPTIONS_STATE
#define _OPTIONS_STATE

#include "Core/State.hpp"
#include "Core/Entity.hpp"
#include "Gui/Panel.hpp"
#include "Hud/Text.hpp"

class OptionsState : public State {
public:
    OptionsState();
    ~OptionsState();

    virtual void OnUpdate(float time_diff);
    virtual void OnDraw(sf::RenderTarget& target);
    virtual void OnHandleEvent(sf::Event& event);

    void ButtonClick(void* sender, sf::Mouse::Button button);

private:
    Panel mGui;

};

#endif
