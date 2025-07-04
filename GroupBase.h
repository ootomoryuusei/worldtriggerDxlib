#pragma once
#include<string>
#include<list>
#include"Engine/GameObject.h"

class GroupBase : public GameObject {
public:
	GroupBase(GameObject* parent) : GameObject(parent){}
	virtual ~GroupBase() = default;
};