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
    _SetFocus(mFocus + offset);
}

void FocusManager::ShiftFocusRight() {
    // - find first the widget that starts right of this
    // - if multiple widgets with same x-coordinate, take the one closest in y-coordinate
    // - ignore size

    Widget* new_focus = nullptr;
    Widget* current = GetFocusWidget();
    for(std::vector<Widget*>::iterator iter = mWidgets.begin(); iter != mWidgets.end(); ++iter) {
        if(*iter != current) {
            if((*iter)->Position.x > current->Position.x) {
                if(new_focus == nullptr || abs(new_focus->Position.y - current->Position.y) > abs((*iter)->Position.y - current->Position.y)) {
                    new_focus = *iter;
                }
            }
        }
    }
    if(new_focus == nullptr) {
        // take leftmost widget at closest height
        for(std::vector<Widget*>::iterator iter = mWidgets.begin(); iter != mWidgets.end(); ++iter) {
            if(new_focus == nullptr)
                new_focus = *iter;

            if((*iter)->Position.x <= new_focus->Position.x) {
                // either the iter is further left             OR   it is closer to the current y
                if((*iter)->Position.x < new_focus->Position.x || abs((*iter)->Position.y - current->Position.y) < abs(new_focus->Position.y - current->Position.y))
                    new_focus = *iter;
            }
        }
    }

    if(new_focus != nullptr)
        SetFocusWidget(new_focus);
}

void FocusManager::ShiftFocusLeft() {

}

void FocusManager::ShiftFocusUp() {

}

void FocusManager::ShiftFocusDown() {

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
