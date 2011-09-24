#ifndef _INPUT
#define _INPUT

#include <SFML/Window.hpp>
#include <Core/Vector2D.hpp>

class Input {
public:
    static Input& GetInstance();
    void SetDefaultWindow(sf::Window& window);

    Vector2D GetMousePosition();

private:
    sf::Window* mDefaultWindow;
};

#endif
