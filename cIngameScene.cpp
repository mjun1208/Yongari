#include "DXUT.h"
#include "cIngameScene.h"

#include "cPlayer.h"
#include "cEnemyAdmin.h"
#include "cCollision.h"
#include "cBulletAdmin.h"
#include "cSlimeAdmin.h"
#include "cCragon.h"

cIngameScene::cIngameScene()
{
}


cIngameScene::~cIngameScene()
{
	Release();
}

void cIngameScene::Init()
{
	ShowCursor(false);

	mciOpen.lpstrDeviceType = L"mpegvideo";
	mciOpen.lpstrElementName = L"./Sound/이마트 송.mp3";
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);


	dwID = mciOpen.wDeviceID;

	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, // play & repeat
		(DWORD)(LPVOID)&m_mciPlayParms);



	m_scrool = 0;
	m_player = new cPlayer;
	m_Enemy = new cEnemyAdmin;
	m_Coll = new cCollision;
	m_bullet = new cBulletAdmin;
//	m_Slime = new cSlimeAdmin;
	//m_effect = new cEffectAdmin;
	//m_Cragon = new cCragon;
	m_player->Init();
	m_Enemy->Init();
	m_BackGround = IMAGE->AddImage("BackGround", "./Image/BackGround.png");
	m_MBackGround = IMAGE->AddImage("MBackGround", "./Image/BackGround.png");
	m_LevelUp = IMAGE->AddImage("LevelUp", "./Image/Boss/Clear.png");
	speed = 150;
	b_ShowLevelUp = false;
	//ThisTime = DX_Time;
}

void cIngameScene::Update()
{
	if (INPUT->KeyUp('1')) {
		interval = 50000;
	}
	if (INPUT->KeyUp('2')) {
		interval = 150000;
	}
	if (INPUT->KeyUp('3')) {
		interval = 300000;
	}
	if (INPUT->KeyUp('C')) {
		if (b_Coll)
			b_Coll = false;
		else
			b_Coll = true;
	}
	m_scrool += speed * DX_Time;
	m_player->Update();
	m_bullet->Update(D3DXVECTOR2(m_player->GetPos_x(), m_player->GetPos_y() - 80), m_player->GetPowerShot(), m_Coll->GetCoin(), m_Coll->GetDoubleShot(), m_Coll->GetHyperFilght());
	m_Coll->CheckItemColl(m_player->GetTexture(), m_player->GetPos_x(), m_player->GetPos_y());
	m_Coll->Update(m_player->GetPos_x(), m_player->GetPos_y(), m_Enemy->GetEnemy());
	if(b_Coll)
	m_Coll->CheckPlayerColl(m_player->GetTexture(), m_player->GetPos_x(), m_player->GetPos_y(), m_Enemy->GetEnemy());
	if (!m_Coll->GetHyperFilght())
		m_Coll->CheckMonsterColl(m_Enemy->GetEnemy(), m_bullet->GetBullet());
	m_Coll->CheckMeteorColl(m_player->GetTexture(), m_player->GetPos_x(), m_player->GetPos_y(), m_Enemy->GetMeteor(), m_bullet->GetBullet());
	
	if (m_Coll->GetHyperFilght()) {
		interval += 40;
		speed = 1500;
	}
	else {
		interval += 20;
		speed = 150;
	}


	if (interval >= 300000) {
		level = 4;
		if (b_Level4) {
			b_ShowLevelUp = true;
			ThisTime = DX_Time;
			b_Level4 = false;
		}
	}
	else if (interval >= 150000) {
		level = 3;
		if (b_Level3) {
			b_ShowLevelUp = true;
			ThisTime = DX_Time;
			b_Level3 = false;
		}
	}
	else if (interval >= 50000) {
		level = 2;
		if (b_Level2) {
			b_ShowLevelUp = true;
			ThisTime = DX_Time;
			b_Level2 = false;
		}
	}

	if (b_ShowLevelUp) {
		ThisTime += DX_Time;
		if (ThisTime > 3.f) {
			b_ShowLevelUp = false;
			ThisTime = 0;
		}
	}

	//if (!b_Cragon && interval > 50000 && !m_Coll->GetHyperFilght()) {
	//	b_Cragon = true;
	//}

	//if (!b_Cragon) {
	m_Enemy->Update(m_Coll->GetHyperFilght(), D3DXVECTOR2(m_player->GetPos_x(), m_player->GetPos_y()) , level);
	//}
	//else {
		//m_Slime->Update();
	//	m_Cragon->Update();
	//	m_Enemy->Update(m_Coll->GetHyperFilght(), D3DXVECTOR2(m_player->GetPos_x(), m_player->GetPos_y()),true);
	//	//m_Coll->CheckSlimeColl(m_player->GetTexture(), m_player->GetPos_x(), m_player->GetPos_y(), m_Slime->GetSlime(), m_bullet->GetBullet());
	//}
}

void cIngameScene::Render()
{
	float renderPos = (int)m_scrool % (m_BackGround->info.Height);
	IMAGE->Render(m_BackGround, 0, 0);
	IMAGE->Render(m_MBackGround, 0, renderPos - m_MBackGround->info.Height);
	IMAGE->Render(m_MBackGround, 0, renderPos);

	m_player->Render(m_Coll->GetHyperFilght());
	m_Enemy->Render();
	m_bullet->Render();
	m_Coll->Render();

	//if (b_Cragon) {
	//	m_Cragon->Render();
	//}

	char c_intervalSize[128] = "";
	char c_Coinsize[128] = "";
	char c_EnemySize[128] = "";

	sprintf(c_intervalSize, "%012d" ,interval);
	IMAGE->PrintText(c_intervalSize,410, 10, 50, D3DCOLOR_XRGB(255, 255, 255), 0);
	sprintf(c_Coinsize, "%06d", m_Coll->GetCoin());
	IMAGE->PrintText(c_Coinsize, 50, 70, 50, D3DCOLOR_XRGB(255, 255, 255), 0);
	sprintf(c_EnemySize, "%012d", m_Coll->GetScore());
	IMAGE->PrintText(c_EnemySize, 0, 10, 50, D3DCOLOR_XRGB(255, 255, 255), 0);

	IMAGE->Render(IMAGE->FindImage("Coin"), 0, 70,D3DXVECTOR3(0.7f,0.7f,0.7f), 0, D3DCOLOR_XRGB(255, 255, 255));
	if (b_ShowLevelUp)
	IMAGE->Render(m_LevelUp, WINSIZEX / 2, 300, D3DXVECTOR3(1.f, 1.f, 1.f), 0, D3DCOLOR_ARGB(255, 255, 255, 255), true);
	
}

void cIngameScene::Release()
{
	SAFE_DELETE(m_player);
	SAFE_DELETE(m_Enemy);
	SAFE_DELETE(m_bullet);
	SAFE_DELETE(m_Coll);
	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
	//SAFE_DELETE(m_Slime);
	//SAFE_DELETE(m_effect);
}
