#include "Timer.h"

Timer::Timer(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//Timer.png");
	position = { 220, 10, 0 };
	canVisible_ = true;
}

Timer::~Timer()
{
}

void Timer::Update()
{
}
