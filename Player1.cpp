#include "Player1.h"
#include "Camera.h"
#include"Tile.h"
#include"Engine/CsvReader.h"
#include"Characters.h"
#include"ImGui/imgui.h"

Player1::Player1(GameObject* parent) : Object3D(parent)
{
}

Player1::~Player1()
{
	/*if (hModel > 0) {
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
	}*/
	/*DEL(hModel, 1);
	DEL(hBlade, 1);
	DEL(hShield, 1);
	DEL(hAsteroid, 1);*/
}

void Player1::Initialize()
{
	pTile_ = GetParent()->FindGameObject<Tile>();
	pCharacters_ = Instantiate<Characters>(this);

	CsvReader* csv = new CsvReader();
	csv->Load("Assets//Character//SelectCharacter.csv");
	for (int y = 1;y < csv->GetHeight();y++) {
		pCharacters_->CreateCharacterInstance(csv->GetInt(0, y));
	}

	int index = 0;
	for (auto& itr : pCharacters_->GetpCharacters()) {
		int placementIndex = csv->GetInt(9, index + 1);

		int x = placementIndex % MAX_MAP_WIDTH;
		int y = placementIndex / MAX_MAP_WIDTH;

		VECTOR initialPosition = pTile_->GetTilesData(x, y).position;
		itr->Set3DPosition(initialPosition);
		itr->ReadMyTrigger(index);
		index++;
	}
}

void Player1::Update()
{
	//Characters* pCharacters = GetParent()->GetParent()->FindGameObject<Characters>();
	//XMFLOAT3 c_rota = pCharacters->GetRotate();
	//VECTOR c_position = pCharacters->Get3DPosition();

	//// �J�����̐ݒ�
	//MATRIX mRot = MGetRotY(c_rota.y);  // ��]�s��
	//// ����ĂȂ��Ƃ��A�v���C���[����ǂꂮ�炢���H���x�N�g��
	//VECTOR tmpP = VGet(0, 5, 10);
	//// ����ɉ�]�s���������
	//VECTOR pRot = tmpP * mRot;
	//// ����Ƀv���C���[�̍��W�𑫂��ƁA�J�����ʒu���o��
	//VECTOR vRot = VGet(0, 5, -5) * mRot;

	//VECTOR cam_position = c_position + pRot;
	//VECTOR cam_target = c_position + vRot;
	//SetCameraPositionAndTarget_UpVecY(cam_position,cam_target);
}

void Player1::Draw()
{
}

void Player1::SetMyTrigger(MYTRIGGER _trigger)
{
	Trigger = _trigger;
}

void Player1::DrawMyTrigger(MYTRIGGER _trigger, MATRIX _leftMatrix, MATRIX _rightMatrix)
{

	/*for (int i = 0; i < 4; i++) {
		if (_trigger.Main[i].IsSelected) {
			switch (_trigger.Main[i].tNum)
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
			switch (_trigger.Sub[i].tNum)
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
	}*/
}