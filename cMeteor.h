#pragma once
class cMeteor
{
private:
	cTexture * m_image;
	cTexture * m_Effect;
	cTexture * m_Danger;

	D3DXVECTOR2 m_pos;
	float m_speed;
	cFrame * m_frame;

	float ThisTime;

	int i_Alpha;
	bool b_Alpha;
	bool b_fail;
	bool b_MeteorParty;
	int Rot = 0;
public:
	cMeteor(D3DXVECTOR2 pos, cTexture * image, float speed, cTexture * Effect, cTexture * Danger, bool MeteorParty = false);
	~cMeteor();

	void Update(D3DXVECTOR2 PlayerPos);
	void Render();

	bool IsOutMap();
	
	D3DXVECTOR2 GetPos() { return m_pos; }
	cTexture * GetTexture() { return m_image; }
	bool GetFail() { return b_fail; }
};

