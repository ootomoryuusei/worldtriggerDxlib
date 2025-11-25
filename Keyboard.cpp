#include "Keyboard.h"
#include <DxLib.h>
#include "Time.h" // DeltaTime() 用

Keyboard::Keyboard(GameObject* parent) : GameObject(parent,"キーボード")
{
}

Keyboard::~Keyboard()
{
}

void Keyboard::Initialize()
{
}

void Keyboard::Update()
{
	k_prev = k_now;
	for (int key = 0;key < 256;key++) {
		k_now[key] = (CheckHitKey(key) != 0);
	}

	for (int key = 0;key < 256;key++) {
		if (k_now[key] && !k_prev[key] && OnKeyDown) OnKeyDown({ key });
		if (!k_now[key] && k_prev[key] && OnKeyUp) OnKeyUp({ key });
		if (k_now[key] && k_prev[key] && OnKeyRepeat) OnKeyRepeat({ key });
	}
}