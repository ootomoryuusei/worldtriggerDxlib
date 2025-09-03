#include "Asteroid.h"
#include "GroupManager.h"
#include<list>
#include "Character.h"
#include"TriggerData.h"

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
	pData_ = Instantiate<TriggerData>(this);
}

void Asteroid::Update()
{
	auto groupManger = GetParent()->GetParent()->GetParent()->GetParent()->FindGameObject<GroupManager>();
	string target = pData_->GetTarget();
	auto target_group = groupManger->GetGroup(target);
	list<Character*> target_list = target_group->FindGameObjects<Character>();
	float angle = pData_->GetTriggerData().arc.angle;
	for (auto& itr : target_list) {
		if (ArcInPoint(itr->Get3DPosition(), { 0,0,1 },angle)) {

		}
	}
	matrix = ToMATRIX(position, rotation);
}

void Asteroid::Draw()
{
	MV1SetMatrix(hModel, matrix);
	MV1DrawModel(hModel);
}
