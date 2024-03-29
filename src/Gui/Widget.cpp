#include "Widget.hpp"

#include "Core/Input.hpp"
#include "FocusManager.hpp"
#include <iostream>

Widget::Widget(QString name)
    : Entity(name) {
    FocusManager::GetInstance().RegisterWidget(this);
    mState = -1; // force refresh on next draw

    EventClick = new Callback<sf::Mouse::Button>();
    EventMouseButtonReleased = new Callback<sf::Mouse::Button>();
    EventMouseOver = new Callback<>();
    EventMouseOut = new Callback<>();
    EventKeyDown = new Callback<sf::Keyboard::Key>();
    EventKeyUp = new Callback<sf::Keyboard::Key>();
    EventTextEntered = new Callback<uint32_t>();
    EventChangeFocus = new Callback<bool>();
    EventChangeCaption = new Callback<QString, QString>();

    Show();
}

Widget::~Widget() {
    FocusManager::GetInstance().UnregisterWidget(this);
}

uint32_t Widget::GetTypeId() const {
    return ET_UNKNOWN;
}

Serializable* Widget::CreateInstance() const {
    return nullptr;
}

void Widget::OnUpdate(float time_diff) {
}

void Widget::OnDraw(sf::RenderTarget& target) {
    if(IsVisible()) {
        _AdjustWidgetState();
        Render(target);
    }
}

bool Widget::HandleEvent(sf::Event& event) {
    if(!IsVisible())
        return true;

    // handle event in children
    // children are usually in front of their parent, so they have to be
    // handled first
    for(auto iter = mChildren.begin(); iter != mChildren.end(); ++iter) {
        if(!((Widget*)(iter->second))->HandleEvent(event))
            return false;
    }

    if(event.Type == sf::Event::MouseButtonPressed) {
        if(_IsMouseInside()) {
            if(CanHaveFocus())
                FocusManager::GetInstance().SetFocusWidget(this);
            EventClick->Call(this, event.MouseButton.Button);
            return OnClick(event.MouseButton.Button);
        }
    } else if(event.Type == sf::Event::MouseButtonReleased) {
        if(_IsMouseInside()) {
            EventMouseButtonReleased->Call(this, event.MouseButton.Button);
            return OnMouseButtonReleased(event.MouseButton.Button);
        }
    } else if(event.Type == sf::Event::KeyPressed) {
        EventKeyDown->Call(this, event.Key.Code);
        return OnKeyDown(event.Key.Code);
    } else if(event.Type == sf::Event::KeyReleased) {
        EventKeyUp->Call(this, event.Key.Code);
        return OnKeyUp(event.Key.Code);
    } else if(event.Type == sf::Event::TextEntered) {
        EventTextEntered->Call(this, event.Text.Unicode);
        return OnTextEntered(event.Text.Unicode);
    }

    // do custom stuff
    if(!OnHandleEvent(event))
        return false;

    return true;
}

bool Widget::OnHandleEvent(sf::Event& event) {
    // return true by default
    return true;
}

int Widget::GetWidgetState() {
    return mState;
}

bool Widget::IsHover() {
    return (mState & WS_HOVER) == WS_HOVER;
}

bool Widget::HasFocus() {
    return (mState & WS_FOCUS) == WS_FOCUS;
}

bool Widget::IsVisible() {
    if(GetParent() != nullptr && !((Widget*)GetParent())->IsVisible())
        return false;
    return (mState & WS_VISIBLE) == WS_VISIBLE;
}

void Widget::SetCaption(QString caption) {
    if(OnChangeCaption(mCaption, caption)) {
        mCaption = caption;
        _Refresh();
    }
}

QString Widget::GetCaption() {
    return mCaption;
}

void Widget::Show() {
    if((mState & WS_VISIBLE) != WS_VISIBLE) {
        mState ^= WS_VISIBLE;
    }
}

void Widget::Hide() {
    if((mState & WS_VISIBLE) == WS_VISIBLE) {
        mState ^= WS_VISIBLE;
    }
}

void Widget::_Refresh() {
    /*if(Size.x != mRenderTexture.GetWidth() || Size.y != mRenderTexture.GetHeight()) {
        mRenderTexture.Create(Size.x, Size.y);
    }
    mRenderTexture.Clear(sf::Color(0,0,0,0)); // remove everything
    Render(mRenderTexture);
    mRenderTexture.Display();*/
}

bool Widget::_IsPointInside(Vector2D p) {
    return (p.x >= GetAbsolutePosition().x && p.x <= GetAbsolutePosition().x + Size.x && p.y >= GetAbsolutePosition().y && p.y <= GetAbsolutePosition().y + Size.y);
}

bool Widget::_IsPointInside(float x, float y) {
    return _IsPointInside(Vector2D(x, y));
}

bool Widget::_IsMouseInside() {
    return _IsPointInside(Input::GetInstance().GetMousePosition());
}

void Widget::_AdjustWidgetState() {
    int before = mState;
    bool hover_before = IsHover();
    bool focus_before = HasFocus();
    bool visible_before = ((mState & WS_VISIBLE) == WS_VISIBLE);

    mState = WS_NORMAL;
    if(_IsMouseInside()) {
        mState |= WS_HOVER;
    }

    if(FocusManager::GetInstance().GetFocusWidget() == this) {
        mState |= WS_FOCUS;
    }

    if(visible_before) {
        mState |= WS_VISIBLE;
    }


    if(mState != before) {
        if(hover_before != IsHover()) {
            // TODO: Toggle hover event
            if(hover_before) {
                EventMouseOut->Call(this);
                OnMouseOut();
            } else {
                EventMouseOver->Call(this);
                OnMouseOver();
            }
        }
        if(focus_before != HasFocus()) {
            EventChangeFocus->Call(this, HasFocus());
            OnChangeFocus(HasFocus());
        }
        // _Refresh();
    }
}

// === EVENTS ===

bool Widget::OnClick(sf::Mouse::Button button) {
    return true;
}

bool Widget::OnMouseButtonReleased(sf::Mouse::Button button) {
    return true;
}

bool Widget::OnMouseOver() {
    return true;
}

bool Widget::OnMouseOut() {
    return true;
}

bool Widget::OnKeyDown(sf::Keyboard::Key key) {
    return true;
}

bool Widget::OnKeyUp(sf::Keyboard::Key key) {
    return true;
}

bool Widget::OnTextEntered(uint32_t unicode) {
    return true;
}

bool Widget::OnChangeFocus(bool focus) {
    return true;
}

bool Widget::OnChangeCaption(QString old_caption, QString new_caption) {
    return true;
}

bool Widget::CanHaveFocus() {
    return false;
}
