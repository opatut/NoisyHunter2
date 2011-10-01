#include "EditorState.hpp"
#include "Core/Input.hpp"
#include "Core/Resources.hpp"
#include "Gui/GraphicsButton.hpp"

EditorState::EditorState()
    : mScene("scene"),
      mGuiPanel("gui") {

    mGuiPanel.SetBackground(sf::Color(0,0,0, 255));
    mGuiPanel.SetBorder(2.f, sf::Color::White);
    mGuiPanel.Position = Vector2D(0, 0);
    mGuiPanel.Size = Vector2D(32 * 16, Input::GetInstance().GetDefaultWindow().GetHeight());

    for(int x = 0; x < 16; ++x) {
        for(int y = 0; y < 16; ++y) {
            sf::Sprite sprite(Resources::GetInstance().GetTexture("gfx/tiles.png"));
            sprite.SetSubRect(sf::IntRect(x * 64, y * 64, 64, 64));
            GraphicsButton* b = new GraphicsButton("tile-" + QString::number(x) + "-" + QString::number(y), "", sprite);
            b->Position = Vector2D(5 + 32 * x, 5 + 32 * y);
            b->Size = Vector2D(32, 32);
            b->EventClick = new ClassCallback<EditorState, sf::Mouse::Button>(this, &EditorState::ButtonSelectTile);
            mGuiPanel.AddChild(b);
        }
    }
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

        mGuiPanel.Draw(target);
    }
}

void EditorState::OnHandleEvent(sf::Event& event) {
    if(event.Type == sf::Event::KeyPressed) {
        if(event.Key.Code == sf::Keyboard::Escape) {
            StartTransitionOut(1.f);
        }
    }
}

void EditorState::ButtonSelectTile(void* sender, sf::Mouse::Button button) {
    std::cout << "Sender: " << ((Button*)sender)->GetName().toStdString() << std::endl;
}
