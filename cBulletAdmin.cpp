#include "DXUT.h"
#include "cBulletAdmin.h"
#include "cPlayerBullet.h"

cBulletAdmin::cBulletAdmin()
{
	m_Bulletimage = IMAGE->AddImage("Bullet", "./Image/Bullet/Bullet(%d).png", 5);
	m_PowerShot = IMAGE->AddImage("PowerShot", "./Image/Bullet/PowerShot.png");
	m_frame = new cFrame;
	m_frame->SetFrame(0, 5, 70);
	ThisTime = DX_Time;
	b_PowerShot = false;
	i_PowerShot = 0;

	m_Dmg = 1;
	Upgrade = 0;
}


cBulletAdmin::~cBulletAdmin()
{
	Release();
}

void cBulletAdmin::Update(D3DXVECTOR2 pos, bool PowerShot, int coin , bool DoubleShot, bool HyperFlight)
{
	if (coin > 300) {
		Upgrade = 1;
		m_Dmg = 2;
	}
	if (coin > 600) {
		Upgrade = 2;
		m_Dmg = 4;
	}
	if (coin > 1500) {
		Upgrade = 3;
		m_Dmg = 7;
	}
	if (coin > 2300) {
		Upgrade = 4;
		m_Dmg = 11;
	}
	if (coin > 3200) {
		Upgrade = 5;
		m_Dmg = 20;
	}

	if (PowerShot && i_PowerShot <= 0) {
		i_PowerShot += 20;
	}

	if (i_PowerShot <= 0) {
		b_PowerShot = false;
	}
	else {
		b_PowerShot = true;
	}

	if (!HyperFlight) {
		if (ThisTime > 0.1f) {
			if (!b_PowerShot) {
				if (DoubleShot) {
					m_bullet.push_back(new cPlayerBullet(D3DXVECTOR2(pos.x - m_Bulletimage->FindImage(m_frame->NowFrame + Upgrade)->info.Width / 2, pos.y), m_Bulletimage->FindImage(m_frame->NowFrame + Upgrade)));
					m_bullet.push_back(new cPlayerBullet(D3DXVECTOR2(pos.x + m_Bulletimage->FindImage(m_frame->NowFrame + Upgrade)->info.Width / 2, pos.y), m_Bulletimage->FindImage(m_frame->NowFrame + Upgrade)));
					for (auto iter : m_bullet)
						iter->InputDmg(m_Dmg);
				}
				else {
					m_bullet.push_back(new cPlayerBullet(D3DXVECTOR2(pos.x, pos.y), m_Bulletimage->FindImage(m_frame->NowFrame + Upgrade)));
					for (auto iter : m_bullet)
						iter->InputDmg(m_Dmg);
				}
			}
			else {
				m_bullet.push_back(new cPlayerBullet(D3DXVECTOR2(pos.x, pos.y), m_PowerShot, true));
				for (auto iter : m_bullet)
					iter->InputDmg(m_Dmg * 2);
				i_PowerShot--;
			}
			ThisTime = 0;
		}
	}

	ThisTime += DX_Time;

	for (auto iter : m_bullet)
		iter->Update();

	size_t size = m_bullet.size();
	for (size_t i = 0; i < size; i++) {
		auto& iter = m_bullet[i];
		if (iter->IsOutMap()) {
			SAFE_DELETE(iter);
			m_bullet.erase(m_bullet.begin() + i);
			i--, size--;
		}
	}
}

void cBulletAdmin::Render()
{
	for (auto iter : m_bullet)
		iter->Render();
}

void cBulletAdmin::Release()
{
	for (auto iter : m_bullet) {
		SAFE_DELETE(iter)
	}
	m_bullet.clear();

	SAFE_DELETE(m_frame);
}
