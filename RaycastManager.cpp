#include"RaycastManager.h"

RaycastManager::RaycastManager(GameObject* parent)
{
}

RaycastManager::~RaycastManager()
{
}

void RaycastManager::Initialize()
{
	raycaster2D_ = Instantiate<Raycaster2D>(this);
	raycaster3D_ = Instantiate<Raycaster3D>(this); 
}

void RaycastManager::Update()
{
	raycaster2D_->Raycast();
	raycaster3D_->Raycast();
}
