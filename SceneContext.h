#pragma once
#include "Engine/GameObject.h"
#include"RaycastManager.h"

class SceneContext :
    public GameObject
{
public:
    RaycastManager* raycastManager = nullptr;
    SceneContext(GameObject* parent) :
        GameObject(parent,"SceneContext"){ }

    ~SceneContext(){}

    void Initialize() override {
        raycastManager = Instantiate<RaycastManager>(this);
    }
};

