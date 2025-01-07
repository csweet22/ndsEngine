// This file includes all relevant headers for engine use

#pragma once

#include "SceneTree.h"

// Nodes
#include "Animator.h"
#include "Camera3D.h"
#include "Mesh3D.h"
#include "Node.h"
#include "Node3D.h"
#include "Timer.h"

// Static helpers / Singletons
#include "Debug.h"
#include "Input.h"
#include "Renderer.h"
#include "Time.h"

// Data
#include "AnimationData.h"
#include "MeshData.h"
#include "TextureData.h"

// Other
#include <nds.h>
#include <stdio.h>
#include <functional>
#include <vector>

// glm
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

class Engine {
   public:
    Engine();
    ~Engine();
    void Init();
    void Start();

    using Delegate = std::function<void()>;
    std::vector<Delegate> onUpdateFunctions;
};