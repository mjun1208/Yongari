#include "DXUT.h"
#include "cPlayerBullet.h"


cPlayerBullet::cPlayerBullet(D3DXVECTOR2 pos, cTexture * image, bool PowerShot)
	:m_pos(pos), m_image(image), b_PowerShot(PowerShot)
{
	m_Dmg = 0;
}


cPlayerBullet::~cPlayerBullet()
{
}

void cPlayerBullet::Update()
{
	m_pos.y -= 1000.f * DX_Time;
}

void cPlayerBullet::Render()
{
	IMAGE->Render(m_image, m_pos.x, m_pos.y - m_image->info.Height / 2.f, 0, true);
}

bool cPlayerBullet::IsOutMap()
{
	return (m_pos.x < -100 || m_pos.x > 1000 || m_pos.y < -100 || m_pos.y >  1500);
}
