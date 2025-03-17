#pragma once
#include "Icon.h"
class Timer :
    public Icon
{
public:
	Timer(GameObject* parent);
	~Timer();
	void Update() override;
private:

};

