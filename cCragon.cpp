#include "DXUT.h"
#include "cCragon.h"


cCragon::cCragon()
{
	m_Idleimage = IMAGE->AddImage("Cragon_Idle", "./Image/Boss/Cragon/Idle(%d).png", 1);
	m_RightAttackimage = IMAGE->AddImage("Cragon_Right", "./Image/Boss/Cragon/Right(%d).png",2);
	m_LeftAttackimage = IMAGE->AddImage("Cragon_Left", "./Image/Boss/Cragon/Left(%d).png", 2);

	m_IdleFrame = new cFrame;
	m_IdleFrame->SetFrame(0,1,100);
	
	m_RightFrame = new cFrame;
	m_RightFrame->SetFrame(0, 2, 60);

	m_LeftFrame = new cFrame;
	m_LeftFrame->SetFrame(0, 2, 60);

	b_Idle = true;
	b_Right = false;
	b_Left = false;
}


cCragon::~cCragon()
{
	SAFE_DELETE(m_IdleFrame);
	SAFE_DELETE(m_RightFrame);
	SAFE_DELETE(m_LeftFrame);
}

void cCragon::Update()
{
	if (b_Idle)
		m_IdleFrame->Frame();
	else if (b_Right)
		m_RightFrame->Frame();
	else if (b_Left)
		m_LeftFrame->Frame();

	if (FirstMove) {
		if (m_pos.y < m_Idleimage->FindImage(m_IdleFrame->NowFrame)->info.Height / 2)
			m_pos.y += 10;
		else
			FirstMove = false;
	}
}

void cCragon::Render()
{
	if (b_Idle) {
		IMAGE->Render(m_Idleimage->FindImage(m_IdleFrame->NowFrame), m_pos.x, m_pos.y, 0, true);
	}
	//else if (b_Right) {
	//	IMAGE->Render(m_RightFrame->FindImage(m_RightFrame->NowFrame), m_pos.x, m_pos.y, 0, true);
	//}
	//else if (b_Left) {
	//	IMAGE->Render(m_LeftFrame->FindImage(m_LeftFrame->NowFrame), m_pos.x, m_pos.y, 0, true);
	//}
}
