#pragma once
#include "Engine/GameObject.h"
#include"MoveMentsLoad.h"
#include<vector>

using std::vector;

class MoveMentsLoads :
    public GameObject
{
public:
	MoveMentsLoads(GameObject* parent);
	~MoveMentsLoads();
	void Initialize() override;
	void Update() override;

	auto GetpMoveMentsLoads() { return pMoveMentsLoads_; }
private:
	vector<MoveMentsLoad*> pMoveMentsLoads_;
};

