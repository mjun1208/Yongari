#pragma once
class cCragon
{
private:
	cTexture * m_Idleimage;
	cTexture * m_RightAttackimage;
	cTexture * m_LeftAttackimage;

	cFrame * m_IdleFrame;
	cFrame * m_RightFrame;
	cFrame * m_LeftFrame;

	D3DXVECTOR2 m_pos;

	bool FirstMove;

	bool b_Idle;
	bool b_Right;
	bool b_Left;
public:
	cCragon();
	~cCragon();

	void Update();
	void Render();

};

