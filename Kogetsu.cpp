#include "Kogetsu.h"
#include "Character.h"
#include "GroupManager.h"


AutoRegister<Kogetsu, TriggerFactory> Kogetsu::register_("KOGETSU");

Kogetsu::Kogetsu(GameObject* parent) : Trigger(parent)
{
	hModel = MV1LoadModel("Assets//Model//SampleKogetsu.mv1");
	assert(hModel >= 0);
}

Kogetsu::~Kogetsu()
{
}

void Kogetsu::Initialize()
{
}

void Kogetsu::Update()
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

void Kogetsu::Draw()
{
	MV1SetMatrix(hModel, matrix);
	MV1DrawModel(hModel);
}
