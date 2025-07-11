#pragma once
#include "Object3D.h"
#include "TriggerStatusFactory.h"
class TriggerData :
    public Object3D
{
public:
	TriggerData(GameObject* parent);
	~TriggerData();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	void SetTriggerData(TRIGGER _trigger) { trigger_ = _trigger; }
	TRIGGER GetTriggerData() { return trigger_; }

	void SetTarget(string _target) { target_ = _target; }
	const string& GetTarget()const { return target_; }
private:
	string target_;
	TRIGGER trigger_;

	TriggerStatus t_status_;
};

