#include "Shield.h"
#include<list> 
#include"CharacterGroup.h"
#include "GroupManager.h"

using std::list;

AutoRegister<Shield, TriggerFactory> Shield::register_("SHIELD");

Shield::Shield(GameObject* parent) : Trigger(parent)
{
	hModel = MV1LoadModel("Assets//Model//SampleShield.mv1");
	assert(hModel >= 0);
}

Shield::~Shield()
{
}

void Shield::Initialize()
{
}

void Shield::Update()
{
	auto groupManger = GetParent()->GetParent()->GetParent()->GetParent()->FindGameObject<GroupManager>();
	auto target_group = groupManger->GetGroup(target_);
	list<Character*> target_list = target_group->FindGameObjects<Character>();
	for (auto& itr : target_list) {
		if (ArcInPoint(itr->Get3DPosition(), { 0,0,1 }, trigger_.arc.percent * 3.6)) {

		}
	}
	matrix = Object3D::ChangeFLOAT3ToMATRIX(position, rotation);
}

void Shield::Draw()
{
	MV1SetMatrix(hModel, matrix);
	MV1DrawModel(hModel);
}
