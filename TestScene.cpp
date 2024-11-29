#include "TestScene.h"
#include "ImGui/imgui.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
}

//�X�V
void TestScene::Update()
{
	SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_TITLE);
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
