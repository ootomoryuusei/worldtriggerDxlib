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
	void SetStatus(CHARACTER_STATUS _status) { status_ = _status; }
	void SetMyTrigger(MYTRIGGER _myTrigger) { myTrigger_ = _myTrigger; }
	string GetName() { return name_; }
	CHARACTER_STATUS GetStatus() { return status_; }
	MYTRIGGER GetMyTrigger() { return myTrigger_; }

	void DefaultSetStatus(string _name);
	void DefaultSetMyTrigger(string _name);
private: 
	CsvReader* csv_;
	CHARACTER_STATUS status_;
	MYTRIGGER myTrigger_;
	string name_;
};

