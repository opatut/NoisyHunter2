#include "OptionsState.hpp"

#include "Gui/Button.hpp"
#include "Core/Random.hpp"

OptionsState::OptionsState()
    : mGui("gui") {

    Button* b;
    for(int i = 1; i <= 10; ++i) {
        b = new Button("b" + QString::number(i), QString::number(i));
        b->Position.x = Random::Get(200, 600);
        b->Position.y = Random::Get(200, 600);
        b->Size = Vector2D(50, 50);
        b->EventClick = new ClassCallback<OptionsState, sf::Mouse::Button>(this, &OptionsState::ButtonClick);
        mGui.AddChild(b);
    }

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
