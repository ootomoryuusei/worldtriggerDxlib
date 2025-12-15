#include "Amatori_Chika.h"
#include"Enemy.h"

AutoRegister<Amatori_Chika,CharacterFactory> Amatori_Chika::register_("Amatori_Chika");

Amatori_Chika::Amatori_Chika(GameObject* parent) : Character(parent)
{
	LoadModel("Assets//Model//human.mv1");

	transform_.position_ = { 0, 0, 0 };
	transform_.rotate_ = { 0, 0, 0 };

	movetime = 5.0f;
	flame = 1.0f / 60.0f;
	time = 0.0f;
}

Amatori_Chika::~Amatori_Chika()
{
}

void Amatori_Chika::Draw()
{
	Object3D::Draw();
}
