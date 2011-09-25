#ifndef _PANEL
#define _PANEL

#include "Gui/Widget.hpp"

class Panel : public Widget {
public:
    Panel(QString name, sf::Color background = sf::Color(60, 60, 60, 230));
    virtual void Render();

    void SetBorder(float size, sf::Color color = sf::Color::White);

private:
    sf::Color mBackground;
    float mBorderSize;
    sf::Color mBorderColor;
};

#endif
