#pragma once
class cBulletAdmin;
class cPlayer
{
private:
	D3DXVECTOR2 m_pos;
	cTexture * m_image;
	cFrame * m_frame;
	bool b_PowerShot;

	cTexture * m_HyperFlightEffect;
	cFrame * m_HyperFlightFrame;

	int i_PowerShot;
	cTexture * m_PowerShotIcon;
	//vector<cBullet*> m_bullet;
public:
	cPlayer();
	~cPlayer();

	void Init();
	void Update();
	void Render(bool HyperFlight);
	float GetPos_x() { return m_pos.x; };
	float GetPos_y() { return m_pos.y; };
	bool GetPowerShot() { return b_PowerShot; }

	cTexture * GetTexture() { return m_image->FindImage(m_frame->NowFrame); }
};

