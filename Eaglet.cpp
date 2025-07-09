#include "Eaglet.h"
#include "Character.h"
#include "GroupManager.h"


AutoRegister<Eaglet, TriggerFactory> Eaglet::register_("EAGLET");

Eaglet::Eaglet(GameObject* parent) : Trigger(parent)
{
	hModel = MV1LoadModel("Assets//Model//SampleEaglet.mv1");
	assert(hModel >= 0);
}

Eaglet::~Eaglet()
{
}

void Eaglet::Initialize()
{
}

void Eaglet::Update()
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

void Eaglet::Draw()
{
	
	MV1SetMatrix(hModel, matrix);
	MV1DrawModel(hModel);
}
