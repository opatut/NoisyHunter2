#include "Text.hpp"

#include "Core/Resources.hpp"

Text::Text(QString name, QString caption, Vector2D position, unsigned int size, int align)
    : Entity(name, position) {
    mText.SetFont(Resources::GetInstance().GetDefaultFont());
    SetCaption(caption);
    SetSize(size);
    SetAlign(align);
    mAlignToPixel = true;
}

void Text::OnUpdate(float time_diff) {
    mText.SetScale(Size.x, Size.y);
    if(mAlignToPixel) {
        mText.SetPosition(round(GetAbsolutePosition().x), round(GetAbsolutePosition().y));
    } else {
        mText.SetPosition(GetAbsolutePosition().x, GetAbsolutePosition().y);
    }
    mText.SetRotation(Vector2D::rad2Deg(Rotation));
}

void Text::OnDraw(sf::RenderTarget& target) {
    target.Draw(mText);
}

void Text::SetSize(unsigned int points) {
    mText.SetCharacterSize(points);
    _Refresh();
}

void Text::SetCaption(QString caption) {
    mText.SetString(caption.toStdString());
    _Refresh();
}

void Text::SetAlign(int align) {
    mAlign = align;
    _Refresh();
}

void Text::SetAlignToPixel(bool align_to_pixel) {
    mAlignToPixel = align_to_pixel;
}

bool Text::GetAlignToPixel() {
    return mAlignToPixel;
}

void Text::_Refresh() {
    // set origin based on width / height and align

    int x = 0;
    int y = 0;
    float w = mText.GetRect().Width;
    float h = mText.GetRect().Height;

    if((mAlign & TA_LEFT) == TA_LEFT) {
        x = 0;
    } else if((mAlign & TA_RIGHT) == TA_RIGHT) {
        x = w;
    } else {
        x = w / 2;
    }

    if((mAlign & TA_TOP) == TA_TOP) {
        y = 0;
    } else if((mAlign & TA_BOTTOM) == TA_BOTTOM) {
        y = h;
    } else {
        y = h / 2;
    }

    mText.SetOrigin(x, y);
}
