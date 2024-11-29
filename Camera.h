#pragma once
#include "Object3D.h"

class Camera : public Object3D {
public:
	Camera(GameObject* parent);
	~Camera();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// カメラ振動を開始する
	/// </summary>
	/// <param name="v">衝撃の方向</param>
	void Vibration(VECTOR v);

private:
	VECTOR lookTarget;
	float vibTimer;	// 時間を測る変数
	VECTOR vibParam; // 引数で指定された値
	// 揺れ幅を持つ変数
	// 揺れ量を持つ変数
	VECTOR vibValue; // この値を加える
};