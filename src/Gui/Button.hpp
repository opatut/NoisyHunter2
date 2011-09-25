#ifndef _BUTTON
#define _BUTTON

#include "Gui/Widget.hpp"
#include "Core/Callback.hpp"

class Button : public Widget {
public:
    Button(QString name, QString caption = "");
    virtual void Render();
    virtual bool OnClick(sf::Mouse::Button button);
    virtual bool CanHaveFocus();
    virtual bool OnChangeCaption(QString old_caption, QString new_caption);
    virtual bool OnMouseOver();

    Callback<sf::Mouse::Button>* ClickEvent;

private:
    sf::Text mText;


};

#endif
