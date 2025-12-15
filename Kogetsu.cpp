#include "Kogetsu.h"
#include "Character.h"
#include "GroupManager.h"
#include"TriggerData.h"

AutoRegister<Kogetsu, TriggerFactory> Kogetsu::register_("KOGETSU");

Kogetsu::Kogetsu(GameObject* parent) : Trigger(parent)
{
	LoadModel("Assets//Model//SampleKogetsu.mv1");
}

Kogetsu::~Kogetsu()
{
}

void Kogetsu::Initialize()
{
	pData_ = Instantiate<TriggerData>(this);
}

void Kogetsu::Update()
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

void Kogetsu::Draw()
{
	Object3D::Draw();
}
