#pragma once
#include "Icon.h"
#include<vector>

using std::vector;

class CharacterSetUIFrame :
    public Icon
{
public:
    CharacterSetUIFrame(GameObject* parent);
    ~CharacterSetUIFrame();
    void Update() override;
    void Draw() override;

    void SetIsSet(bool _isSet) { isSet_ = _isSet; }
    bool GetIsSet() { return isSet_; }
private:
    bool isSet_;
};

