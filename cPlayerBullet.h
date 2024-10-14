#pragma once

class cPlayerBullet
{
private:
	cTexture * m_image;
	D3DXVECTOR2 m_pos;
	int m_Dmg;
	bool b_PowerShot;
public:
	cPlayerBullet(D3DXVECTOR2 pos, cTexture * image ,bool PowerShot = false);
	~cPlayerBullet();

	void Update();
	void Render();

	bool IsOutMap();

	cTexture * GetTexture() { return m_image; }
	D3DXVECTOR2 GetPos() { return m_pos; }
	int GetDmg() { return m_Dmg; }

	void InputDmg(int dmg) { m_Dmg = dmg; }
	bool GetPowerShot() { return b_PowerShot; }
};

