#pragma once
#include "Engine/GameObject.h"

class Player1;
class Tile;
class Icon;
class CsvReader;

enum SCENE {
	SELECT,
	STEP1
};

class PlayScene : public GameObject
{
public:
	PlayScene(GameObject* parent);
	~PlayScene();
	void Update() override;
	void Draw() override;
private:
	/*Player1* pl1;
	Tile* tile;
	Icon* icon;*/
	CsvReader* csv_;
};
