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
	events_.clear();
	mouse_->Update(events_);
	keyboard_->Update(events_);
	
	for (auto& event : events_) {
		for (auto& component : inputComponents_) {
			if (!component->IsEntered()) continue;
			component->HandleInput(event);
		}
	}
}

void InputManager::RegisterInputComponent(InputComponent* component)
{
	inputComponents_.push_back(component);
}