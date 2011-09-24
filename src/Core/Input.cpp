#include "Input.hpp"

Input& Input::GetInstance() {
    static Input instance;
    return instance;
}

void Input::SetDefaultWindow(sf::Window& window) {
    mDefaultWindow = &window;
}

Vector2D Input::GetMousePosition() {
    sf::Vector2i p = sf::Mouse::GetPosition(*mDefaultWindow);
    return Vector2D(p.x, p.y);
}
