#ifndef _LOADING_STATE
#define _LOADING_STATE

#include "Core/State.hpp"
#include "Core/Entity.hpp"
#include "Entities/Submarine.hpp"
#include "Hud/Text.hpp"
#include "Gui/Panel.hpp"

class LoadingState : public State {
public:
    LoadingState();
    ~LoadingState();

    void OnActivate();
    virtual void OnUpdate(float time_diff);
    virtual void OnDraw(sf::RenderTarget& target);
    virtual void OnHandleEvent(sf::Event& event);

private:
    Entity mOverlay;
    Text* mLoadingText;
    Panel mProgressBarOuter;
    Panel mProgressBarInner;

    sf::Sprite mLogo;
    sf::Texture mLogoTexture;

    bool mLoadingDone;
    float mLifetime;
};

#endif
