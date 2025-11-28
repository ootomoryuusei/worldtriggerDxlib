#pragma once
#include "Engine/GameObject.h"
#include"Keyboard.h"
#include"Mouse.h"
#include "InputComponent.h"
#include<functional>
#include<variant>

using std::function;
using std::visit;

class InputManager :
    public GameObject
{
public:
	InputManager(GameObject* parent);
	~InputManager(){}

	void Initialize() override;
	void Update() override;

	void AddEvent(const InputEvents& event) {
		events_.push_back(event);
	}

	void EventDispatch(GameObject* obj, const InputEvents& events) {
		visit([&](auto&& event) {
			obj->DeviceEvent(event)
			}, events);
	}

private:
	Keyboard* keyboard_;
	Mouse* mouse_;
	vector<InputEvents> events_;
};


