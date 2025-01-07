#include "Timer.h"

#include <stdio.h>

#include "Time.h"

Timer::Timer(bool _autostart) {
    autostart = _autostart;
    if (autostart)
        Start();
}

Timer::~Timer() {
}

void Timer::Update() {
    Node::Update();

    if (running) {
        currentTime += float(Time::GetInstance().GetDeltaTime());
        // printf("Timer: %f\n", currentTime);
    } else {
        return;
    }

    if (currentTime > waitTime) {
        if (onTimeout)
            onTimeout();

        if (oneshot) {
            Stop();
        } else {
            Restart();
        }
    }
}

void Timer::Start(float time) {
    currentTime = time;
    running = true;
}

void Timer::Pause() {
    running = false;
}

void Timer::Unpause() {
    running = true;
}

void Timer::Stop() {
    running = false;
}

void Timer::Restart() {
    Stop();
    Start();
}
