
#include <nds.h>

#include "Singleton.h"

class Time : public Singleton<Time> {
   public:
    float GetDeltaTime() {
        return deltaTime;
    }

    void UpdateDeltaTime() {
        deltaTime = ((float)timerTicks2msec(cpuEndTiming())) / 1e3f;  // ms to s
        cpuStartTiming(0);
    }

   private:
    float deltaTime = 0;
};