#pragma once
#include "Object3D.h"

class CsvReader;

class CharacterData :
    public Object3D
{
public:
	CharacterData(GameObject* parent);
	~CharacterData();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	void SetName(string _name) { name_ = _name; }
private: 
	CsvReader* csv_;
	CHARACTER_STATUS status_;
	MYTRIGGER myTrigger_;
	string name_;

};

