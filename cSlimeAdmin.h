#pragma once
class cSlime;
class cSlimeAdmin
{
private:
	cTexture * m_image;
	D3DXVECTOR2 m_pos;

	vector<cSlime*> m_Slime;
	bool FirstSpawn = false;
public:
	cSlimeAdmin();
	~cSlimeAdmin();
	
	void Update();
	void Render();
	vector<cSlime*>& GetSlime() { return m_Slime; }
};

