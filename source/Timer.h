#pragma once

#include <functional>

#include "Node.h"

class Timer : public Node {
   public:
    virtual NodeType GetType() const { return TIMER; }
    Timer(bool _autostart = false);
    ~Timer();
    virtual void Update();
    virtual void Start(float time = 0.0);
    virtual void Pause();
    virtual void Unpause();
    virtual void Stop();
    virtual void Restart();
    bool autostart = false;
    bool oneshot = false;
    float waitTime = 1.0;
    float currentTime = 0.0;
    bool running = false;

    using Delegate = std::function<void()>;
    Delegate onTimeout;
};