#include "DXUT.h"
#include "cEndScene.h"


cEndScene::cEndScene()
{
}


cEndScene::~cEndScene()
{
}

void cEndScene::Init()
{
	//m_BackGround =IMAGE.
	//m_Ok = new cButton(, , "Ok", "./Image/End/Ok");
}

void cEndScene::Update()
{
	//if (INPUT->KeyDown('O')) {
		SCENE->ChangeScene("Title");
	//}
}

void cEndScene::Render()
{
}

void cEndScene::Release()
{
}
