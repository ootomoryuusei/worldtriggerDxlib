#pragma once
#include<functional>
#include<DirectXMath.h>
#include<variant>

using namespace DirectX;
using std::function;
using std::variant;
typedef int KeyCode;

using InputEvents = variant<MouseClickEvent, MouseDragEvent, MouseWheelEvent, KeyEvent>;

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