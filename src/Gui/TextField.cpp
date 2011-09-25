#include "TextField.hpp"

#include "Core/Resources.hpp"

TextField::TextField(QString name)
    : Widget(name) {

    mText.SetFont(Resources::GetInstance().GetDefaultFont());
    mText.SetCharacterSize(11);

    ChangeEvent = new Callback<QString>();
}

void TextField::Render() {
    // draw the shape
    if(!HasFocus()) {
        mBackground = sf::Shape::Rectangle(1, 1, Size.x - 2, Size.y - 2, sf::Color(255, 255, 255, 100), 1.f, sf::Color::White);
        mRenderTexture.Draw(mBackground);
    }

    // draw the text
    mText.SetColor(sf::Color::White);
    mText.SetPosition(5, round(Size.y / 2 - mText.GetRect().Height / 2));
    mRenderTexture.Draw(mText);
}

bool TextField::OnKeyDown(sf::Keyboard::Key key) {
    if(key == sf::Keyboard::Back) {
        if(mCaption.size() > 0) {
            SetCaption(mCaption.mid(0, mCaption.size() - 1));
        }
    }
    return false;
}

bool TextField::OnTextEntered(uint32_t unicode) {
    if(unicode > 31)
        SetCaption(mCaption + QChar(unicode));
    return false;
}

bool TextField::OnChangeCaption(QString old_caption, QString new_caption) {
    std::cout << "caption: " << new_caption.toStdString() << std::endl;
    mText.SetString(new_caption.toStdString() + "_");
    return true;
}
