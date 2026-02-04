#pragma once
#include "Icon.h"
#include<vector>
#include<array>
#include"TriggerIcon.h"
#include"CharacterIcon.h"

class CsvReader;

//class TriggerIcon;
//class CharacterIcon;
//class CharacterSetUIFrame;
//class TriggerSetUIFrame;

using std::vector;
using std::array;

class TriggerIcons :
    public Icon
{
public:
    TriggerIcons(GameObject* parent);
    ~TriggerIcons();
    void Initialize() override;
    void Update() override;
    void Draw() override;

    const auto& GetpTIcons() const{ return pALLTIcons_; }

    void SetTriggers(CharacterIcon* pCharacterIcon, HANDS hands);

    void SetpCharacterIcon_(CharacterIcon* _pChracterIcon) { pCharacterIcon_ = _pChracterIcon; }
private:
    CsvReader* csv_;
    array<vector<TriggerIcon*>,static_cast<size_t>(HANDS::MAX)> pTIcons_;
    array<vector<TriggerIcon*>, static_cast<size_t>(HANDS::MAX)> pCanSet_;
    vector<TriggerIcon*> pSubTIcons_;
    vector<TriggerIcon*> pALLTIcons_;
    CharacterIcon* pCharacterIcon_;
    bool firstSet;

    void DefaultSetTriggers(CharacterIcon* pCharacterIcon, HANDS hands);
    void CreateCanSet(CharacterIcon* pCharacterIcon, HANDS hands);
};

