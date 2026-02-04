#pragma once
#include<string>
#include<array>

using std::string;
using std::array;

const int MAX_MAP_HIGHT = 11;
const int MAX_MAP_WIDTH = 11;
const int MAX_SELECT_CHARACTER = 3;
const int MAX_TRIGGER_HANDS = 2;
const int MAX_CAN_SET_TRIGGER = 4;

struct OBJ_SIZE {
	int x, y, z;
	void set(int _x, int _y, int _z) {
		x = _x, y = _y, z = _z;
	}
	void set(XMFLOAT3 size) {
		x = size.x; y = size.y; z = size.z;
	}
	int halfX() const { return x / 2; }
	int halfY() const { return y / 2; }
	int halfZ() const { return z / 2; }
	XMINT3 half() const { return { halfX(),halfY(),halfZ() }; }
	XMINT3 size() const { return { x,y,z }; }
};

struct OBJ_SIZE_F {
	float x, y, z;
	void set(float _x, float _y, float _z) {
		x = _x; y = _y; z = _z;
	}
	void set(XMFLOAT3 size) {
		x = size.x; y = size.y; z = size.z;
	}
	float halfX() const { return x / 2; }
	float halfY() const { return y / 2; }
	float halfZ() const { return z / 2; }
	XMFLOAT3 half() const { return { halfX(), halfY(), halfZ() }; }
	XMFLOAT3 size() const { return { x,y,z }; }
};

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

enum class STATUS {
	MOVE = 0,
	TRION,
	ATTACK,
	AVOIDANCE,
	DEFENCE,
	SUPPORT,
	TECHNIQUE,
	SIZE
};
struct CHARACTER_STATUS
{
	array<int, static_cast<size_t>(STATUS::SIZE)> status_;
	/*int status[static_cast<size_t>(STATUS::SIZE)];*/
};

enum class STEP {
	FIRST = 0,
	SECONDE,
	THIRD,
	STEP_MAX
};


enum class HANDS {
	RIGHT_HAND = 0,
	LEFT_HAND,
	MAX
};

enum class WEAPON {
	FREE,
	KOGETSU,
	SHIELD,
	ASTEROID,
	EAGLET,
	WEAPON_MAX
};

template<class T>
size_t ToIndex(T t) {
	return static_cast<size_t>(t);
}

