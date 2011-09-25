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
        sf::Shape h = sf::Shape::Line(0,0,800,0,1.f,sf::Color(255,255,255,20));
        for(int i = 0; i < 600; i += 32) {
            h.SetPosition(0, i);
            target.Draw(h);
        }

        sf::Shape v = sf::Shape::Line(0,0,0,600,1.f,sf::Color(255,255,255,20));
        for(int i = 0; i < 800; i += 32) {
            v.SetPosition(i, 0);
            target.Draw(v);
        }

        mScene.Draw(target);
        mGuiPanel.Draw(target);
    }
}
