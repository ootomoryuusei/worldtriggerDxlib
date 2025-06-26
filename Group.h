#pragma once
#include "Object3D.h"
#include<vector>
#include<list>

using std::vector;
using std::list;


class Group :
    public Object3D
{
public:
    Group(GameObject* parent, const std::string& name = "") : Object3D(parent) {}
protected:
    vector<GameObject*> members_;
};

