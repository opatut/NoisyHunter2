#ifndef _FOCUS_MANAGER
#define _FOCUS_MANAGER

#include <vector>

// forward declaration
class Widget;

class FocusManager {
public:
    static FocusManager& GetInstance();

    void RegisterWidget(Widget* widget);
    void UnregisterWidget(Widget* widget);

    Widget* GetFocusWidget();
    void ShiftFocus(int offset = 1);
    void ShiftFocusRight();
    void ShiftFocusLeft();
    void ShiftFocusUp();
    void ShiftFocusDown();
    bool SetFocusWidget(Widget* widget);

private:
    void _SetFocus(int focus);
    FocusManager();
    void _FixFocus();

    std::vector<Widget*> mWidgets;
    int mFocus;

};

#endif
