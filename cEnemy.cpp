#include "DXUT.h"
#include "cEnemy.h"


cEnemy::cEnemy(D3DXVECTOR2 pos, cTexture * image, float speed, cTexture * HpGauge, cTexture * HpEdge, DragonKind type)
	: m_pos(pos), m_image(image), m_speed(speed) , m_HpGauge(HpGauge),  m_HpEdge(HpEdge) , m_type(type)
{
	m_frame = new cFrame;

	m_frame->SetFrame(0, 1, 100);

	b_hp = false;

	if (m_type == Nomal) {
		m_max =9;
		m_hp = m_max;
		m_Score = 50;
	}
	if (m_type == Gold) {
		m_max = 45;
		m_hp = m_max;
		m_Score = 100;
	}
	if (m_type == Bomb) {
		m_max = 25;
		m_hp = m_max;
		m_Score = 100;
	}
	if (m_type == Black) {
		m_max = 100;
		m_hp = m_max;
		m_Score = 400;
	}
	if (m_type == Chest) {
		m_max = 7;
		m_hp = m_max;
		m_Score = 5000;
	}

}


cEnemy::~cEnemy()
{
	SAFE_DELETE(m_frame);
}

void cEnemy::Update(bool HyperFilght)
{
	m_frame->Frame();
	if (HyperFilght)
	m_pos.y += 3000.f * DX_Time * m_speed;
	else 
	m_pos.y += 300.f * DX_Time * m_speed;
}

void cEnemy::Render()
{
	IMAGE->Render(m_image->FindImage(m_frame->NowFrame), m_pos.x, m_pos.y , D3DXVECTOR3(0.5f, 0.5f, 0.5f),0 ,D3DCOLOR_XRGB(255,255,255), true);
	if (b_hp) {
		RECT m_range = {  
			0, 
			0,
			(m_HpGauge->info.Width / m_max) * m_hp,
			m_HpGauge->info.Height
		};

		IMAGE->Render(m_HpEdge, m_pos.x, m_pos.y + 70 , D3DXVECTOR3(0.5f, 0.5f, 0.5f), 0,D3DCOLOR_XRGB(255,255,255),  true);
		IMAGE->CropRender(m_HpGauge, m_pos.x, m_pos.y + 70, D3DXVECTOR3(0.5f, 0.5f, 0.5f), m_range);
	}
}

bool cEnemy::IsOutMap()
{
	return (m_pos.x < -100 || m_pos.x > 1000 || m_pos.y < -100 || m_pos.y >  1500);
}
