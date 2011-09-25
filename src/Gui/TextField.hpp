#ifndef _TEXT_FIELD
#define _TEXT_FIELD

#include "Gui/Widget.hpp"
#include "Core/Callback.hpp"

class TextField : public Widget {
public:
    TextField(QString name);
    virtual void Render();
    virtual bool OnKeyDown(sf::Keyboard::Key key);
    virtual bool OnTextEntered(uint32_t unicode);
    virtual bool OnChangeCaption(QString old_caption, QString new_caption);

    Callback<QString>* ChangeEvent;

private:
    sf::Text mText;
    sf::Shape mBackground;

};

#endif
