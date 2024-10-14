#include "DXUT.h"
#include "cItem.h"


cItem::cItem(cTexture * image, D3DXVECTOR2 pos, int rand, ItemKind type, float randRot ,int div)
	: m_pos(pos), m_oldpos(pos), m_type(type), m_image(image), m_Rot(randRot), RandDis(rand)
{
	m_dis = RandDis;
	m_olddis = RandDis;
	b_move = false;

	if (div == 1) {
		b_div = true;
	}
	else {
		b_div = false;
	}
	speed = 300;


}


cItem::~cItem()
{
}

void cItem::Update(D3DXVECTOR2 PlayerPos)
{	
	if (!b_move && m_pos.y + 30 > m_oldpos.y) {
		if (m_pos.x > 0 + m_image->info.Width / 2 && m_pos.x < 720 - m_image->info.Width / 2) {
			if (b_div) {
				m_pos.x += 10.f * RandDis * DX_Time;
				m_dis += RandDis;
			}
			else {
				m_pos.x -= 10.f * RandDis * DX_Time;
				m_dis -= RandDis;
			}
		}
		m_pos.y -= 180 * DX_Time;
	}
	else
		b_move = true;

	if (b_move) {
		if (b_Magnet)
		{
			IsMagnet(PlayerPos);
		}
		else {
			m_pos.y += speed * DX_Time;
			speed += 20;
			if (b_div)
				m_pos.x += m_olddis / 10.f;
			else if (!b_div)
				m_pos.x -= m_olddis / 10.f;
		}
	}

}

void cItem::Render()
{
	IMAGE->Render(m_image, m_pos.x, m_pos.y, D3DXVECTOR3(0.5f,0.5f,0.5f),m_Rot, D3DCOLOR_XRGB(255,255,255),  true);
}

void cItem::Release()
{
}

void cItem::IsHyperFlight()
{
}

void cItem::IsMagnet(D3DXVECTOR2 PlayerPos)
{
	D3DXVECTOR2 tempTarget = PlayerPos;
	D3DXVECTOR2 direction = tempTarget - m_pos;
	D3DXVec2Normalize(&direction, &direction);
	m_pos += direction * 10;
}

void cItem::IsDoubleScore()
{
}

void cItem::IsDoubleShot()
{
}

bool cItem::IsOutMap()
{
	return (m_pos.x < -100 || m_pos.x > 1000 || m_pos.y < -150 || m_pos.y >  1200);
}
