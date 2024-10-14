#pragma once
class cButton {
private:
	cTexture * m_Nomal;
	cTexture * m_OnCursor;
	cTexture * m_Click;

	bool b_Nomal = false;
	bool b_OnCursor = false;
	bool b_Click = false;

	RECT m_rc;
	D3DXVECTOR2 m_pos;

	cFrame * m_frame = nullptr;

	void SettingRect() { SetRect(&m_rc, m_pos.x - m_Nomal->info.Width / 2, m_pos.y - m_Nomal->info.Height / 2, m_pos.x + m_Nomal->info.Width / 2, m_pos.y + m_Nomal->info.Height); };
public:
	cButton(float x, float y, const string& key, const string& path);
	~cButton();
	bool Update();
	void Render();
};
