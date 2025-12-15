#include "Shield.h"
#include<list> 
#include"CharacterGroup.h"
#include "GroupManager.h"
#include"TriggerData.h"

AutoRegister<Shield, TriggerFactory> Shield::register_("SHIELD");

Shield::Shield(GameObject* parent) : Trigger(parent)
{
	LoadModel("Assets//Model//SampleShield.mv1");
}

Shield::~Shield()
{
}

void Shield::Initialize()
{
	pData_ = Instantiate<TriggerData>(this);
}

void Shield::Update()
{
	auto groupManger = GetParent()->GetParent()->GetParent()->GetParent()->FindGameObject<GroupManager>();
	string target = pData_->GetTarget();
	auto target_group = groupManger->GetGroup(target);
	list<Character*> target_list = target_group->FindGameObjects<Character>();
	float angle = pData_->GetTriggerData().arc.angle;
	for (auto& itr : target_list) {
		if (ArcInPoint(itr->GetPosition(), { 0,0,1 },angle)) {

		}
	}
	Object3D::Update();
}

void Shield::Draw()
{
	Object3D::Draw();
}
