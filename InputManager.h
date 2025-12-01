#pragma once
#include "Engine/GameObject.h"
#include"Keyboard.h"
#include"Mouse.h"
#include "InputComponent.h"
#include<functional>
#include<variant>
#include<type_traits>

using std::function;

class InputManager :
    public GameObject
{
public:
	InputManager(GameObject* parent);
	~InputManager(){}

	void Initialize() override;
	void Update() override;

	void AddEvent(const DeviceEvents& event) {
		events_.push_back(event);
	}

	void EventDispatch(GameObject* obj, const DeviceEvents& events) {
		std::visit([&](auto const& event) {obj->DeviceEvent(event);},events);
	}
private:
	Keyboard* keyboard_;
	Mouse* mouse_;
	vector<DeviceEvents> events_;
};


