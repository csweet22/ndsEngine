#include "Input.h"

std::map<std::string, int> Input::bindings;

using Delegate = std::function<void()>;
std::map<int, std::vector<Delegate>> Input::onHeldFunctions;
std::map<int, std::vector<Delegate>> Input::onDownFunctions;
std::map<int, std::vector<Delegate>> Input::onUpFunctions;