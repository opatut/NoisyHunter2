#ifndef _TEXT
#define _TEXT

#include <QString>

#include "Gui/Widget.hpp"

class Text : public Widget {
public:
    enum TextAlign {
        TA_CENTER = 0x0000,
        TA_LEFT = 0x0001,
        TA_RIGHT = 0x0010,
        TA_TOP = 0x0100,
        TA_BOTTOM = 0x1000
    };

    Text(QString name, QString caption, Vector2D position = Vector2D(), unsigned int size = 12, int align = TA_CENTER);

    virtual void OnUpdate(float time_diff);
    virtual void Render(sf::RenderTarget& target);

    void SetSize(unsigned int points);
    void SetCaption(QString caption);
    void SetAlign(int align);

    void SetAlignToPixel(bool align_to_pixel);
    bool GetAlignToPixel();

private:
    int mAlign;
    bool mAlignToPixel;
    void _Refresh();

    sf::Text mText;
};

#endif
