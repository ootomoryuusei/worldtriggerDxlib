#include "InputManager.h"

InputManager::InputManager(GameObject* parent)
{
}

void InputManager::Initialize()
{
	keyboard_ = Instantiate<Keyboard>(this); //キーボード
	mouse_ = Instantiate<Mouse>(this); //マウス
	raycastManager_ = Instantiate<RaycastManager>(this); //レイキャストマネージャー

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
	HitInfo hit_obj;
	hit_obj = raycastManager_->RaycastFromMouse(m_pos.x, m_pos.y, rayOrigin, rayDir);
	for (auto& event : events_) {
		EventDispatch(hit_obj.target, event); // イベントを対象オブジェクトに送る
	}
	events_.clear();
}
