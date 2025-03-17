#pragma once
#include "Object3D.h"
#include<vector>
#include"TriggerIcon.h"
#include"CharacterIcon.h"

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

private:

 /*   CsvReader* csv_;
    int FN2DLine;*/
    MYTRIGGER trigger;
    //string DLC; //ディレクトリ
    vector<vector<bool>> button_;
    /*bool button[][MAX_SELECT_CHARACTER];*/
};


