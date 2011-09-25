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
    ~Widget();

    virtual void Render() = 0;

    void OnUpdate(float time_diff);
    void OnDraw(sf::RenderTarget& target);

    bool HandleEvent(sf::Event& event); // return true to continue event execution
    virtual bool OnHandleEvent(sf::Event& event); // see above

    int GetWidgetState();
    bool IsHover();
    bool HasFocus();

    void SetCaption(QString caption);
    QString GetCaption();

    virtual bool OnClick(sf::Mouse::Button button);
    virtual bool OnMouseButtonReleased(sf::Mouse::Button button);
    virtual bool OnMouseOver();
    virtual bool OnMouseOut();
    virtual bool OnKeyDown(sf::Keyboard::Key key);
    virtual bool OnKeyUp(sf::Keyboard::Key key);
    virtual bool OnTextEntered(uint32_t unicode);
    virtual bool OnFocus();
    virtual bool OnDefocus();
    virtual bool OnChangeCaption(QString old_caption, QString new_caption);

    virtual bool CanHaveFocus();

protected:
    void _Refresh(); // renders the texture again

    // used to check for hover state, defaults to bounding box
    virtual bool _IsPointInside(Vector2D p);
    bool _IsPointInside(float x, float y);
    bool _IsMouseInside();

    sf::RenderTexture mRenderTexture;
    QString mCaption;

private:
    void _AdjustWidgetState(); // checks if there is a hover / focus / active state and adjusts mState
    int mState;

};

#endif
