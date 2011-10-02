#include "EditorState.hpp"
#include "Core/Input.hpp"
#include "Core/Resources.hpp"
#include "Gui/GraphicsButton.hpp"

EditorState::EditorState()
    : mScene("scene"),
      mGuiPanel("gui"),
      mLevel("level") {

    mGuiPanel.SetBackground(sf::Color(0,0,0, 255));
    mGuiPanel.SetBorder(2.f, sf::Color::White);
    mGuiPanel.Position = Vector2D(Input::GetInstance().GetDefaultWindow().GetWidth() / 2 - 32 * 8, Input::GetInstance().GetDefaultWindow().GetHeight() / 2 - 32 * 8);
    mGuiPanel.Size = Vector2D(32 * 16, 32 * 16);
    mGuiPanel.Hide();

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

    mLevel.SetGridSize(100, 100);
    mLevel.SetTileSize(32);
    mLevel.SetTile(5, 5, 2);

    mCurrentTile = -1;
}

void EditorState::OnUpdate(float time_diff) {
    if(IsActive()) {
        Vector2D m = Input::GetInstance().GetMousePosition();
        Vector2D s(Input::GetInstance().GetDefaultWindow().GetWidth(), Input::GetInstance().GetDefaultWindow().GetHeight());

        int border = 10;
        float speed = 250;
        if(m.x < border) {
            // move view left
            mLevel.Move(Vector2D(time_diff * speed, 0));
        } else if(m.x > s.x - border) {
            // move view left
            mLevel.Move(Vector2D(- time_diff * speed, 0));
        }
        if(m.y < border) {
            // move view left
            mLevel.Move(Vector2D(0, time_diff * speed));
        } else if(m.y > s.y - border) {
            // move view left
            mLevel.Move(Vector2D(0, - time_diff * speed));
        }

        mScene.Update(time_diff);
        mGuiPanel.Update(time_diff);
        mLevel.Update(time_diff);
    }
}

void EditorState::OnDraw(sf::RenderTarget& target) {
    if(IsActive()) {
        mScene.Draw(target);

        Vector2D d = mLevel.GetAbsolutePosition();

        sf::Shape h = sf::Shape::Line(0,0,target.GetWidth(),0,1.f,sf::Color(255,255,255,20));
        for(int i = -32; i <= (int)target.GetHeight(); i += 32) {
            h.SetPosition(0, i + ((int)d.y % 32));
            target.Draw(h);
        }

        sf::Shape v = sf::Shape::Line(0,0,0,target.GetHeight(),1.f,sf::Color(255,255,255,20));
        for(int i = -32; i <= (int)target.GetWidth(); i += 32) {
            v.SetPosition(i + ((int)d.x % 32), 0);
            target.Draw(v);
        }

        mLevel.Draw(target);
        mGuiPanel.Draw(target);
    }
}

void EditorState::OnHandleEvent(sf::Event& event) {
    if(!mGuiPanel.HandleEvent(event))
        return;

    if(event.Type == sf::Event::KeyPressed) {
        if(event.Key.Code == sf::Keyboard::Escape) {
            StartTransitionOut(0.2f);
        } else if(event.Key.Code == sf::Keyboard::Space) {
            if(mGuiPanel.IsVisible())
                mGuiPanel.Hide();
            else
                mGuiPanel.Show();
        }
    } else if(event.Type == sf::Event::MouseButtonPressed) {
        // get tile
        if(!mGuiPanel.IsVisible() || !mGuiPanel.IsHover()) {
            Vector2D m = mLevel.GetTileCoordinate(Input::GetInstance().GetMousePosition());
            if(event.MouseButton.Button == sf::Mouse::Left)
                mLevel.SetTile(m.x, m.y, mCurrentTile);
            else if(event.MouseButton.Button == sf::Mouse::Right)
                mLevel.SetTile(m.x, m.y, -1);
        }
    } else if(event.Type == sf::Event::MouseMoved) {
        // get tile
        if(!mGuiPanel.IsVisible() || !mGuiPanel.IsHover()) {
            Vector2D m = mLevel.GetTileCoordinate(Input::GetInstance().GetMousePosition());
            if(sf::Mouse::IsButtonPressed(sf::Mouse::Left))
                mLevel.SetTile(m.x, m.y, mCurrentTile);
            else if(sf::Mouse::IsButtonPressed(sf::Mouse::Right))
                mLevel.SetTile(m.x, m.y, -1);
        }
    }
}

void EditorState::ButtonSelectTile(void* sender, sf::Mouse::Button button) {
    QString name = ((Button*)sender)->GetName();
    QList<QString> split = name.split("-");
    if(split[0] == "tile") {
        int x = split[1].toInt(0);
        int y = split[2].toInt(0);
        mCurrentTile = x + y * 16;
    }
}
