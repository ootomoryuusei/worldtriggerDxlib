#pragma once
#include"Engine/GameObject.h"
#include"Raycaster2D.h"
#include"Raycaster3D.h"

class RaycastManager : public GameObject
{
public:
	RaycastManager(GameObject* parent);
	~RaycastManager();

	void Initialize() override;
	void Update() override;

private:
	Raycaster2D* raycaster2D_;
	Raycaster3D* raycaster3D_;
};

