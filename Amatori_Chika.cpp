#include "Amatori_Chika.h"
#include"Enemy.h"

AutoRegister<Amatori_Chika,CharacterFactory> Amatori_Chika::register_("Amatori_Chika");

Amatori_Chika::Amatori_Chika(GameObject* parent) : Character(parent)
{
	hModel = MV1LoadModel("Assets//Model//human.mv1");
	assert(hModel >= 0);

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);

	movetime = 5.0f;
	flame = 1.0f / 60.0f;
	time = 0.0f;
}

Amatori_Chika::~Amatori_Chika()
{
}

void Amatori_Chika::Initialize()
{
	
}

void Amatori_Chika::Update()
{
	pEnemy_ = GetParent()->GetParent()->FindGameObject<Enemy>();
	e_characterlist_ = pEnemy_->FindGameObjects<Character>();

	switch (state_)
	{
	case FIRST: break;
	case SECONDE: break;
	case THIRD:
	{
		for (auto& itr : e_characterlist_) {
			VECTOR e_pos = itr->Get3DPosition();
			ArcInPoint(e_pos,40);
		}
		MoveMent();
		break;
	}
	default:
		break;
	}
}

void Amatori_Chika::Draw()
{
	MATRIX mModel = Object3D::ChangeFLOAT3ToMATRIX(position, rotation);
	MV1SetMatrix(hModel, mModel);
	MV1DrawModel(hModel);
}
