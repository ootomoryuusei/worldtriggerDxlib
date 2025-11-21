#pragma once
#include "Engine/GameObject.h"
#include"Keyboard.h"
#include"Mouse.h"
#include "InputComponent.h"

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

	void RegisterInputComponent(InputComponent* component);
private:
	vector<InputEvent> events_;
	vector<InputComponent*> inputComponents_;
	Keyboard* keyboard_;
	Mouse* mouse_;
};


