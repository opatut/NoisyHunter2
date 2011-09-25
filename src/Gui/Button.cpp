#include "Button.hpp"

#include <iostream>
#include <ctime>
#include "Core/Resources.hpp"
#include "FocusManager.hpp"

Button::Button(QString name, QString caption)
    : Widget(name) {
    // use name as caption if no caption given (for debug)
    SetCaption(caption != "" ? caption : name);

    mText.SetFont(Resources::GetInstance().GetDefaultFont());
    mText.SetCharacterSize(16);

    mBackground.SetTexture(Resources::GetInstance().GetTexture("gfx/gui.png"));
}

void Button::Render() {
    // draw the shape
    //sf::Shape shape = sf::Shape::Rectangle(1, 1, Size.x - 2, Size.y - 2, sf::Color(255, 255, 255, (HasFocus() ? 100 : 50)), 2.f, sf::Color::White);
    // mRenderTexture.Draw(shape);
    mBackground.SetPosition(0, 0);
    mBackground.SetScale(Size.x, Size.y);
    mBackground.SetSubRect(sf::IntRect(0, (HasFocus() ? 40 : 0), 200, 40));
    mRenderTexture.Draw(mBackground);

    // draw the text
    mText.SetColor(sf::Color::White);
    mText.SetPosition(round(Size.x / 2 - mText.GetRect().Width / 2), round(Size.y / 2 - mText.GetRect().Height / 2));
    mRenderTexture.Draw(mText);
}

bool Button::OnClick(sf::Mouse::Button button) {
    return false;
}

bool Button::CanHaveFocus() {
    return true;
}

bool Button::OnChangeCaption(QString old_caption, QString new_caption) {
    mText.SetString(new_caption.toStdString());
    return true;
}

bool Button::OnMouseOver() {
    FocusManager::GetInstance().SetFocusWidget(this);
    return true;
}
