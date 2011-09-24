#include "Widget.hpp"

#include "Core/Input.hpp"
#include <iostream>

Widget::Widget(QString name)
    : Entity(name) {}

void Widget::OnUpdate(float time_diff) {
    int before = mState;
    _AdjustWidgetState();
    if(before != mState) {
        // state has changed, refresh
        _Refresh();
    }
}

void Widget::OnDraw(sf::RenderTarget& target) {
    sf::Sprite sprite;
    sprite.SetTexture(mRenderTexture.GetTexture(), true);
    sprite.SetPosition(GetAbsolutePosition().x, GetAbsolutePosition().y);
    target.Draw(sprite);
}

int Widget::GetWidgetState() {
    return mState;
}

void Widget::SetCaption(QString caption) {
    mCaption = caption;
    _Refresh();
}

QString Widget::GetCaption() {
    return mCaption;
}

void Widget::_Refresh() {
    mRenderTexture.Create(Size.x, Size.y, false);
    mRenderTexture.Clear(sf::Color(0,0,0,0)); // remove everything
    Render();
    mRenderTexture.Display();
}

bool Widget::_IsPointInside(float x, float y) {
    return (x >= Position.x && x <= Position.x + Size.x && y >= Position.y && y <= Position.y + Size.y);
}

void Widget::_AdjustWidgetState() {
    mState = WS_NORMAL;
    if(_IsPointInside(Input::GetInstance().GetMousePosition().x, Input::GetInstance().GetMousePosition().y)) {
        mState |= WS_HOVER;
    }

    // TODO: Focus
    // TODO: Active

}
