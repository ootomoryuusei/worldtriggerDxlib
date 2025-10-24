#include "PlayScene.h"
#include "Engine/SceneManager.h"
#include"Player1.h"
#include"Enemy.h"
#include "Camera.h"
#include"Tiles.h"
#include"BackGround.h"
#include"Map.h"
#include"rader.h"
#include"Unit.h"
#include"Timer.h"
#include"TileIcons.h"
#include"UnitIcons.h"
#include "Mouse.h"
#include"MoveSelectIcon.h"
#include"MoveSetIcon.h"

#include"GroupManager.h"
#include"Keyboard.h"

PlayScene::PlayScene(GameObject* parent) : GameObject(parent,"playscene")
{
	Instantiate<Keyboard>(this); //�L�[�{�[�h
	Instantiate<Mouse>(this); //�}�E�X
	Instantiate<BackGround>(this); //�w�i
	Instantiate<GroupManager>(this); //�O���[�v�Ǘ��N���X
	Instantiate<Timer>(this);

	/*Instantiate<rader>(this);*/
	/*Instantiate<Unit>(this);*/

	Instantiate<Tiles>(this); //�^�C���Q

	Instantiate<Player1>(this); //�v���C���[

	Instantiate<Enemy>(this); //�G

	Instantiate<Map>(this); //�}�b�v

	Instantiate<MoveSelectIcon>(this); //�s���I��p�A�C�R��
	Instantiate<MoveSetIcon>(this); //�s���Z�b�g�p�A�C�R��

	Instantiate<UnitIcons>(this); //���j�b�g�Q

	Instantiate<Camera>(this); // Player����ɏ���
	
	// �Ƃ肠�����J������ݒ肷��
	/*SetCameraPositionAndTarget_UpVecY(VGet(0,0,0), VGet(0, 0, 0));*/
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	/*if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_SELECT);
	}*/
}

void PlayScene::Draw()
{
	//DrawString(0, 0, "PlayScene", GetColor(0, 0, 255));

	//// �A�i���O�̎���
	//int x;
	//int y;
	//GetJoypadAnalogInput(&x, &y, DX_INPUT_PAD1);
	//DrawFormatString(100, 10, GetColor(255,255,255), "Analog %d,%d", x, y);
}
