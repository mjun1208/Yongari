#include "DXUT.h"
#include "cEnemyAdmin.h"
#include "cEnemy.h"
#include "cMeteor.h"
void cEnemyAdmin::SpawnEnemy(D3DXVECTOR2 pos)
{
	RandNum = rand() % 100;
	if (RandNum <= Chest_probability)
		m_Enemy.push_back(new cEnemy(pos, Chest_Dragon.m_image, speed, m_HpGauge, m_HpEdge, Chest_Dragon.type));
	else if (RandNum <= Nomal_probability && RandNum > Chest_probability)
		m_Enemy.push_back(new cEnemy(pos, Nomal_Dragon.m_image, speed, m_HpGauge, m_HpEdge, Nomal_Dragon.type));
	else if (RandNum <= Gold_probability && RandNum > Nomal_probability)
		m_Enemy.push_back(new cEnemy(pos, Gold_Dragon.m_image, speed, m_HpGauge, m_HpEdge, Gold_Dragon.type));
	else if (RandNum <= Bomb_probability && RandNum > Gold_probability)
		m_Enemy.push_back(new cEnemy(pos, Bomb_Dragon.m_image, speed, m_HpGauge, m_HpEdge, Bomb_Dragon.type));
	else if (RandNum <= Black_probability && RandNum > Bomb_probability)
		m_Enemy.push_back(new cEnemy(pos, Black_Dragon.m_image, speed, m_HpGauge, m_HpEdge, Black_Dragon.type));
}

cEnemyAdmin::cEnemyAdmin()
{

}


cEnemyAdmin::~cEnemyAdmin()
{
	Release();
}

void cEnemyAdmin::Init()
{
	Nomal_Dragon  = { IMAGE->AddImage("Nomal_Dragon" , "./Image/Enemy/Nomal(%d).png",1)  ,Nomal };
	Gold_Dragon = { IMAGE->AddImage("Gold_Dragon" , "./Image/Enemy/Gold(%d).png",1)  ,Gold  };
	Bomb_Dragon  = { IMAGE->AddImage("Bomb_Dragon" , "./Image/Enemy/Bomb(%d).png",1)  ,Bomb };
	Black_Dragon = { IMAGE->AddImage("Black_Dragon" , "./Image/Enemy/Black(%d).png",1)  ,Black };
	Chest_Dragon = { IMAGE->AddImage("Chset", "./Image/Enemy/Chest(%d).png",1),Chest };
	Meteor_Dragon = { IMAGE->AddImage("Meteo_Dragon", "./Image/Meteor/Meteor.png"),Meteor };

	speed = 1.f;
	ThisTime = DX_Time;
	SpawnMeteorTime = DX_Time;

	m_HpGauge = IMAGE->AddImage("HpGauge", "./Image/Hp/HpGauge.png");
	m_HpEdge = IMAGE->AddImage("HpEdge", "./Image/Hp/HpEdge.png");

	MeteorEffect = IMAGE->AddImage("MeteorEffect", "./Image/Meteor/Effect(%d).png", 2);
	Danger = IMAGE->AddImage("Danger", "./Image/Meteor/Danger.png");

	srand(time(NULL));
	RandSpawnTime = rand() % 15 + 8;
	
	Chest_probability = 5;
	Nomal_probability = 100;
	Gold_probability = 0;
	Bomb_probability = 0;
	Black_probability = 0;

}

void cEnemyAdmin::Update(bool HyperFilght, D3DXVECTOR2 PlayerPos, int level, bool Boss)
{
	if (level == 4) {
		Nomal_probability = 0;
		Gold_probability = 0;
		Bomb_probability = 0;
		Black_probability = 100;
	}
	else if (level == 3) {
		Nomal_probability = 20;
		Gold_probability = 40;
		Bomb_probability = 50;
		Black_probability = 100;
	}
	else if (level == 2) {
		Nomal_probability = 50;
		Gold_probability = 90;
		Bomb_probability = 100;
		Black_probability = 0;
	}
	if (!Boss) {
		if (HyperFilght) {
			if (ThisTime > 0.8f / level) {
				SpawnEnemy(D3DXVECTOR2(90, -100));
				SpawnEnemy(D3DXVECTOR2(275, -100));
				SpawnEnemy(D3DXVECTOR2(450, -100));
				SpawnEnemy(D3DXVECTOR2(625, -100));

				ThisTime = 0.f;
			}
		}
		else {
			if (ThisTime > 2.f) {
				SpawnEnemy(D3DXVECTOR2(90, -100));
				SpawnEnemy(D3DXVECTOR2(275, -100));
				SpawnEnemy(D3DXVECTOR2(450, -100));
				SpawnEnemy(D3DXVECTOR2(625, -100));

				ThisTime = 0.f;
			}

		}
		ThisTime += DX_Time;
		SpawnMeteorTime += DX_Time;

		if ((float)RandSpawnTime < SpawnMeteorTime) {
			m_Meteor.push_back(new cMeteor(D3DXVECTOR2(PlayerPos.x, -130), Meteor_Dragon.m_image, 1000, MeteorEffect, Danger));
			SpawnMeteorTime = 0;
			RandSpawnTime = (rand() % (15 - level * 2) + (8 - level * 2)) / level;
		}
	}
	for (auto iter : m_Enemy)
		iter->Update(HyperFilght);
	for (auto iter : m_Meteor)
		iter->Update(PlayerPos);

	size_t size = m_Enemy.size();
	for (size_t i = 0; i < size; i++) {
		auto& iter = m_Enemy[i];
		if (iter->IsOutMap()) {
			SAFE_DELETE(iter);
			m_Enemy.erase(m_Enemy.begin() + i);
			i--, size--;
		}
	}
	for (auto iter = m_Meteor.begin(); iter != m_Meteor.end();) {
		if ((*iter)->IsOutMap()) {
			SAFE_DELETE(*iter);
			iter = m_Meteor.erase(iter);
		}
		else
			++iter;
	}
}

void cEnemyAdmin::Render()
{
	for (auto iter : m_Enemy)
		iter->Render();
	for (auto iter : m_Meteor)
		iter->Render();
}
 
void cEnemyAdmin::Release()
{
	for (auto iter : m_Enemy) {
		SAFE_DELETE(iter);
	}
	m_Enemy.clear();

	for (auto iter : m_Meteor) {
		SAFE_DELETE(iter);
	}
	m_Meteor.clear();
}
