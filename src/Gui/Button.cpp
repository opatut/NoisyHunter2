#include "Button.hpp"

#include "Core/Resources.hpp"

Button::Button(QString name, QString caption)
    : Widget(name) {
    // use name as caption if no caption given (for debug)
    SetCaption(caption != "" ? caption : name);
}

void Button::Render() {
    // draw the shape
    sf::Color background = sf::Color(255, 255, 255, 50);
    if((GetWidgetState() & WS_HOVER) == WS_HOVER) {
        background.a = 100;
    }
    sf::Shape shape = sf::Shape::Rectangle(2, 2, Size.x - 4, Size.y - 4, background, 2.f, sf::Color::White);
    mRenderTexture.Draw(shape);

    // draw the text
    sf::Text text(mCaption.toStdString(), Resources::GetInstance().GetDefaultFont(), 11);
    text.SetPosition(round(Size.x / 2 - text.GetRect().Width / 2), round(Size.y / 2 - text.GetRect().Height / 2));
    mRenderTexture.Draw(text);
}
