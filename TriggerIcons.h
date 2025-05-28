#pragma once
#include "Icon.h"
#include<vector>
#include"TriggerIcon.h"
#include"CharacterIcon.h"

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
    void Initialize() override;
    void Update() override;
    void Draw() override;

    auto GetpTIcons() { return pTIcons_; }

    void DefaultSetTriggers(CharacterIcon* pCharacterIcon);

    void SetTriggers(CharacterIcon* pCharacterIcon);

    void SetpCharacterIcon_(CharacterIcon* _pChracterIcon) { pCharacterIcon_ = _pChracterIcon; }
private:
    CsvReader* csv_;
    vector<TriggerIcon*> pMainTIcons_;
    vector<TriggerIcon*> pCanSetMain_;
    vector<TriggerIcon*> pSubTIcons_;
    vector<TriggerIcon*> pCanSetSub_;
    vector<TriggerIcon*> pTIcons_;
    CharacterIcon* pCharacterIcon_;
    bool firstSet;

    void CreateCanSetMain(CharacterIcon* pCharacterIcon);
};

