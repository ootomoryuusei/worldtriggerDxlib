#pragma once
#include "Engine/GameObject.h"
#include"Keyboard.h"
#include"Mouse.h"

class InputManager :
    public GameObject
{
public:
	static InputManager* GetInstance(GameObject* parent = nullptr) {
		static InputManager instance(parent);
		return &instance;
	}

	InputManager(GameObject* parent);

	void Initialize() override;
	void Update() override;

	//各入力体のアクセス関数
	const Keyboard& GetKeyboard() const { return *keyboard_; }
	const Mouse& GetMouse() const { return *mouse_; }

	bool IsActionTriggerd(std::string actionName);
private:
	Keyboard* keyboard_;
	Mouse* mouse_;
};

