#pragma once
#include "Object3D.h"
#include<vector>
#include"TriggerIcon.h"
#include"TriggerIcons.h"
#include"CharacterIcon.h"
#include"TriggerSetUI.h"
#include"TriggerSetUIFrame.h"
#include"TriggerSetUIFrames.h"

#include"CharacterSetUIFrame.h"
#include"TriggerSetButton.h";

class CsvReader;

//class TriggerIcon;
//class CharacterIcon;
//class CharacterSetUIFrame;
//class TriggerSetUIFrame;

using std::vector;

class Icons :
    public Object3D
{
public:
    Icons(GameObject* parent);
    ~Icons();
    void Update() override;
    void Draw() override;

    auto GetpCIcons() { return pCIcons_; }
    /* auto GetpTSUIFrames() { return pTSUIFrames_; }*/
    auto GetpCSUIFrames() { return pCSUIFrames_; }
private:
    vector<CharacterIcon*> pCIcons_;
    /* vector<TriggerSetUIFrame*> pTSUIFrames_;*/
    vector<CharacterSetUIFrame*> pCSUIFrames_;
    vector<TriggerSetUI*> pTSUIs_;
    vector<TriggerSetButton*> pTSButtons_;
    vector<TriggerSetUIFrames*> pTSUIFSs_;
    vector<TriggerIcons*> pTIcons_;
    CsvReader* csv_;
    int FN2DLine;
    MYTRIGGER trigger;
    string DLC; //ディレクトリ
    vector<vector<bool>> button_;
    /*bool button[][MAX_SELECT_CHARACTER];*/
};


