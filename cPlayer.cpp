#include "DXUT.h"
#include "cPlayer.h"


cPlayer::cPlayer()
	: m_pos(WINSIZEX / 2, 820)
{
	m_image = IMAGE->AddImage("Player", "./Image/Player/Player(%d).png", 3);

	m_HyperFlightFrame = new cFrame;
	m_HyperFlightEffect = IMAGE->AddImage("HyperFlightEffect", "./Image/Effect/HyperFlight/HyperFlight(%d).png", 1);
	m_PowerShotIcon = IMAGE->AddImage("PowerShotIcon", "./Image/Item/PowerShot.png");
	m_HyperFlightFrame->SetFrame(0, 1, 50);
	i_PowerShot = 9;
}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_frame);
	SAFE_DELETE(m_HyperFlightFrame);

}

void cPlayer::Init()
{
	m_frame = new cFrame;
	m_frame->SetFrame(0, 3, 100);
	b_PowerShot = false;

}

void cPlayer::Update()
{
	POINT ptMouse;
	HWND m_hWnd = DXUTGetHWND();
	GetCursorPos(&ptMouse);
	ScreenToClient(m_hWnd, &ptMouse);
	if (ptMouse.x < (720 - 60) && ptMouse.x > (0 + 60))
		m_pos.x = ptMouse.x;
 
	m_HyperFlightFrame->Frame();
	m_frame->Frame();
	//if (INPUT->KeyPress(VK_SHIFT)) {
	//	if (m_pos.x < (720 - 100) && INPUT->KeyPress(VK_RIGHT))
	//		m_pos.x += 450 * DX_Time;
	//	if (m_pos.x >(0 + 100) && INPUT->KeyPress(VK_LEFT))
	//		m_pos.x -= 450 * DX_Time;
	//}
	//else {
	//	if (m_pos.x < (720 - 100) && INPUT->KeyPress(VK_RIGHT))
	//		m_pos.x += 700 * DX_Time;
	//	if (m_pos.x > (0 + 100) && INPUT->KeyPress(VK_LEFT))
	//		m_pos.x -= 700 * DX_Time;
	//}

	if (INPUT->KeyDown('Z')) {
		b_PowerShot = true;
		i_PowerShot--;
	}
	else {
		b_PowerShot = false;
	}
	//DEBUG_LOG(m_image->FindImage(m_frame->NowFrame)->info.Width);
	//DEBUG_LOG(m_image->FindImage(m_frame->NowFrame)->info.Height);
}

void cPlayer::Render(bool HyperFlight)
{
	if (HyperFlight)
		IMAGE->Render(m_HyperFlightEffect->FindImage(m_HyperFlightFrame->NowFrame), m_pos.x, m_pos.y, D3DXVECTOR3(0.7f, 0.7f, 0), 0, D3DCOLOR_XRGB(255, 255, 255), true);
	IMAGE->Render(m_image->FindImage(m_frame->NowFrame), m_pos.x, m_pos.y, D3DXVECTOR3(0.7f, 0.7f, 0), 0, D3DCOLOR_XRGB(255, 255, 255), true);
	char size[128];
		sprintf(size, "%d", i_PowerShot);
		IMAGE->Render(m_PowerShotIcon, WINSIZEX / 2, 930, D3DXVECTOR3(1.f, 1.f, 1.f), 0, D3DCOLOR_XRGB(255, 255, 255), true);
		IMAGE->PrintText(size, WINSIZEX / 2, 950, 50, D3DCOLOR_XRGB(0, 0, 0), true);
}
