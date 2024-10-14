#pragma once
enum ItemKind
{
	HyperFlight , Magnet, DoubleScore, DoubleShot , Coin , Ruby , Diamond, Emerald
};
class cItem
{
private:
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_oldpos;
	ItemKind m_type;
	cTexture * m_image;

	float m_dis;
	float m_olddis;
	float m_Rot;
	bool b_move;

	bool b_div;
	int speed;
	int RandDis;

	int Direction = 0;
public:
	cItem(cTexture * image , D3DXVECTOR2 pos, int rand, ItemKind type, float randRot, int div);
	~cItem();

	void Update(D3DXVECTOR2 PlayerPos);
	void Render();
	void Release();

	void IsHyperFlight();
	void IsMagnet(D3DXVECTOR2 PlayerPos);
	void IsDoubleScore();
	void IsDoubleShot();
	
	bool b_Magnet = false;

	bool IsOutMap();
	ItemKind GetType() { return m_type; }
	D3DXVECTOR2 GetPos() { return m_pos; }
	bool GetMove() { return b_move; }

};

