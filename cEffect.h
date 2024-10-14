#pragma once
class cEffect
{
private:
	D3DXVECTOR2 m_pos;
	cTexture * m_image;
	cFrame * m_frame;
	bool b_Del = false;
	bool b_3frame = false;
	float ThisTime;

	int m_max;
	bool b_Bomb;
	bool b_HyperFlight;
public:

	cEffect(cTexture * image , D3DXVECTOR2 pos, int min, int max, int delay, bool Bomb = false, bool HyperFlight = false);
	~cEffect();

	void Update();
	void Render();
	void Release();

	bool GetDel() { return b_Del; }
};

