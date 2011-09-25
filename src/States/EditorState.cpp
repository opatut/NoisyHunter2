#include "EditorState.hpp"

EditorState::EditorState()
    : mScene("scene"),
      mGuiPanel("gui") {

    mGuiPanel.Position = Vector2D(5, 5);
    mGuiPanel.Size = Vector2D(790, 42);

}

void EditorState::OnUpdate(float time_diff) {
    if(IsActive()) {
        mScene.Update(time_diff);
        mGuiPanel.Update(time_diff);
    }
}

void EditorState::OnDraw(sf::RenderTarget& target) {
    if(IsActive()) {
        mScene.Draw(target);
        mGuiPanel.Draw(target);

        sf::Shape h = sf::Shape::Line(0,0,target.GetWidth(),0,1.f,sf::Color(255,255,255,20));
        for(unsigned int i = 0; i < target.GetHeight(); i += 32) {
            h.SetPosition(0, i);
            target.Draw(h);
        }

        sf::Shape v = sf::Shape::Line(0,0,0,target.GetHeight(),1.f,sf::Color(255,255,255,20));
        for(unsigned int i = 0; i < target.GetWidth(); i += 32) {
            v.SetPosition(i, 0);
            target.Draw(v);
        }
    }
}

void EditorState::OnHandleEvent(sf::Event& event) {
    if(event.Type == sf::Event::KeyPressed) {
        if(event.Key.Code == sf::Keyboard::Escape) {
            StartTransitionOut(1.f);
        }
    }
}
