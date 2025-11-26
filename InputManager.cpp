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

void InputManager::CollectRawEvents()
{
}

void InputManager::DoHitTest()
{
}

void InputManager::DispatchEvents()
{
}
