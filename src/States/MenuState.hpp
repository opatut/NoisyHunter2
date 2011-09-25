#ifndef _MENU_STATE
#define _MENU_STATE

#include "Core/State.hpp"
#include "Core/Entity.hpp"
#include "Gui/Panel.hpp"
#include "Hud/Text.hpp"

class MenuState : public State {
public:
    MenuState();
    ~MenuState();

    virtual void OnUpdate(float time_diff);
    virtual void OnDraw(sf::RenderTarget& target);
    virtual void OnHandleEvent(sf::Event& event);

    void CampaignButtonClick(sf::Mouse::Button button);
    void EditorButtonClick(sf::Mouse::Button button);
    void CloseButtonClick(sf::Mouse::Button button);

private:
    Text* mHeadline1, *mHeadline2;
    float mLifetime;
    Entity mScene;
    Panel mGui;

};

#endif
