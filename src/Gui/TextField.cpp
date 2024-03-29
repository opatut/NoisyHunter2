#include "TextField.hpp"

#include "Core/Resources.hpp"

TextField::TextField(QString name)
    : Widget(name) {

    mText.SetFont(Resources::GetInstance().GetDefaultFont());
    mText.SetCharacterSize(14);

    EventSubmitField = new Callback<QString>();
}

void TextField::Render(sf::RenderTarget& target) {
    std::string caption(mCaption.toUtf8().data());
    mText.SetString(caption + (HasFocus() ? "_" : ""));

    sf::Color c = HasFocus() ? sf::Color::White : sf::Color(255, 255, 255, 150);

    // draw the shape
    mBackground = sf::Shape::Rectangle(GetAbsolutePosition().x + 1, GetAbsolutePosition().y + 1, Size.x - 2, Size.y - 2, sf::Color(255, 255, 255, 100), 1.f, c);
    target.Draw(mBackground);

    // draw the text
    mText.SetColor(c);
    mText.SetPosition(GetAbsolutePosition().x + 10, round(GetAbsolutePosition().y + Size.y / 2 - mText.GetRect().Height / 2));
    target.Draw(mText);
}

bool TextField::OnKeyDown(sf::Keyboard::Key key) {
    if(HasFocus()) {
        if(key == sf::Keyboard::Back) {
            if(mCaption.size() > 0) {
                SetCaption(mCaption.mid(0, mCaption.size() - 1));
            }
        } else if(key == sf::Keyboard::Return) {
            EventSubmitField->Call(this, mCaption);
        }
        return false;
    }
    return true;
}

bool TextField::OnTextEntered(uint32_t unicode) {
    if(HasFocus()) {
        if(unicode > 31)
            SetCaption(mCaption + QChar(unicode));
        return false;
    }
    return true;
}

bool TextField::OnChangeFocus(bool focus) {
    _Refresh();
    return true;
}

bool TextField::CanHaveFocus() {
    return true;
}
