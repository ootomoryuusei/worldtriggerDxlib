#pragma once
#include<string>

using std::string;

const int MAX_MAP_HIGHT = 11;
const int MAX_MAP_WIDTH = 11;
const int MAX_SELECT_CHARACTER = 3;
const int MAX_TRIGGER_HANDS = 2;
const int MAX_CAN_SET_TRIGGER = 4;

struct ARC_DATA {
	float percent;
	float startPercent;
	float angle;
	float rangeSize;
};

struct TRIGGER {
	string triggerName; //トリガー名
	bool IsSelected; //選択されているかどうか
	ARC_DATA arc; //トリガーの範囲(円弧のデータ)
};

struct TRIGGERS {
	TRIGGER trigger[4];
};

struct MYTRIGGER {
	TRIGGERS myTrigger[2];
};

struct TILEDATA {
	VECTOR pos;
	VECTOR offset;
	int num;
};

struct MOVEMENT {
	VECTOR movement;
	string movename;
};

enum STATUS {
	MOVE = 0,
	TRION,
	ATTACK,
	AVOIDANCE,
	DEFENCE,
	SUPPORT,
	TECHNIQUE,
	STATUS_MAX
};
struct CHARACTER_STATUS
{
	int status[STATUS_MAX];
};

enum STEP {
	FIRST = 0,
	SECONDE,
	THIRD,
	STEP_MAX
};


enum HANDS {
	RIGHT_HAND = 0,
	LEFT_HAND,
	MAX
};

enum WEAPON {
	FREE,
	KOGETSU,
	SHIELD,
	ASTEROID,
	EAGLET,
	WEAPON_MAX
};
