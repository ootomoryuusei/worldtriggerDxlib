#pragma once
#include "Engine/GameObject.h"
#include"Keyboard.h"
#include"Mouse.h"
#include "InputComponent.h"
#include<functional>

using std::function;

class InputManager :
    public GameObject
{
public:
	InputManager(GameObject* parent);
	~InputManager(){}

	void Initialize() override;
	void Update() override;

private:
	Keyboard* keyboard_;
	Mouse* mouse_;
};


