#pragma once
#include "cScene.h"
#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>
#include "Digitalv.h"
class cPlayer;
class cEnemyAdmin;
class cCollision;
class cBulletAdmin;
class cSlimeAdmin;
class cCragon;
class cIngameScene : public cScene
{
private:
	MCI_OPEN_PARMS m_mciOpenParms;
	MCI_PLAY_PARMS m_mciPlayParms;

	MCI_OPEN_PARMS      mciOpen; //파일을 로드
	MCI_PLAY_PARMS       mciPlay; //파일을 재생
	MCI_STATUS_PARMS   mciStatus; //파일의 상태

	DWORD m_dwDeviceID;

	int dwID;
private:
	cTexture * m_BackGround;
	cTexture * m_MBackGround;

	cTexture * m_LevelUp;

	float m_scrool = 0.f;
	int speed;
	cPlayer * m_player = nullptr;
	cEnemyAdmin * m_Enemy = nullptr;
	cCollision * m_Coll = nullptr;
	cBulletAdmin * m_bullet = nullptr;
	cSlimeAdmin * m_Slime = nullptr;
	cCragon * m_Cragon = nullptr;

	bool b_Slime = false;
	bool b_Cragon = false;
	bool b_MaKing = false;
	int interval = 0;
	int level = 1;

	bool b_ShowLevelUp;

	bool b_Level2 = true;
	bool b_Level3 = true;
	bool b_Level4 = true;

	float ThisTime;

	int i_Alpha = 0;

	bool b_Coll = true; 
public:
	cIngameScene();
	virtual ~cIngameScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

