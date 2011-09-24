#ifndef _BUTTON
#define _BUTTON

#include "Gui/Widget.hpp"

class Button : public Widget {
public:
    Button(QString name, QString caption = "");
    virtual void Render();
};

#endif
