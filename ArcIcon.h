#pragma once
#include "Object2D.h"
class ArcIcon :
    public Object2D
{
public:
    ArcIcon(GameObject* parent, const std::string& name = "ArcIcon");
    virtual ~ArcIcon();

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void Release() override;
};

