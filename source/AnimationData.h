#pragma once

#include <algorithm>  // For sort
#include <vector>

#include "../glm/glm.hpp"

struct Keyframe {
    float time = 0;
    glm::vec3 position = glm::vec3(0);
    glm::vec3 rotation = glm::vec3(0);
    glm::vec3 scale = glm::vec3(1);
};

class AnimationData {
   public:
    AnimationData() {
    }
    ~AnimationData() {
    }
    void AddKeyframe(Keyframe newFrame) {
        keyframes.emplace_back(newFrame);
        std::sort(keyframes.begin(), keyframes.end(), [](const Keyframe& a, const Keyframe& b) {
            return a.time < b.time;
        });

        if (newFrame.time > duration){
            duration = newFrame.time;
        }
    }
    void RemoveKeyFrame(size_t index) {
        if (index < keyframes.size())
            keyframes.erase(keyframes.begin() + index);
        // Recalculate duration
    }
    Keyframe Interpolate(float time) {
        if (keyframes.empty()) {
            // If there are no keyframes, return a default Keyframe
            return Keyframe();
        }

        if (time <= keyframes.front().time) {
            // If time is before the first keyframe, return the first keyframe
            return keyframes.front();
        }

        if (time >= keyframes.back().time) {
            // If time is after the last keyframe, return the last keyframe
            return keyframes.back();
        }

        // Find the two keyframes surrounding the given time
        for (size_t i = 0; i < keyframes.size() - 1; ++i) {
            const Keyframe& keyA = keyframes[i];
            const Keyframe& keyB = keyframes[i + 1];

            if (time >= keyA.time && time < keyB.time) {
                // Interpolate between keyA and keyB
                float t = (time - keyA.time) / (keyB.time - keyA.time);

                Keyframe result;
                result.time = time;
                result.position = glm::mix(keyA.position, keyB.position, t);
                result.rotation = glm::mix(keyA.rotation, keyB.rotation, t);
                result.scale = glm::mix(keyA.scale, keyB.scale, t);

                return result;
            }
        }

        // Fallback (shouldn't be reached with valid input)
        return Keyframe();
    }
    
    float duration = 0.0;

   private:
    std::vector<Keyframe> keyframes;
};