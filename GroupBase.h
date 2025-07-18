#pragma once
#include"Engine/GameObject.h"

class GroupBase : public GameObject {
public:
	virtual ~GroupBase() = default;
	virtual void Remove(GameObject* obj) = 0;
};