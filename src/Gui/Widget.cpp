#include "Widget.hpp"

#include "Core/Input.hpp"
#include "FocusManager.hpp"
#include <iostream>

Widget::Widget(QString name)
    : Entity(name) {
    FocusManager::GetInstance().RegisterWidget(this);
    mState = -1; // force refresh on next draw
}

Widget::~Widget() {
    FocusManager::GetInstance().UnregisterWidget(this);
}

void Widget::OnUpdate(float time_diff) {
}

void Widget::OnDraw(sf::RenderTarget& target) {
    _AdjustWidgetState();

    sf::Sprite sprite;
    sprite.SetTexture(mRenderTexture.GetTexture(), true);
    sprite.SetPosition(GetAbsolutePosition().x, GetAbsolutePosition().y);
    target.Draw(sprite);
}

bool Widget::HandleEvent(sf::Event& event) {
    // handle event in children
    // children are usually in front of their parent, so they have to be
    // handled first
    for(auto iter = mChildren.begin(); iter != mChildren.end(); ++iter) {
        Widget* w = (Widget*)iter->second;
        if(!w->HandleEvent(event))
            return false;
    }

    if(event.Type == sf::Event::MouseButtonPressed && _IsMouseInside()) {
        std::cout << "event!" << std::endl;
        return OnClick(event.MouseButton.Button);
    }

    if(event.Type == sf::Event::MouseButtonReleased && _IsMouseInside()) {
        return OnMouseButtonReleased(event.MouseButton.Button);
    }

    if(event.Type == sf::Event::MouseMoved) {
        int was_hover = IsHover();
        _AdjustWidgetState();

        // we are now hovered but weren't before
        if(_IsMouseInside() && !was_hover) {
            return OnMouseOver();
        }

        // we are not hovered but were before
        if(!_IsMouseInside() && was_hover) {
            return OnMouseOut();
        }
    }

    if(event.Type == sf::Event::KeyPressed) {
        return OnKeyDown(event.Key.Code);
    }

    if(event.Type == sf::Event::KeyReleased) {
        return OnKeyUp(event.Key.Code);
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

void Widget::SetCaption(QString caption) {
    if(OnChangeCaption(mCaption, caption)) {
        mCaption = caption;
        _Refresh();
    }
}

QString Widget::GetCaption() {
    return mCaption;
}

void Widget::_Refresh() {
    if(Size.x != mRenderTexture.GetWidth() || Size.y != mRenderTexture.GetHeight()) {
        mRenderTexture.Create(Size.x, Size.y);
    }
    mRenderTexture.Clear(sf::Color(0,0,0,0)); // remove everything
    Render();
    mRenderTexture.Display();
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

    mState = WS_NORMAL;
    if(_IsMouseInside()) {
        mState |= WS_HOVER;
    }

    if(FocusManager::GetInstance().GetFocusWidget() == this) {
        mState |= WS_FOCUS;
    }

    // TODO: Active

    if(mState != before) {
        _Refresh();
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

bool Widget::OnFocus() {
    return true;
}

bool Widget::OnDefocus() {
    return true;
}

bool Widget::OnChangeCaption(QString old_caption, QString new_caption) {
    return true;
}

bool Widget::CanHaveFocus() {
    return false;
}
