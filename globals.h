#pragma once
#if 0
#include<string>
#include <DxLib.h>

using std::string;

struct TRIGGER {
	string trigger; //�g���K�[��
	bool IsSelected; //�I������Ă��邩�ǂ���
	float angle; //�A���O��
	float startAngle; //�͂��߂̃A���O��
	float rangeSize; //�˒���x���͈͂̒���
	int tNum; //trigger�i���o�[
};

struct MYTRIGGER {
	TRIGGER Main[4];
	TRIGGER Sub[4];
};

struct HALF {
	int halfX, halfY;
};

struct HALF_F {
	float halfX, halfY;
};

struct SIZE_2D {
	int x, y, halfX, halfY;
	SIZE_2D(int x, int y, int halfX, int halfY) : x(x), y(y), halfX(halfX), halfY(halfY) {}
	HALF GetHalfSize() { return { x / 2,y / 2 }; }
};

struct SIZE_F_2D {
	float x, y, halfX, halfY;
	SIZE_F_2D(float x, float y, float halfX, float halfY) : x(x), y(y), halfX(halfX), halfY(halfY) {}
	HALF_F GetHalfSize() { return { x / 2,y / 2 }; }
};

struct TILEDATA {
	VECTOR position;
	int num;
};

struct CHARACTER_STATUS
{
	int move, attack, speed, defense;
};

#endif