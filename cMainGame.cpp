#include "DXUT.h"
#include "cMainGame.h"

#include "cTitleScene.h"
#include "cEndScene.h"

cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
}

void cMainGame::Init()
{
	IMAGE->Init();
	SCENE->AddScene("Title", new cTitleScene);
	SCENE->AddScene("End", new cEndScene);

	SCENE->ChangeScene("Title");
}

void cMainGame::Update()
{
	SCENE->Update();
	INPUT->Update();
}

void cMainGame::Render()
{
	IMAGE->Begin();
	SCENE->Render();
	IMAGE->End();
}

void cMainGame::Release()
{
	cSceneManager::ReleaseInstance();
	cImageManager::ReleaseInstance();
	cInputManager::ReleaseInstance();
}

void cMainGame::LostDevice()
{
	IMAGE->LostDevice();
}

void cMainGame::ResetDevice()
{
	IMAGE->ResetDevice();
}
