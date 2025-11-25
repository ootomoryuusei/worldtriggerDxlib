#pragma once
#include<functional>
#include<DirectXMath.h>

using namespace DirectX;
using std::function;
typedef int KeyCode;

enum InputEventType {
	NONE,
	MOUSE_DOWN,
	MOUSE_UP,
	MOUSE_MOVE,
	MOUSE_CLICK
};

enum MouseButton {
	LEFT,
	RIGHT,
	MIDDLE,
	MOUSE_MAX
};

struct MouseClickEvent
{
	MouseButton button;
	XMFLOAT2 position;
};

struct MouseDragEvent
{
	MouseButton button;
	XMFLOAT2 start;
	XMFLOAT2 current;
	XMFLOAT2 delta;
};

struct MouseWheelEvent
{
	float delta;
};

struct KeyEvent
{
	KeyCode key;
};