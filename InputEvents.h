#pragma once
#include<string>
#include<DirectXMath.h>

using namespace DirectX;

enum InputDeviceType {
	MOUSE,
	KEYBOARD,
	GAMEPAD
};

enum MouseClickType {
	NONE,
	PRESS,
	RELEASE,
	CLICK,
	DOBULECLICK,
	DRAGSTART,
	DRAGGING,
	DRAGEND
};

enum MouseButton {
	NONE,
	LEFT,
	RIGHT,
	MIDDLE,
	MOUSE_MAX
};

struct InputEvent {
	InputDeviceType device; //入力デバイス
	MouseButton m_Button = MouseButton::NONE;
	MouseClickType clickType = MouseClickType::NONE;
	int keyCode = -1; //キーコード
	XMFLOAT2 position = { 0,0 }; //マウス座標
	bool pressed = false; //押された
	bool released = false; //離された
};