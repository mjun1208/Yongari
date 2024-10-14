#pragma once
class cSlime
{
private:
	cTexture * m_image;
	cFrame * m_frame;
	D3DXVECTOR2 m_pos;
	int m_Hp;
	int m_Dan;
	float m_Width;
	float m_Height;
public:
	bool b_hp = false;
	cSlime(cTexture * image, D3DXVECTOR2 pos , int Dan);
	~cSlime();

	void Update();
	void Render();

	inline void InputHp(int hp) { m_Hp = hp; }

	D3DXVECTOR2 GetPos() { return m_pos; }
	int GetHp() { return m_Hp; }
	int GetDan() { return m_Dan; }
	float GetWidth() { return m_Width; }
	float GetHeight() { return m_Height; }
};

