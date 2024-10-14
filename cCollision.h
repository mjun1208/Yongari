#pragma once
class cEnemyAdmin;
class cEnemy;
class cBulletAdmin;
class cPlayerBullet;
class cEffect;
class cItem;
class cMeteor;
class cSlime;
class cCollision
{
private:
	D3DXVECTOR2 m_PlayerPos;
	cTexture * m_image;
	cTexture * m_Deadimage;
	cTexture * m_Bombimage;
	cTexture * m_HyperFlightimage;

	cTexture * m_HyperFlight;
	cTexture * m_Magnet;
	cTexture * m_DoubleScore;
	cTexture * m_DoubleShot;
	cTexture * m_Ruby;
	cTexture * m_Diamond;
	cTexture * m_Emerald;
	cTexture * m_Coin;

	vector<cEffect*> m_effect;
	vector<cItem*> m_item;

	float m_FDely;

	bool b_Chest = false;

	int RuBy_probability;
	int Diamond_probability;
	int Emerald_probability;

	int coin =0;
	int Score = 0;

	bool b_Magnet = false;
	bool b_HyperFlight = false;
	bool b_DoubleScore = false;
	bool b_DoubleShot = false;

	float MagnetTime;
	float HyperFlightTime;
	float DoubleScoreTime;
	float DoubleShotTime;
public:
	~cCollision();
	cCollision();

	void CheckPlayerColl(cTexture * image, float x, float y, vector<cEnemy*>& enemy);
	void CheckMonsterColl(vector<cEnemy*>& enemy, vector<cPlayerBullet*>& bullet);
	void CheckItemColl(cTexture * image, float x, float y);
	void CheckMeteorColl(cTexture * image, float x, float y, vector <cMeteor*>& meteor, vector<cPlayerBullet*>& bullet);
	void CheckSlimeColl(cTexture * image, float x, float y, vector <cSlime*>& slime, vector<cPlayerBullet*>& bullet);
	void BombColl(vector<cEnemy*>& enemy, float y);
	void Update(float x, float y, vector<cEnemy*>& enemy);
	void Render();

	void SpawnItem(int RandNum, D3DXVECTOR2 pos);
	void SpawnfunctionItem(int RandNum, D3DXVECTOR2 pos);
	int GetCoin() { return coin; }
	vector<cItem*>& GetItem() { return m_item; }
	int GetScore() { return Score; }

	bool GetHyperFilght() { return b_HyperFlight; }
	//bool GetDoubleScore() { return b_DoubleScore; }
	bool GetDoubleShot() { return b_DoubleShot; }
};

