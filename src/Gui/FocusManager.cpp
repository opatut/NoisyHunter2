#include "FocusManager.hpp"

#include <iostream>
#include "Widget.hpp"

FocusManager& FocusManager::GetInstance() {
    static FocusManager instance;
    return instance;
}

void FocusManager::RegisterWidget(Widget* widget) {
    mWidgets.push_back(widget);
}

void FocusManager::UnregisterWidget(Widget* widget) {
    for(std::vector<Widget*>::iterator iter = mWidgets.begin(); iter != mWidgets.end(); ++iter) {
        if(*iter == widget) {
            iter = mWidgets.erase(iter);
        }
    }
}

Widget* FocusManager::GetFocusWidget() {
    _FixFocus();
    if(mFocus >= (int)mWidgets.size())
        return nullptr;
    return mWidgets.at(mFocus);
}

void FocusManager::ShiftFocus(int offset) {
    std::cout << "New focus: " << mFocus << " -> " << mFocus + offset << std::endl;
    _SetFocus(mFocus + offset);
}

void FocusManager::ShiftFocusRight() {
    // - find first the widget that starts right of this
    // - if multiple widgets with same x-coordinate, take the one closest in y-coordinate
    // - ignore size

    Widget* new_focus = nullptr;
    Widget* current = GetFocusWidget();

    // select the widget that is closest right of the current widget
    for(std::vector<Widget*>::iterator iter = mWidgets.begin(); iter != mWidgets.end(); ++iter) {
        Widget* i = (*iter);
        if(!i->CanHaveFocus())
            continue;
        // is the widget right of the current widget?
        if(i->Position.x > current->Position.x) {
            // is it closer than the last found widget or the first widget found?
            if(new_focus == nullptr || i->Position.x < new_focus->Position.x)
                new_focus = i;
        }
    }

    if(new_focus != nullptr)
        SetFocusWidget(new_focus);
}

void FocusManager::ShiftFocusLeft() {
    Widget* new_focus = nullptr;
    Widget* current = GetFocusWidget();

    for(std::vector<Widget*>::iterator iter = mWidgets.begin(); iter != mWidgets.end(); ++iter) {
        Widget* i = (*iter);
        if(!i->CanHaveFocus())
            continue;
        if(i->Position.x < current->Position.x) {
            if(new_focus == nullptr || i->Position.x > new_focus->Position.x)
                new_focus = i;
        }
    }

    if(new_focus != nullptr)
        SetFocusWidget(new_focus);
}

void FocusManager::ShiftFocusUp() {
    Widget* new_focus = nullptr;
    Widget* current = GetFocusWidget();

    for(std::vector<Widget*>::iterator iter = mWidgets.begin(); iter != mWidgets.end(); ++iter) {
        Widget* i = (*iter);
        if(!i->CanHaveFocus())
            continue;
        if(i->Position.y < current->Position.y) {
            if(new_focus == nullptr || i->Position.y > new_focus->Position.y)
                new_focus = i;
        }
    }

    if(new_focus != nullptr)
        SetFocusWidget(new_focus);
}

void FocusManager::ShiftFocusDown() {
    Widget* new_focus = nullptr;
    Widget* current = GetFocusWidget();

    for(std::vector<Widget*>::iterator iter = mWidgets.begin(); iter != mWidgets.end(); ++iter) {
        Widget* i = (*iter);
        if(!i->CanHaveFocus())
            continue;
        if(i->Position.y > current->Position.y) {
            if(new_focus == nullptr || i->Position.y < new_focus->Position.y)
                new_focus = i;
        }
    }

    if(new_focus != nullptr)
        SetFocusWidget(new_focus);
}

bool FocusManager::SetFocusWidget(Widget* widget) {
    unsigned int i = 0;
    for(std::vector<Widget*>::iterator iter = mWidgets.begin(); iter != mWidgets.end(); ++iter) {
        if(*iter == widget) {
            _SetFocus(i);
            return true;
        }
        ++i;
    }
    // didn't work
    return false;
}

void FocusManager::_FixFocus() {
    unsigned int s = mWidgets.size();
    if(s > 0) {
        while(mFocus < 0)
            mFocus += s;
        while(mFocus >= (int)s)
            mFocus -= s;
    }
}

FocusManager::FocusManager() {
    mFocus = -1;
}

void FocusManager::_SetFocus(int focus) {
    Widget* old_focus = GetFocusWidget();
    mFocus = focus;
    _FixFocus();
    while(!GetFocusWidget()->CanHaveFocus() && mWidgets.size() > 0) {
        UnregisterWidget(GetFocusWidget());
        _FixFocus();
    }

    while(!GetFocusWidget()->IsVisible()) {
        ShiftFocus(1);
        if(GetFocusWidget() == old_focus)
            break; // shit, seems like we wrapped around
    }
}
