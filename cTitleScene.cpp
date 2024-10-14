#include "DXUT.h"
#include "cTitleScene.h"
#include "cIngameScene.h"

cTitleScene::cTitleScene()
{
	
}


cTitleScene::~cTitleScene()
{
}

void cTitleScene::Init()
{
	mciOpen.lpstrDeviceType = L"mpegvideo";
	mciOpen.lpstrElementName = L"./Sound/52.mp3";
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);


	dwID = mciOpen.wDeviceID;

	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, // play & repeat
		(DWORD)(LPVOID)&m_mciPlayParms);



	m_pBackGround = IMAGE->AddImage("Title_BackGround", "./Image/Title/BackGround.png");

	m_Frame1 = IMAGE->AddImage("Title_Frame1", "./Image/Title/Frame1.png");
	m_Frame2 = IMAGE->AddImage("Title_Frame2", "./Image/Title/Frame2.png");
	m_Frame3 = IMAGE->AddImage("Title_Frame3", "./Image/Title/Frame3.png");
	m_Frame3_1 = IMAGE->AddImage("Title_Frame3_1", "./Image/Title/Frame3_1.png");
	m_Frame4 = IMAGE->AddImage("Title_Frame4", "./Image/Title/Frame4.png");
	m_Frame5 = IMAGE->AddImage("Title_Frame5", "./Image/Title/Frame5.png");

	m_Start = new cButton(WINSIZEX / 2, 600, "Start", "./Image/Title/Start");
	m_Exit = new cButton(WINSIZEX / 2, 800, "Exit", "./Image/Title/Exit");
	m_HowTo = new cButton(WINSIZEX / 2, 700, "HowTo", "./Image/Title/HowTo");
	m_HowToChang = IMAGE->AddImage("HowToChang", "./Image/Title/HowToChang.png");
	m_ExitChang = new cButton(WINSIZEX / 2 + m_HowToChang->info.Width / 2 - 30, 700 - m_HowToChang->info.Height / 2,  "HowToExit", "./Image/Title/ExitChang");


	Rot = 0;
	Scale = 0.f;
	RandNum = 0;
	x = 1100;
	y = -100;
	color = { 0,0,0,0 };
	color2 = { 0,0,0,0 };

	Dragon1 = { 0.f, 0.f , -150,-100 };
	Dragon2 = { 0.f, 0.f, -150 ,-100 };
	b_Dance = false;
	b_DRot = false;

	SCENE->AddScene("Ingame", new cIngameScene);
}

void cTitleScene::Update()
{
	RandNum = rand() % 100;
	color.r = rand() % 255 + 50;
	color.g = rand() % 255 + 50;
	color.b = rand() % 255 + 50;

	if (INPUT->KeyDown(VK_SPACE))
	{
		color.a = 255;
		Scale = 1.f;
		Rot = 0.f;
		x = WINSIZEX / 2;
		color2.a = 255;
		b_Dance = true;
	}
	if (!b_Dance) {
		if (color.a >= 255) {
			color.a = 255;
			if (color2.a >= 255) {
				if (Scale >= 1.f) {
					Scale = 1.f;
					Rot = 0.f;
					if (y < 200){
						y += 10;
					}
					else {
						if (x > WINSIZEX / 2)
							x -= 30;
						else {
							x = WINSIZEX / 2;
							b_Dance = true;
						}
					}
				
				}
				else {
					Scale += 0.005f;
					Rot += 60.f;
				}
			}
			else
				color2.a += 1;
		}
		else
			color.a += 1;
	}
	else {
		
		if (!b_DNum)
		{
			if (Dragon1.y_dis > 180)
				b_DNum = true;
		
			Dragon1.y_dis += 8;
			Dragon2.y_dis -= 8; 
		}
		else
		{
			if (Dragon1.y_dis <= 0)
				b_DNum = false;
		
			Dragon1.y_dis -= 8;
			Dragon2.y_dis += 8;
		}


		Dragon1.x = -150 + (70 * cosf(D3DXToRadian(Dragon1.x_dis)));
		Dragon1.y = -100 + (60 * sinf(D3DXToRadian(Dragon1.y_dis * -1)));

		Dragon2.x = -150 - (70 * cosf(D3DXToRadian(Dragon2.x_dis)));
		Dragon2.y = -100 + (60 * sinf(D3DXToRadian(Dragon2.y_dis * -1)));
	
		Dragon1.x_dis += 10.f;
		Dragon2.x_dis -= 10.f;

		if (!b_DRot)
		{
			if (Rot > 10.f)
				b_DRot = true;

			Rot += 1.f;
		}
		else
		{
			if (Rot < -10.f)
				b_DRot = false;

			Rot -= 1.f;
		}
		if (!b_HowTo) {
			if (m_Start->Update()) {
				mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
				SCENE->ChangeScene("Ingame");
			}
			if (m_HowTo->Update()) {
				b_HowTo = true;
			}

			if (m_Exit->Update()) {
				PostQuitMessage(0);
			}
		}
		else if (b_HowTo) {
			if (m_ExitChang->Update()) {
				b_HowTo = false;
			}
		}
	}
}

void cTitleScene::Render()
{
	IMAGE->Render(m_pBackGround, 0, 0);

	IMAGE->Render(m_Frame1, Dragon1.x, Dragon1.y, D3DXVECTOR3(1.f, 1.f, 1.f), 0, D3DCOLOR_ARGB((int)color.a, 255, 255, 255));
	IMAGE->Render(m_Frame2, Dragon2.x, Dragon2.y, D3DXVECTOR3(1.f, 1.f, 1.f), 0, D3DCOLOR_ARGB((int)color2.a, 255, 255, 255));
	if (color2.a >= 255) {
		IMAGE->Render(m_Frame3_1, WINSIZEX / 2, 200, D3DXVECTOR3(Scale, Scale, 0.f), Rot, D3DCOLOR_ARGB(255, 255, 255, 255), true);
		IMAGE->Render(m_Frame3, WINSIZEX / 2, 200, D3DXVECTOR3(Scale, Scale, 0.f), Rot, D3DCOLOR_ARGB(255, 255, 255, 255), true);
	

	}

	if (Scale >= 1.f) {
		IMAGE->Render(m_Frame4, x, 300 , 0, true);
	}
	if (x <= WINSIZEX / 2) {
		m_Start->Render();
		m_Exit->Render();
		m_HowTo->Render();

		IMAGE->Render(m_Frame5, 0, 0, D3DXVECTOR3(1.f, 1.f, 1.f), 0, D3DCOLOR_ARGB(100, (int)color.r, (int)color.g, (int)color.b));
		if (b_HowTo) {
			IMAGE->Render(m_HowToChang, WINSIZEX / 2, 700, 0, true);
			m_ExitChang->Render();
		}
	}
}

void cTitleScene::Release()
{
	SAFE_DELETE(m_Start);
	SAFE_DELETE(m_Exit);
	SAFE_DELETE(m_HowTo);
	SAFE_DELETE(m_ExitChang);
}
