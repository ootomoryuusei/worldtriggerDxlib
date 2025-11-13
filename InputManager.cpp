#include "InputManager.h"

InputManager::InputManager(GameObject* parent)
{
}

void InputManager::Initialize()
{
	keyboard_ = Instantiate<Keyboard>(this);
	mouse_ = Instantiate<Mouse>(this);
}

void InputManager::Update()
{
}

bool InputManager::IsActionTriggerd(std::string actionName)
{
	return false;
}
