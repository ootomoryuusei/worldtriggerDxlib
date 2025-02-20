#pragma once
#include "Object3D.h"
#include<vector>
#include"TriggerSetUIFrame.h"
#include"CharacterSetUIFrame.h"
#include"TriggerIcon.h"
#include"CharacterIcon.h"

class CsvReader;

//class TriggerIcon;
//class CharacterIcon;
//class CharacterSetUIFrame;
//class TriggerSetUIFrame;

using std::vector;

class TriggerIcons :
    public Object3D
{
public:
    TriggerIcons(GameObject* parent);
    ~TriggerIcons();
    void Update() override;
    void Draw() override;

    auto GetpTIcons() { return pTIcons_; }
    auto GetpCIcons() { return pCIcons_; }
    auto GetpTSUIFrames() { return pTSUIFrames_; }
    auto GetpCSUIFrames() { return pCSUIFrames_; }

private:
    vector<TriggerIcon*> pTIcons_;
    vector<CharacterIcon*> pCIcons_;
    vector<TriggerSetUIFrame*> pTSUIFrames_;
    vector<CharacterSetUIFrame*> pCSUIFrames_;
    CsvReader* csv_;
    int FN2DLine;
    MYTRIGGER trigger;
    string DLC; //ディレクトリ
};

