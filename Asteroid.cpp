#include "Asteroid.h"
#include "GroupManager.h"
#include<list>
#include "Character.h"

using std::list;

AutoRegister<Asteroid, TriggerFactory> Asteroid::register_("ASTEROID");

Asteroid::Asteroid(GameObject* parent) : Trigger(parent)
{
	hModel = MV1LoadModel("Assets//Model//SampleAsteroid.mv1");
	assert(hModel >= 0);
}

Asteroid::~Asteroid()
{
}

void Asteroid::Initialize()
{
}

void Asteroid::Update()
{
	auto groupManger = GetParent()->GetParent()->GetParent()->GetParent()->FindGameObject<GroupManager>();
	auto target_group = groupManger->GetGroup(target_);
	list<Character*> target_list = target_group->FindGameObjects<Character>();
	for (auto& itr : target_list) {
		if (ArcInPoint(itr->Get3DPosition(), { 1,0,0 }, trigger_.arc.angle)) {

		}
	}
}

void Asteroid::Draw()
{
	MATRIX mModel = Object3D::ChangeFLOAT3ToMATRIX(position, rotation);
	MV1SetMatrix(hModel, mModel);
	MV1DrawModel(hModel);
}
