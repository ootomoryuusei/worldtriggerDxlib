#pragma once
#include "Object3D.h"
#include<vector>

class Icon;

using std::vector;

class UIManager :
    public Object3D
{
public:
    UIManager(GameObject* parent);
    ~UIManager();
    void Initialize() override;
    void Update() override;
    void Draw() override;

    void AddUI(Icon* pIcon_) { pIcons_.push_back(pIcon_); }

    const auto& GetpUIs() const { return pIcons_; }
private:
    vector<Icon*> pIcons_;
};

