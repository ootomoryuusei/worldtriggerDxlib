#include "InputManager.h"

InputManager::InputManager(GameObject* parent)
{
}

void InputManager::Initialize()
{
	keyboard_ = Instantiate<Keyboard>(this);
	mouse_ = Instantiate<Mouse>(this);
	raycastManager_ = Instantiate<RaycastManager>(this);

	mouse_->OnClick = [&](const ClickEvent& e) {AddEvent(e);};
	mouse_->OnDoubleClick = [&](const DoubleClickEvent& e) {AddEvent(e);};
	mouse_->OnPress = [&](const PressEvent& e) {AddEvent(e);};
	mouse_->OnRelease = [&](const PressEvent& e) {AddEvent(e);};
	mouse_->OnDrag = [&](const DragEvent& e) {AddEvent(e);};
	mouse_->OnDragStart = [&](const DragEvent& e) {AddEvent(e);};
	mouse_->OnDragEnd = [&](const DragEvent& e) {AddEvent(e);};
	mouse_->OnWheel = [&](const WheelEvent& e) {AddEvent(e);};
	keyboard_->OnKeyDown = [&](const KeyEvent& e) {AddEvent(e);};
	keyboard_->OnKeyUp = [&](const KeyEvent& e) {AddEvent(e);};
	keyboard_->OnKeyRepeat = [&](const KeyEvent& e) {AddEvent(e);};
}

void InputManager::Update()
{
	XMFLOAT3 m_pos = mouse_->GetPosition();
	VECTOR rayOrigin = VGet(m_pos.x, m_pos.y, 0);
	VECTOR rayDir = VGet(m_pos.x, m_pos.y, 1);
	const auto& hit_obj = raycastManager_->RaycastFromMouse(m_pos.x,m_pos.y,rayOrigin,rayDir);
	EventDispatch(hit_obj.target, events_);
	events_.clear();
}
