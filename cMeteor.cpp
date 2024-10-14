#include "DXUT.h"
#include "cMeteor.h"


cMeteor::cMeteor(D3DXVECTOR2 pos, cTexture * image, float speed, cTexture * Effect, cTexture * Danger , bool MeteorParty)
	:m_pos(pos), m_speed(speed) , m_image(image), m_Effect(Effect), m_Danger(Danger) , b_MeteorParty(MeteorParty)
{
	m_frame = new cFrame;
	m_frame->SetFrame(0, 2, 40);

	ThisTime = DX_Time;
	i_Alpha = 200;
	b_Alpha = true;
	b_fail = false;
}


cMeteor::~cMeteor()
{
	SAFE_DELETE(m_frame);
}

void cMeteor::Update(D3DXVECTOR2 PlayerPos)
{
	m_frame->Frame();
	ThisTime += DX_Time;
	Rot++;
	if (ThisTime > 3.f)
		b_fail = true;
	else
		b_fail = false;

	if (b_fail) {
		m_pos.y += m_speed * DX_Time;
	}
	else {
		if (!b_MeteorParty) {
			D3DXVECTOR2 tempTarget = PlayerPos;
			D3DXVECTOR2 direction = tempTarget - m_pos;
			D3DXVec2Normalize(&direction, &direction);
			m_pos.x += direction.x * 10;
		}
		if (b_Alpha) {
			if (i_Alpha >= 255)
				b_Alpha = false;
			i_Alpha += 10;
		}
		else {
			if (i_Alpha <= 150)
				b_Alpha = true;
			i_Alpha -= 10;
		}
	}

}

void cMeteor::Render()
{
	if (!b_fail)
		IMAGE->Render(m_Danger, m_pos.x, 0 + m_Danger->info.Height / 2, D3DXVECTOR3(1.f, 1.f, 1.f), 0, D3DCOLOR_ARGB(i_Alpha, 255, 255, 255), true);
	else {
		IMAGE->Render(m_Effect->FindImage(m_frame->NowFrame), m_pos.x, m_pos.y - 100, 0,  true);
		IMAGE->Render(m_image, m_pos.x, m_pos.y, Rot, true);
	}
}

bool cMeteor::IsOutMap()
{
	return (m_pos.x < -100 || m_pos.x > 1000 || m_pos.y < -300 || m_pos.y >  1500);
}

