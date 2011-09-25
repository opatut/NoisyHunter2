#ifndef _EDITOR_STATE
#define _EDITOR_STATE

#include "Core/State.hpp"
#include "Core/Entity.hpp"
#include "Gui/Panel.hpp"

class EditorState : public State {
public:
    EditorState();
    ~EditorState();

    virtual void OnUpdate(float time_diff);
    virtual void OnDraw(sf::RenderTarget& target);
    virtual void OnHandleEvent(sf::Event& event);

private:
    Entity mScene;
    Panel mGuiPanel;

};

#endif
