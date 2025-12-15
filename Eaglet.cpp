#include "Eaglet.h"
#include "Character.h"
#include "GroupManager.h"
#include"TriggerData.h"


AutoRegister<Eaglet, TriggerFactory> Eaglet::register_("EAGLET");

Eaglet::Eaglet(GameObject* parent) : Trigger(parent)
{
	LoadModel("Assets//Model//SampleEaglet.mv1");
}

Eaglet::~Eaglet()
{
}

void Eaglet::Initialize()
{
	pData_ = Instantiate<TriggerData>(this);
}

void Eaglet::Update()
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

void Eaglet::Draw()
{
	Object3D::Draw();
}
