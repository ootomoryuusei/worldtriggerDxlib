#include "Kuga_Yuuma.h"

AutoRegister<Kuga_Yuuma,CharacterFactory> Kuga_Yuuma::register_("Kuga_Yuuma");

Kuga_Yuuma::Kuga_Yuuma(GameObject* parent) : Character(parent)
{
	LoadModel("Assets//Model//human.mv1");

	transform_.position_ = {0,0,0};
	transform_.rotate_ = { 0,0,0 };

	
	movetime = 5.0f;
	flame = 1.0f / 60.0f;
	time = 0.0f;
}

Kuga_Yuuma::~Kuga_Yuuma()
{
}

void Kuga_Yuuma::Draw()
{
	Object3D::Draw();
}
