#include "TransitionState.hpp"

TransitionState::TransitionState() {}

TransitionState::TransitionState(StateCode state, float duration, float time) {
    State = state;
    Duration = duration;
    Time = time;
}

void TransitionState::SetProgress(float progress) {
    Time = progress * Duration;
}

void TransitionState::AddTime(float time) {
    Time += time;
    if(Time > Duration) {
        if(State == INTO)
            State = WHILE;
        if(State == OUT)
            State = AFTER;
    }
}

bool TransitionState::IsTransitioning() {
    return State == INTO || State == OUT;
}

bool TransitionState::IsInactive() {
    return State == BEFORE || State == AFTER;
}

float TransitionState::GetProgress() {
    return Time / Duration;
}
