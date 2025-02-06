#pragma once
#include"Object3D.h"
class ShealdIcon :
    public Object3D
{
public:
	ShealdIcon(GameObject* parent);
	~ShealdIcon();
	void Load(const std::string _fileName);
	void Update() override;
	void Draw() override;
private:
	SIZE_2D graphSize_; //アイコンの画像サイズ
	std::string fileName_;
};

