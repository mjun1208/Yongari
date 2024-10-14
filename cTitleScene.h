#pragma once
#include "cScene.h"
#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>
#include "Digitalv.h"

class cTitleScene : public cScene
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
	cTexture * m_pBackGround;
	cTexture * m_Frame1;
	cTexture * m_Frame2;
	cTexture * m_Frame3;
	cTexture * m_Frame3_1;
	cTexture * m_Frame4;
	cTexture * m_Frame5;

	cButton * m_Start;
	cButton * m_Exit;
	cButton * m_HowTo;
	cButton * m_ExitChang;
	cTexture * m_HowToChang;

	bool b_HowTo = false;

	float  Rot = 0;
	float Scale = 0.f;
	int RandNum = 0;
	int x = 900;
	int y = -100;
	
	struct colorValue
	{
		int a = 0, r = 0, g = 0, b = 0;
	};

	colorValue color;
	colorValue color2;

	struct Dance
	{
		float x_dis =0.f;
		float y_dis = 0.f;
		int x = 0;
		int y = 0;
	};

	Dance Dragon1;
	Dance Dragon2;

	bool b_Dance = false;
	bool b_DNum = false;

	bool b_DRot = false; 
public:
 	cTitleScene();
	virtual ~cTitleScene();
	
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

