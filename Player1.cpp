#include "Player1.h"
#include "Camera.h"
#include"Tile.h"
#include"Icon.h"
#include"resource.h"
#include"ImGui/imgui.h"


Player1::Player1(GameObject* parent) : Object3D(parent),hBlade(-1),hShield(-1)
{
	hModel = MV1LoadModel("Assets//human.mv1");
	assert(hModel >= 0);
	hBlade = MV1LoadModel("Assets//blade.mv1");
	assert(hBlade >= 0);
	hShield = MV1LoadModel("Assets//SampleSheald.mv1");
	assert(hShield >= 0);
	hAsteroid = MV1LoadModel("Assets//SampleAsteroid.mv1");
	assert(hAsteroid >= 0);

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	cPos.x = 0;
	cPos.y = 0;
	prevX = 0;
	prevY = 0;
	prevKey = false;

	cStatus.move = 5;
	cStatus.attack = 4;
	cStatus.speed = 6;
	cStatus.defense = 10;

	movetime = 5.0f;
	flame = 1.0f / 60.0f;
	time = 0.0f;

	Trigger = {};
}

Player1::~Player1()
{
	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
	if (hBlade > 0) {
		MV1DeleteModel(hBlade);
		hBlade = -1;
	}
	if (hShield > 0) {
		MV1DeleteModel(hShield);
		hShield = -1;
	}
	if (hAsteroid > 0) {
		MV1DeleteModel(hAsteroid);
		hAsteroid = -1;
	}
	/*DEL(hModel, 1);
	DEL(hBlade, 1);
	DEL(hShield, 1);
	DEL(hAsteroid, 1);*/
}

void Player1::Update()
{
	// �J�����̐ݒ�
	MATRIX mRot = MGetRotY(rotation.y);  // ��]�s��
	// ����ĂȂ��Ƃ��A�v���C���[����ǂꂮ�炢���H���x�N�g��
	VECTOR tmpP = VGet(0, 5, 10);
	// ����ɉ�]�s���������
	VECTOR pRot = tmpP * mRot;
	// ����Ƀv���C���[�̍��W�𑫂��ƁA�J�����ʒu���o��
	VECTOR vRot = VGet(0,5,-5) * mRot;
	SetCameraPositionAndTarget_UpVecY(position + pRot, position + vRot);
	icon = GetParent()->FindGameObject<Icon>();
	Tile* tile = GetParent()->FindGameObject<Tile>();

	//if (icon->GetCompWay()) {
	//	time += flame;  // ���Ԃ𑝉�������
	//	if (time > movetime) {  // ���̎��Ԃ��o�߂����ꍇ
	//		static size_t index = 0;  // ���ݏ������Ă���C�e���[�^�[�̃C���f�b�N�X
	//		const auto& way = icon->GetWay();

	//		// �C�e���[�^�[���͈͓��ɂ���ꍇ�ɏ���
	//		if (index < way.size()) {
	//			// ���݂̈ʒu���擾
	//			position = tile->GetTilesData(way[index].y, way[index].x).position;
	//			// �C���f�b�N�X�����ɐi�߂�
	//			++index;
	//		}
	//		else {
	//			// ���ׂĂ̏������I������ꍇ�A�C���f�b�N�X�����Z�b�g
	//			icon->SetCompWay(false);
	//			icon->GetWay().clear();
	//		}
	//		time = 0.0f;  // ���ԃ��Z�b�g
	//	}
	//}
	
	
}

void Player1::Draw()
{
	position = { icon->GetPIconPos().x,0.0,icon->GetPIconPos().y };
	//Object3D::Draw(); // ���N���X�̊֐����Ăԁ�Player�L������`�悷��
	MATRIX mModel = Object3D::ChangeFLOAT3ToMATRIX(position,rotation);
	MV1SetMatrix(hModel,mModel);
	MV1DrawModel(hModel);

	/*DrawCapsule3D(position, position + VGet(0, 160, 0), 30, 20, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);*/

	int RightHand = MV1SearchFrame(hModel, "RightHand");
	assert(RightHand >= 0);
	MATRIX mRightHand = MV1GetFrameLocalWorldMatrix(hModel, RightHand);
	//MATRIX mBlade = MV1GetFrameLocalWorldMatrix(hModel, RightHand);

	int LeftHand = MV1SearchFrame(hModel, "LeftHand");
	assert(LeftHand >= 0);
	MATRIX mLeftHand = MV1GetFrameLocalWorldMatrix(hModel, LeftHand);
	MATRIX mAsteroid = Object3D::ChangeFLOAT3ToMATRIX(VGet(mLeftHand.m[3][0],mLeftHand.m[3][1] - 0.2f, mLeftHand.m[3][2]),rotation);

	MATRIX mShield = Object3D::ChangeFLOAT3ToMATRIX({ position.x,position.y,position.z - 1.0f }, rotation);

	DrawMyTrigger(Trigger, mLeftHand, mRightHand);

	// �T�[�x���̐n�́A(0,0,0)�`(0,-150,0)�ɂ���B�����mSabel��������ƁA���̍��W����ɓ���
	/*DrawLine3D(VGet(0, 0, 0) * hBlade, VGet(0, -150, 0) * hBlade, GetColor(255, 0, 0));*/
}

void Player1::SetMyTrigger(MYTRIGGER _trigger)
{
	Trigger = _trigger;
}

void Player1::DrawMyTrigger(MYTRIGGER _trigger, MATRIX _leftMatrix, MATRIX _rightMatrix)
{
	for (int i = 0; i < 4; i++) {
		if (_trigger.Main[i].IsSelected) {
			switch ( _trigger.Main[i].trigger)
			{
			case FREE:
			{
				break;
			}
			case MOONBLADE:
			{
				IsLoaded(hBlade,_rightMatrix);
				break;
			}
			case SHIELD:
			{
				IsLoaded(hShield,_rightMatrix);
				break;
			}
			case ASTEROID:
			{
				IsLoaded(hAsteroid,_rightMatrix);
				break;
			}
			default:
				break;
			}
		}

		if (_trigger.Sub[i].IsSelected) {
			switch (_trigger.Sub[i].trigger)
			{
			case FREE:
			{
				break;
			}
			case MOONBLADE:
			{
				IsLoaded(hBlade, _leftMatrix);
				break;
			}
			case SHIELD:
			{
				IsLoaded(hShield, _leftMatrix);
				break;
			}
			case ASTEROID:
			{
				IsLoaded(hAsteroid, _leftMatrix);
				break;
			}
			default:
				break;
			}
		}
	}
}

//BOOL Player1::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
//{
//	switch (msg)
//	{
//	case WM_INITDIALOG:
//		/*SendMessage(GetDlgItem(hDlg, IDC_RADIO_RANGE), BM_SETCHECK, BST_CHECKED, 0);
//
//		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"�f�t�H���g");
//		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"�����K");
//		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"��");
//		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"��");
//		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"��");*/
//		break;
//	case WM_COMMAND:
//		switch (LOWORD(wp))
//		{
//		case IDC_RADIO_RANGE:
//			selectMode = 0;
//			break;
//		case IDC_RADIO_ANGLE:
//			selectMode = 1;
//			break;
//		case IDC_RADIO_CHANGE:
//			selectMode = 2;
//			break;
//		case IDC_COMBO3:
//			selectType = SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_GETCURSEL, 0, 0);
//			break;
//		default:
//			break;
//		}
//		break;
//	}
//
//	return FALSE;
//}
