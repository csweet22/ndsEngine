#include "Animator.h"

#include "AnimationData.h"

Animator::Animator(Node3D* _targetNode, AnimationData _animData) {
    targetNode = _targetNode;
    animData = _animData;
    waitTime = animData.duration;
}

Animator::~Animator() {
}

void Animator::Update() {
    Timer::Update();

    // Set target node transform
    Keyframe interpolatedFrame = animData.Interpolate(currentTime);

    targetNode->SetLocalPosition(interpolatedFrame.position);
    targetNode->SetLocalRotation(interpolatedFrame.rotation);
    targetNode->SetLocalScale(interpolatedFrame.scale);
}
