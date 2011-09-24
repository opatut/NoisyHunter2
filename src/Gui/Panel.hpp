#ifndef _PANEL
#define _PANEL

#include "Gui/Widget.hpp"

class Panel : public Widget {
public:
    Panel(QString name);
    virtual void Render();
};

#endif
