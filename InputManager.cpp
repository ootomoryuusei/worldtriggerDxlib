#include "InputManager.h"

InputManager::InputManager(GameObject* parent)
{
}

void InputManager::Initialize()
{
	keyboard_ = Instantiate<Keyboard>(this);
	mouse_ = Instantiate<Mouse>(this);

	mouse_->OnClick = [&](const MouseClickEvent& e) {AddEvent(e);};
	mouse_->OnDoubleClick = [&](const MouseClickEvent& e) {AddEvent(e);};
	mouse_->OnPress = [&](const MouseClickEvent& e) {AddEvent(e);};
	mouse_->OnRelease = [&](const MouseClickEvent& e) {AddEvent(e);};
	mouse_->OnDrag = [&](const MouseDragEvent& e) {AddEvent(e);};
	mouse_->OnDragStart = [&](const MouseDragEvent& e) {AddEvent(e);};
	mouse_->OnDragEnd = [&](const MouseDragEvent& e) {AddEvent(e);};
	mouse_->OnWheel = [&](const MouseWheelEvent& e) {AddEvent(e);};
	keyboard_->OnKeyDown = [&](const KeyEvent& e) {AddEvent(e);};
	keyboard_->OnKeyUp = [&](const KeyEvent& e) {AddEvent(e);};
	keyboard_->OnKeyRepeat = [&](const KeyEvent& e) {AddEvent(e);};
}

void InputManager::Update()
{

}
