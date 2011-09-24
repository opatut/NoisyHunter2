#ifndef _WIDGET
#define _WIDGET

#include <QString>
#include <SFML/Graphics.hpp>
#include <Core/Entity.hpp>

class Widget : public Entity {
public:
    enum WidgetState {
        WS_NORMAL = 0x0000,
        WS_HOVER = 0x0001,
        WS_ACTIVE = 0x0010,
        WS_FOCUS = 0x0100
    };

    Widget(QString name);

    virtual void Render() = 0;

    void OnUpdate(float time_diff);
    void OnDraw(sf::RenderTarget& target);

    int GetWidgetState();

    void SetCaption(QString caption);
    QString GetCaption();

protected:
    void _Refresh(); // renders the texture again
    virtual bool _IsPointInside(float x, float y); // used to check for hover state, defaults to bounding box
    sf::RenderTexture mRenderTexture;

    QString mCaption;

private:
    void _AdjustWidgetState(); // checks if there is a hover / focus / active state and adjusts mState
    int mState;

};

#endif
