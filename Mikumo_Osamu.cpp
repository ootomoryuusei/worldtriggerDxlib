#include "Mikumo_Osamu.h"

AutoRegister<Mikumo_Osamu,CharacterFactory> Mikumo_Osamu::register_("Mikumo_Osamu");

Mikumo_Osamu::Mikumo_Osamu(GameObject* parent) :Character(parent)
{
	LoadModel("Assets//Model//human.mv1");
	
	transform_.position_ = { 0,0,0 };
	transform_.rotate_ = { 0,0,0 };

	movetime = 5.0f;
	flame = 1.0f / 60.0f;
	time = 0.0f;
}

Mikumo_Osamu::~Mikumo_Osamu()
{
}

void Mikumo_Osamu::Draw()
{
	Object3D::Draw();
}
