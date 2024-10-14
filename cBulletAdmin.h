#pragma once
class cPlayerBullet;
class cBulletAdmin
{
private:
	vector<cPlayerBullet* > m_bullet;
	cTexture * m_Bulletimage;
	cTexture * m_PowerShot;
	cFrame * m_frame;

	float ThisTime;

	bool b_PowerShot;
	int i_PowerShot;

	int m_Dmg;

	int Upgrade;
public:
	cBulletAdmin();
	~cBulletAdmin();

	void Update(D3DXVECTOR2 pos , bool PowerShot, int coin, bool DoubleShot, bool HyperFlight);
	void Render();
	void Release();

	vector<cPlayerBullet*>& GetBullet() { return m_bullet; }
};

