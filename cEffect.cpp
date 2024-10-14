#include "DXUT.h"
#include "cEffect.h"


cEffect::cEffect(cTexture* image, D3DXVECTOR2 pos, int min, int max, int delay, bool Bomb, bool HyperFlight)
	: m_image(image), m_pos(pos), m_max(max), b_Bomb(Bomb), b_HyperFlight(HyperFlight)
{
	m_frame = new cFrame;
	m_frame->SetFrame(min, m_max, 70);
}


cEffect::~cEffect()
{
	Release();
}

void cEffect::Update()
{
	m_frame->Frame();
	if (m_frame->NowFrame >= m_max) {   
		b_3frame = true;
	}
	if (b_3frame && m_frame->NowFrame == 0)
		b_Del = true;
}

void cEffect::Render()
{
	if(b_Bomb)
		IMAGE->Render(m_image->FindImage(m_frame->NowFrame), m_pos.x, m_pos.y, D3DXVECTOR3(1.f, 1.f, 1.f), 0, D3DCOLOR_XRGB(255, 255, 255), true);
	else if (b_HyperFlight)
		IMAGE->Render(m_image->FindImage(m_frame->NowFrame), m_pos.x, m_pos.y, D3DXVECTOR3(3.f, 3.f, 3.f), 0, D3DCOLOR_XRGB(255, 255, 255), true);
	else
		IMAGE->Render(m_image->FindImage(m_frame->NowFrame), m_pos.x, m_pos.y, D3DXVECTOR3(0.5f, 0.5f, 0.5f), 0, D3DCOLOR_XRGB(255, 255, 255), true);
}

void cEffect::Release()
{
	SAFE_DELETE(m_frame);
}
