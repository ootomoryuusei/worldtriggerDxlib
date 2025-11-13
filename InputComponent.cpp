#include "InputComponent.h"

InputComponent::InputComponent(GameObject* parent) 
	: GameObject(parent,"InputComponent")
{
}

void InputComponent::Initialize()
{
	InputManager* inputManager = InputManager::GetInstance();
	keyboard_ = &inputManager->GetKeyboard();
	mouse_ = &inputManager->GetMouse();
}

void InputComponent::Update()
{
	if (mouse_->IsClicked(Mouse::LEFT)) {
		OnClick(mouse_->GetMousePos());
	}
	if (mouse_->IsDoubleClicked(Mouse::LEFT)) {
		OnDoubleClick(mouse_->GetMousePos());
	}
}
