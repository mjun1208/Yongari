#pragma once
class cEnemy;
class cMeteor;
enum DragonKind {
	Nomal, Gold, Bomb, Black , Chest , Meteor
};
class cEnemyAdmin
{
private:
	struct DragonState
	{
		cTexture * m_image;
		DragonKind type;
	};
	DragonState Nomal_Dragon;
	DragonState Gold_Dragon;
	DragonState Bomb_Dragon;
	DragonState Black_Dragon;
	DragonState Chest_Dragon;
	DragonState Meteor_Dragon;

	vector<cEnemy*> m_Enemy;
	vector<cMeteor*> m_Meteor;
	cTexture * m_HpGauge;
	cTexture * m_HpEdge;
	cTexture * MeteorEffect;
	cTexture * Danger;

	float speed;
	
	int RandNum;

	float ThisTime;
	float SpawnMeteorTime;
	int Nomal_probability;
	int Gold_probability;
	int Bomb_probability;
	int Black_probability;
	int Chest_probability;

	int RandSpawnTime;

	void SpawnEnemy(D3DXVECTOR2 pos);
public:
	cEnemyAdmin();
	~cEnemyAdmin();

	void Init();
	void Update(bool HyperFilght, D3DXVECTOR2 PlayerPos , int level, bool Boss = false);
	void Render();
	void Release();

	vector<cEnemy*>& GetEnemy() { return m_Enemy; }
	vector<cMeteor*>& GetMeteor() { return m_Meteor; }
};

