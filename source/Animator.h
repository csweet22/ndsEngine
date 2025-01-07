#pragma once

#include "Timer.h"
#include "Node3D.h"
#include "AnimationData.h"
#include "../glm/glm.hpp"

class Animator : public Timer {
   public:
    virtual NodeType GetType() const { return ANIMATOR; }
    Animator(Node3D* _targetNode, AnimationData _animData);
    ~Animator();
    virtual void Update();

   protected:
    Node3D* targetNode;
    AnimationData animData;
};