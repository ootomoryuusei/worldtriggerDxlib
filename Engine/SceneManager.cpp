#include "sceneManager.h"

#include "../TestScene.h"
#include "../TitleScene.h"
#include"../SelectScene.h"
#include"../SetScene.h"
#include "../PlayScene.h"
#include "time.h"

//コンストラクタ
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
}

//初期化
void SceneManager::Initialize()
{
	Time::Init();
	//最初のシーンを準備
	currentSceneID_ = SCENE_ID_PLAY;
	/*currentSceneID_ = SCENE_ID_SELECT;*/
	nextSceneID_ = currentSceneID_;
	/*Instantiate<TestScene>(this);*/
	/*Instantiate<SelectScene>(this);*/
	Instantiate<PlayScene>(this);

}

//更新
void SceneManager::Update()
{
	//次のシーンが現在のシーンと違う　＝　シーンを切り替えなければならない
	if (currentSceneID_ != nextSceneID_)
	{
		//そのシーンのオブジェクトを全削除
		KillAllChildren();

		//次のシーンを作成
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST: Instantiate<TestScene>(this); break;
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
		case SCENE_ID_SELECT: Instantiate<SelectScene>(this); break;
		case SCENE_ID_SET: Instantiate<SetScene>(this); break;
		case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;

		}
		currentSceneID_ = nextSceneID_;
	}
}

//描画
void SceneManager::Draw()
{
	Time::Refresh();
}

//開放
void SceneManager::Release()
{
}

//シーン切り替え（実際に切り替わるのはこの次のフレーム）
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
}