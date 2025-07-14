#include "TriggerArcIcon.h"
#include"Mouse.h"
#include"TileIcons.h"
#include"UnitIcons.h"
#include <algorithm>

using std::clamp;

TriggerArcIcon::TriggerArcIcon(GameObject* parent) : Icon(parent)
{
	step_ = SECONDE;

	firstSet = false;
	moveing = false;

	totalTime = 10.0f;

	elapsedTime = 0.0f;
}

TriggerArcIcon::~TriggerArcIcon()
{
}

void TriggerArcIcon::Initialize()
{
	percent = 5.0f;
	startPercent = -5.0f;
	VECTOR prevVec = { 0,0,0 };
}

void TriggerArcIcon::Update()
{
	if (canVisible_) {
		switch (step_)
		{
		case FIRST:
		{
			canVisible_ = false;
		}
			break;
		case SECONDE:
		{
			canVisible_ = true;
			calculateArc();
			break;
		}
		case THIRD:
			
			if (!firstSet) {
				for (auto& itr : angle) {
					dq_angle.push_back(itr);
				}
				firstSet = true;
				moveing = true;
			}
			if (moveing) {
				if (dq_angle.size() >= 2) {
					auto it = dq_angle.begin();
					auto startIndex = *it;
					auto targetIndex = *(++it);

					VECTOR start = {startIndex.x,startIndex.y,0};
					VECTOR target = {targetIndex.x,targetIndex.y,0};
					float Percent = elapsedTime / totalTime;
					Percent = clamp(Percent, 0.0f, 1.0f);
					startPercent = Lerp3D(start, target, Percent).x;
					percent = Lerp3D(start, target, Percent).y;
					if (Percent >= 1.0f) {
						// �ړ����� �� ���̋�Ԃ�
						elapsedTime = 0.0f;
						dq_angle.pop_front();
					}
				}

				if (dq_angle.size() < 2) {
					moveing = false;
				}
				elapsedTime += Time::DeltaTime();
			}
			break;
		default:
			break;
		}
	}
}

void TriggerArcIcon::Draw()
{
	TileIcons* pTileIcons = GetParent()->GetParent()->GetParent()->FindGameObject<TileIcons>();
	SIZE_F_2D tileSize = pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D();
	XMFLOAT2 DrawCenterPos = { position.x + (graphSizeF_.halfX - tileSize.halfX),
								position.y + (graphSizeF_.halfY - tileSize.halfY) };

	if (canVisible_) {
		DrawCircleGaugeF(DrawCenterPos.x, DrawCenterPos.y, percent, hModel, startPercent,2.0f);

		if (createNum_ == 0) {
			/*DrawRotaStringF()*/
			DrawString(boxCorners[0].x, boxCorners[0].y, "Main", GetColor(255, 255, 255), 1.5);
		}
		else {
			DrawString(boxCorners[0].x, boxCorners[0].y, "Sub", GetColor(255, 255, 255), 1.5);
		}
	}
#if 0
	// �l�p�`�`��
	for (int i = 0; i < 4; i++) {
		int j = (i + 1) % 4;
		DrawLineAA(boxCorners[i].x, boxCorners[i].y,
			boxCorners[j].x, boxCorners[j].y,
			GetColor(255, 0, 0), FALSE);
	}
	Mouse* pMouse = GetParent()->GetParent()->GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 mousePos = pMouse->GetMousePos();
	for (int i = 0; i < 4; ++i) {
		DrawCircle(boxCorners[i].x, boxCorners[i].y, 2,GetColor(0,255,0)); // �l���̃}�[�N
	}
	DrawCircle(mousePos.x, mousePos.y, 2, GetColor(0,0,255)); // �}�E�X�ʒu
#endif
}

void TriggerArcIcon::calculateArc()
{
	Mouse* pMouse = GetParent()->GetParent()->GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 mousePos = pMouse->GetMousePos();
	TileIcons* pTileIcons = GetParent()->GetParent()->GetParent()->FindGameObject<TileIcons>();
	SIZE_F_2D tileSize = pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D();
	XMFLOAT2 DrawCenterPos = { position.x + (graphSizeF_.halfX - tileSize.halfX),
		position.y + (graphSizeF_.halfY - tileSize.halfY) };


	// ��`�̊p�x�ƒ��S�p�̌������擾
	float startAngleDeg = startPercent * 3.6f;
	float endAngleDeg = percent * 3.6f;
	float centerAngleDeg = (startAngleDeg + endAngleDeg) / 2.0f;
	float angleRad = XMConvertToRadians(centerAngleDeg);

	// �l�p�`�T�C�Y�i���͊p�x�ɉ����āA�����͌Œ�j
	float angleSpanDeg = endAngleDeg - startAngleDeg;
	float width = graphSizeF_.halfX * sqrtf(2 * (1 - cos(XMConvertToRadians(angleSpanDeg))));
	float height = graphSizeF_.halfY;

	// �l�p�`�̃��[�J�����W�i���_�͒�Ӓ����j
	XMFLOAT2 localCorners[4] = {
		{-width / 2, -height}, // ����i����������X�^�[�g�j
		{ width / 2, -height}, // �E��
		{ width / 2, 0},       // �E��
		{-width / 2, 0}        // ����
	};

	// ��]���S�iDrawCircleGauge �Ɠ����j
	center = DrawCenterPos;

	// ���[�J�������[���h���W�֕ϊ��i��]����j
	for (int i = 0; i < 4; i++) {
		float x = localCorners[i].x;
		float y = localCorners[i].y;
		boxCorners[i].x = center.x + x * cos(angleRad) - y * sin(angleRad);
		boxCorners[i].y = center.y + x * sin(angleRad) + y * cos(angleRad);
	}

	VECTOR nowVec, centerVec;
	if (selecting_) { //�I��
		if (pMouse->IsPressed(Mouse::LEFT)) {
			nowVec = { mousePos.x, mousePos.y, 0 };
			centerVec = { center.x, center.y, 0 };

			VECTOR startVec = nowVec - centerVec;
			VECTOR nextVec = prevVec - centerVec;

			VECTOR cross = VCross(nextVec, startVec);
			if (cross.z < 0) { // ���v���
				startPercent -= 0.5;
				percent -= 0.5;
			}
			else if (cross.z > 0) { // �����v���
				startPercent += 0.5;
				percent += 0.5;
			}

			// ���t���[���̂��߂ɕۑ�
			prevVec = nowVec;
		}
	}
}
