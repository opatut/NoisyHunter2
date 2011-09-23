#ifndef _TRANSITION_STATE
#define _TRANSITION_STATE

class TransitionState {
public:
    enum StateCode {
        BEFORE,
        INTO,
        WHILE,
        OUT,
        AFTER
    };

    TransitionState();
    TransitionState(StateCode state, float duration, float time = 0.f);
    void SetProgress(float progress);
    void AddTime(float time);

    StateCode State;
    float Duration;
    float Time;

    bool IsTransitioning();
    bool IsInactive();
    float GetProgress();
};

#endif
