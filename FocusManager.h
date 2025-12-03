#pragma once
#include "Engine/GameObject.h"
class FocusManager :
    public GameObject
{
public:
	FocusManager(GameObject* parent);
	~FocusManager() {}
	void Initialize() override;
	void Update() override;

	void UpdateFocus(const HitInfo& hit) {

	}
private:
	GameObject* focusedObject_;
};

