#pragma once
#include "Icon.h"
#include<vector>
#include"TriggerIcon.h"


class CsvReader;

//class TriggerIcon;
//class CharacterIcon;
//class CharacterSetUIFrame;
//class TriggerSetUIFrame;

using std::vector;

class TriggerIcons :
    public Icon
{
public:
    TriggerIcons(GameObject* parent);
    ~TriggerIcons();
    void Update() override;
    void Draw() override;

    auto GetpTIcons() { return pTIcons_; }
private:
    CsvReader* csv_;
    int FN2DLine;
    vector<TriggerIcon*> pMainTIcons_;
    vector<TriggerIcon*> pSubTIcons_;
    vector<TriggerIcon*> pTIcons_;
};

