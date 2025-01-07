#pragma once

#include "Node.h"
#include "Singleton.h"

class SceneTree : public Singleton<SceneTree> {
   public:
    Node* GetRoot();

   private:
    Node root;
};