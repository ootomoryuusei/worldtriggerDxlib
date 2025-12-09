#pragma once
#include<functional>
#include<DirectXMath.h>
#include<variant>
#include<type_traits>

using namespace DirectX;
using std::function;
using std::variant;
typedef int KeyCode;

enum MouseButton {
	LEFT,
	RIGHT,
	MIDDLE,
	MOUSE_MAX
};

struct ClickEvent{MouseButton button;XMFLOAT2 position;}; //マウスクリックイベント
struct DoubleClickEvent { MouseButton button; XMFLOAT2 position; }; //マウスダブルクリックイベント;
struct PressEvent { MouseButton button; XMFLOAT2 position; }; //マウスプレスイベント
struct DragEvent { MouseButton button;XMFLOAT2 start;XMFLOAT2 current;XMFLOAT2 delta; }; //マウスドラッグイベント
struct WheelEvent { float delta; }; //マウスホイールイベント

struct KeyEvent
{
	KeyCode key;
};

using DeviceEvents = variant<ClickEvent,DoubleClickEvent,PressEvent,DragEvent, WheelEvent, KeyEvent>;
