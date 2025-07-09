#pragma once
#include "Object3D.h"
class TriggerData :
    public Object3D
{
public:
	TriggerData(GameObject* parent);
	~TriggerData();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
	string target_;
	TRIGGER trigger_;
};

