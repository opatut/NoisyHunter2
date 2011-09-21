#ifndef _TEXT
#define _TEXT

#include <QString>

#include "Entity.hpp"

class Text: public Entity {
public:
    enum TextAlign {
        TA_CENTER = 0x0000,
        TA_LEFT = 0x0001,
        TA_RIGHT = 0x0010,
        TA_TOP = 0x0100,
        TA_BOTTOM = 0x1000
    };

    Text(QString name, QString caption);

    virtual void OnUpdate(float time_diff);
    virtual void OnDraw(sf::RenderTarget& target);

    void SetSize(unsigned int points);
    void SetCaption(QString caption);
    void SetAlign(int align);
private:
    int mAlign;
    void _Refresh();

    sf::Text mText;
};

#endif
