#pragma once
#include "Object2D.h"
#include<vector>

using std::vector;
using std::string;

class Icon :
    public Object2D
{
public:
    Icon(GameObject* parent);
    Icon(GameObject* parent,const string& name);
    ~Icon();
    virtual void Update() override;
    virtual void Draw() override;
private:
};
