#pragma once
#include<string>
#include<unordered_set>
#include"Engine/GameObject.h"

using std::unordered_set;

class GroupBase : public GameObject {
public:
	using ObjectList = unordered_set<GameObject*>;
};