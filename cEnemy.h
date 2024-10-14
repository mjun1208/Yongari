#pragma once
#include "cEnemyAdmin.h"
extern enum DragonKind;
class cEnemy
{
private:
	cTexture * m_image;
	cTexture * m_HpGauge;
	cTexture * m_HpEdge;
	D3DXVECTOR2 m_pos;
	float m_speed;
	cFrame * m_frame;
	int m_max;
	int m_hp;
	int m_Score;
	DragonKind m_type;
	
public:
	bool b_hp = false;

	cEnemy(D3DXVECTOR2 pos, cTexture * image, float speed, cTexture * HpGauge, cTexture * HpEdge , DragonKind type);
	~cEnemy();

	void Update(bool HyperFilght);
	void Render();

	bool IsOutMap();
	cTexture * GetTexture() { return m_image->FindImage(m_frame->NowFrame); }
	float GetPos_x() { return m_pos.x; }
	float GetPos_y() { return m_pos.y; }
	int GetHp() { return m_hp;}
	inline void InputHp(int hp) { m_hp = hp; }

	DragonKind GetType() { return m_type; }
	int GetScore() { return m_Score; }
};

