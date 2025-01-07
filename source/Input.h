// These helper methods make detecting input easier.

#pragma once

#include <nds.h>

#include <functional>
#include <map>
#include <string>
#include <vector>

class Input {
   public:
    static int GetKeyHeld(int keyCode) {
        int held = keysHeld();
        return (held & keyCode) ? 1 : 0;
    }

    static int GetKeyDown(int keyCode) {
        int down = keysDown();
        return (down & keyCode) ? 1 : 0;
    }

    static int GetKeyUp(int keyCode) {
        int up = keysUp();
        return (up & keyCode) ? 1 : 0;
    }

    static int GetAxis(int keyCodeNeg, int keyCodeBPos) {
        int held = keysHeld();
        return ((held & keyCodeNeg) ? -1 : 0) + ((held & keyCodeBPos) ? 1 : 0);
    }

    static int GetAxis(std::string bindingNameNeg, std::string bindingNamePos) {
        return ((GetKeyHeld(bindingNameNeg)) ? -1 : 0) + ((GetKeyHeld(bindingNamePos)) ? 1 : 0);
    }

    static int GetKeyHeld(std::string bindingName) {
        if (bindings.find(bindingName) != bindings.end()) {
            return GetKeyHeld(bindings[bindingName]);
        }
        return 0;  // No binding found
    }

    static int GetKeyDown(std::string bindingName) {
        if (bindings.find(bindingName) != bindings.end()) {
            return GetKeyDown(bindings[bindingName]);
        }
        return 0;  // No binding found
    }

    static int GetKeyUp(std::string bindingName) {
        if (bindings.find(bindingName) != bindings.end()) {
            return GetKeyUp(bindings[bindingName]);
        }
        return 0;  // No binding found
    }

    // Add a new binding from a string to a key code
    static void AddBindingKey(std::string bindingName, int keyCode) {
        if (bindings.find(bindingName) != bindings.end()) {
            bindings[bindingName] |= keyCode;
        } else {
            bindings[bindingName] = keyCode;
        }
    }

    // Remove a key binding by its name
    static void RemoveBindingKey(std::string bindingName, int keyCode) {
        if (bindings.find(bindingName) != bindings.end()) {
            bindings[bindingName] &= ~keyCode;
        }
    }

    static void RemoveBinding(std::string bindingName) {
        if (!HasBinding(bindingName))
            return;

        onHeldFunctions.erase(bindings[bindingName]);
        onDownFunctions.erase(bindings[bindingName]);
        onUpFunctions.erase(bindings[bindingName]);
        bindings.erase(bindingName);
    }

    static void AddOnHeld(std::string bindingName, std::function<void()> func) {
        if (HasBinding(bindingName))
            onHeldFunctions[bindings[bindingName]].emplace_back(func);
    }

    static void AddOnDown(std::string bindingName, std::function<void()> func) {
        if (HasBinding(bindingName))
            onDownFunctions[bindings[bindingName]].emplace_back(func);
    }

    static void AddOnUp(std::string bindingName, std::function<void()> func) {
        if (HasBinding(bindingName))
            onUpFunctions[bindings[bindingName]].emplace_back(func);
    }

    static bool HasBinding(std::string bindingName) {
        return bindings.find(bindingName) != bindings.end();
    }

    static std::map<std::string, int> bindings;

    using Delegate = std::function<void()>;
    static std::map<int, std::vector<Delegate>> onHeldFunctions;
    static std::map<int, std::vector<Delegate>> onDownFunctions;
    static std::map<int, std::vector<Delegate>> onUpFunctions;
};