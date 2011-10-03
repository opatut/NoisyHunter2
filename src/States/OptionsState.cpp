#include "OptionsState.hpp"


#include "Gui/Button.hpp"
#include "Core/Random.hpp"
#include "Core/Resources.hpp"

OptionsState::OptionsState()
    : mGui("gui") {

    mGui.SetBackground(sf::Color(255,255,255,50));
    mGui.Size = Vector2D(400, 300);
    mGui.Position = Vector2D(100, 100);
    mGui.SetBorder(1.f, sf::Color::White);

    int line_height = 40;
    int font_size_1 = 12;
    int font_size_2 = 18;

    mGui.AddChild(new Text("label-1", "Fullscreen",         Vector2D(mGui.Size.x / 2 - 10, line_height * 1), font_size_1, Text::TA_RIGHT));
    mGui.AddChild(new Text("label-2", "no",                 Vector2D(mGui.Size.x / 2 + 10, line_height * 1), font_size_2, Text::TA_LEFT));

    mGui.AddChild(new Text("label-3", "Resolution",         Vector2D(mGui.Size.x / 2 - 10, line_height * 2), font_size_1, Text::TA_RIGHT));
    mGui.AddChild(new Text("label-4", "1000 x 680",         Vector2D(mGui.Size.x / 2 + 10, line_height * 2), font_size_2, Text::TA_LEFT));

    mGui.AddChild(new Text("label-5", "Username",           Vector2D(mGui.Size.x / 2 - 10, line_height * 3), font_size_1, Text::TA_RIGHT));
    mGui.AddChild(new Text("label-6", "opatut",             Vector2D(mGui.Size.x / 2 + 10, line_height * 3), font_size_2, Text::TA_LEFT));

    Button* b;

    b = new Button("cancel", "Cancel");
    b->Position = Vector2D(mGui.Size.x / 2 - 110, mGui.Size.y - 40);
    b->Size = Vector2D(100, 30);
    b->EventClick = new ClassCallback<OptionsState, sf::Mouse::Button>(this, &OptionsState::ButtonClick);
    mGui.AddChild(b);

    b = new Button("save", "Save");
    b->Position = Vector2D(mGui.Size.x / 2 + 10, mGui.Size.y - 40);
    b->Size = Vector2D(100, 30);
    b->EventClick = new ClassCallback<OptionsState, sf::Mouse::Button>(this, &OptionsState::ButtonClick);
    mGui.AddChild(b);
}

OptionsState::~OptionsState() {}

void OptionsState::OnUpdate(float time_diff) {
    mGui.Update(time_diff);
}

void OptionsState::OnDraw(sf::RenderTarget& target) {
    mGui.Draw(target);
}

void OptionsState::OnHandleEvent(sf::Event& event) {
    mGui.HandleEvent(event);
}

void OptionsState::ButtonClick(void* sender, sf::Mouse::Button button) {
    std::cout << "Button " << ((Button*)sender)->GetCaption().toStdString() << " clicked." << std::endl;
}
