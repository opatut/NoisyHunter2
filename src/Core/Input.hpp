#ifndef _INPUT
#define _INPUT

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Core/Vector2D.hpp>

class Input {
public:
    static Input& GetInstance();
    void SetDefaultWindow(sf::RenderWindow& window);
    sf::RenderWindow& GetDefaultWindow();

    Vector2D GetMousePosition();

private:
    sf::RenderWindow* mDefaultWindow;
};

#endif
