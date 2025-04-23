#include "MoveMentsLoad.h"
#include"UnitIcons.h"
#include"TileIcons.h"

MoveMentsLoad::MoveMentsLoad(GameObject* parent) : Icon(parent)
{
}

MoveMentsLoad::~MoveMentsLoad()
{
}

void MoveMentsLoad::Initialize()
{
}

void MoveMentsLoad::Update()
{
	UnitIcons* pUnitIcons = GetParent()->GetParent()->FindGameObject<UnitIcons>();
	pUnitIcons->GetpUnitIcons()[createNum_]->GetMoveMent();
}

void MoveMentsLoad::Draw()
{
	DrawMoveLine();
}

void MoveMentsLoad::DrawMoveLine()
{
	UnitIcons* pUnitIcons = GetParent()->GetParent()->FindGameObject<UnitIcons>();
	TileIcons* pTileIcons = GetParent()->GetParent()->FindGameObject<TileIcons>();

	//const auto& movement = pUnitIcons->GetpUnitIcons()[createNum_]->GetMoveMent();
	//if (movement.empty()) return;

	//XMFLOAT2 half_t_IconSize = {
	//	pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D().halfX,
	//	pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D().halfY
	//};

	//// �ŏ��̃X�^�[�g�͌��݈ʒu
	//XMFLOAT2 startPoint = {
	//	pUnitIcons->GetpUnitIcons()[createNum_]->Get3DPosition().x,
	//	pUnitIcons->GetpUnitIcons()[createNum_]->Get3DPosition().y
	//};

	//for (size_t i = 0; i < movement.size(); ++i) {
	//	int nextTileNum = movement[i];

	//	XMFLOAT2 endPoint = {
	//		pTileIcons->GetpTIcon()[nextTileNum]->Get3DPosition().x,
	//		pTileIcons->GetpTIcon()[nextTileNum]->Get3DPosition().y
	//	};

	//	XMFLOAT2 vec = {
	//		endPoint.x - startPoint.x,
	//		endPoint.y - startPoint.y
	//	};

	//	float maxlength = sqrt(vec.x * vec.x + vec.y * vec.y);
	//	if (maxlength == 0) {
	//		// �X�^�[�g�ƃG���h�������Ȃ�X�L�b�v
	//		continue;
	//	}

	//	XMFLOAT2 dir = {
	//		vec.x / maxlength,
	//		vec.y / maxlength
	//	};

	//	int pointNum = 5;
	//	int spaceNum = pointNum - 1;
	//	int num = pointNum + spaceNum;

	//	float interval = maxlength / (num - 1);

	//	for (int j = 0; j < num; ++j) {
	//		// ���ׂĂ̓_��`�悵�Ă݂�
	//		if (j % 2 == 0) {
	//			XMFLOAT2 pos = {
	//		startPoint.x + dir.x * interval * j + half_t_IconSize.x,
	//		startPoint.y + dir.y * interval * j + half_t_IconSize.y
	//			};

	//			DrawCircleAA(pos.x, pos.y, interval / 2.0f, 20, GetColor(255, 0, 0), TRUE);
	//		}
	//	}

	//	// ���̎n�_�ɍX�V
	//	startPoint = endPoint;
	//}

	const auto& movement = pUnitIcons->GetpUnitIcons()[createNum_]->GetMoveMent();
	if (movement.size() < 2) return; // �J�n�_ + 1�_�ȏ�̈ړ����K�v

	XMFLOAT2 half_t_IconSize = {
		pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D().halfX,
		pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D().halfY
	};

	// �X�^�[�g�� movement[0] �ɂ���^�C���ʒu
	XMFLOAT2 startPoint = {
		pTileIcons->GetpTIcon()[movement[0]]->Get3DPosition().x,
		pTileIcons->GetpTIcon()[movement[0]]->Get3DPosition().y
	};

	for (size_t i = 1; i < movement.size(); ++i) {
		int nextTileNum = movement[i];

		XMFLOAT2 endPoint = {
			pTileIcons->GetpTIcon()[nextTileNum]->Get3DPosition().x,
			pTileIcons->GetpTIcon()[nextTileNum]->Get3DPosition().y
		};

		XMFLOAT2 vec = {
			endPoint.x - startPoint.x,
			endPoint.y - startPoint.y
		};

		float maxlength = sqrt(vec.x * vec.x + vec.y * vec.y);
		if (maxlength == 0) continue;

		XMFLOAT2 dir = {
			vec.x / maxlength,
			vec.y / maxlength
		};

		int pointNum = 5;
		int spaceNum = pointNum - 1;
		int num = pointNum + spaceNum;
		float interval = maxlength / (num - 1);

		for (int j = 0; j < num; ++j) {
			if (j % 2 == 0) {
				XMFLOAT2 pos = {
					startPoint.x + dir.x * interval * j + half_t_IconSize.x,
					startPoint.y + dir.y * interval * j + half_t_IconSize.y
				};

				DrawCircleAA(pos.x, pos.y, interval / 2.0f, 20, GetColor(255, 0, 0), TRUE);
			}
		}

		startPoint = endPoint;
	}
}
