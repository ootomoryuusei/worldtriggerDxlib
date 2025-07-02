#include "Trigger.h"

Trigger::Trigger(GameObject* parent) : Object3D(parent)
{
}

Trigger::~Trigger()
{
}

void Trigger::Initialize()
{
}

void Trigger::Update()
{
}

void Trigger::Draw()
{
}

bool Trigger::ArcInPoint(VECTOR _targer_pos,VECTOR _dir,float _fov)
{
	VECTOR toTarget = ToTarget(_targer_pos);
	toTarget = VNorm(toTarget);

	float dot = VDot(_dir, toTarget);
	float angle = ToRad(acosf(dot));

	if (angle <= _fov) {
		return true;
	}
	return false;
}