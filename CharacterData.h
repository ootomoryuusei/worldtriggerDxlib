#pragma once
#include "Object3D.h"
#include"CharacterStatusFactory.h"
#include "TriggerStatusFactory.h"

class CsvReader;
class CharacterGroup;

class CharacterData :
    public Object3D
{
public:
	CharacterData(GameObject* parent);
	~CharacterData();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	void SetCharacterStatus(CharacterStatus _status) { c_status_ = _status; }
	CharacterStatus GetCharacterStatus() { return c_status_; }
	void SetTriggerStatus(TriggerStatus _status) { t_status_ = _status; }
	TriggerStatus GetTriggerStatus() { return t_status_; }
	void SetMyTrigger(MYTRIGGER _myTrigger) { myTrigger_ = _myTrigger; }
	MYTRIGGER GetMyTrigger() { return myTrigger_; }

	void DefaultSetStatus(string _name);
	void DefaultSetMyTrigger(string _name);

	void SetTarget(string _target) { target_ = _target; }
	const string& GetTarget()const { return target_; }
private: 
	CsvReader* csv_;
	MYTRIGGER myTrigger_;
	string target_;
	CharacterStatus c_status_;
	TriggerStatus t_status_;
};

