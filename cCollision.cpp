#include "DXUT.h"
#include "cCollision.h"

#include "cEnemyAdmin.h"
#include "cEnemy.h"
#include "cBulletAdmin.h"
#include "cPlayerBullet.h"
#include "cEffect.h"
#include "cItem.h"
#include "cMeteor.h"
#include "cSlime.h"

cCollision::cCollision()
{
	m_image = IMAGE->AddImage("Effect", "./Image/Effect/MonsterEffect/Effect(%d).png", 3);
	m_Deadimage = IMAGE->AddImage("DeadEffect", "./Image/Effect/DeadEffect/Effect(%d).png", 4);
	m_Bombimage = IMAGE->AddImage("BombEffect", "./Image/Effect/BombEffect/Effect(%d).png", 2);
	m_HyperFlightimage = IMAGE->AddImage("HyperFlightBombEffect", "./Image/Effect/HyperFlight/Effect/Effect(%d).png", 5);

	m_Coin = IMAGE->AddImage("Coin", "./Image/Item/Coin.png");
	m_Ruby = IMAGE->AddImage("Ruby", "./Image/Item/Ruby.png");
	m_Diamond = IMAGE->AddImage("Diamon", "./Image/Item/Diamond.png");
	m_Emerald = IMAGE->AddImage("Emerald", "./Image/Item/Emerald.png");
	
	m_HyperFlight = IMAGE->AddImage("HyperFlight", "./Image/Item/HyperFlight.png");
	m_Magnet = IMAGE->AddImage("Magnet", "./Image/Item/Magnet.png");
	m_DoubleScore = IMAGE->AddImage("DoubleScore", "./Image/Item/DoubleScore.png");
	m_DoubleShot = IMAGE->AddImage("DoubleShot", "./Image/Item/DoubleShot.png");

	srand(time(NULL));
	b_Chest = false;

	RuBy_probability = 70;
	Diamond_probability = 85;
	Emerald_probability = 95; 
	b_Magnet = false;
}


cCollision::~cCollision()
{
	for (auto iter : m_effect)
		SAFE_DELETE(iter)
		m_effect.clear();
	
	for (auto iter : m_item)
		SAFE_DELETE(iter)
		m_item.clear();
}

void cCollision::CheckPlayerColl(cTexture * image, float x, float y, vector<cEnemy*>& enemy )
{
	for (auto iter = enemy.begin(); iter != enemy.end(); ) {

		bool bDel = false;
		float e_x = (*iter)->GetPos_x();
		float e_y = (*iter)->GetPos_y();

		float w = image->info.Width;
		float h = image->info.Height;
		  
		// CENTER RENDER
		RECT range = { x - w / 2, y - h / 2,x + w / 2,y + h / 2 };
		// DEFAULT RENDER
		//RECT range = { x,y,x + w,y + h };

		if (range.left + 40 < e_x &&
			range.right - 40 > e_x &&
			range.top + 40 < e_y &&
			range.bottom - 60> e_y)
		{
			if (b_HyperFlight) {
				bDel = true;
			}
			else
			{
				SCENE->ChangeScene("End");
				//for (int i =0; i<25; i++)
				//MessageBoxW(DXUTGetHWND(), L"´ç½ÅÀº Á×¾ú½À´Ï´Ù ¤¾", L"»ç¸Á", MB_OK);
				//	PostQuitMessage(0);
			}
		}
		if (bDel) {
			if ((*iter)->GetType() == Bomb) {
				m_FDely = (*iter)->GetPos_y();
				m_effect.push_back(new cEffect(m_Bombimage, D3DXVECTOR2((*iter)->GetPos_x(), (*iter)->GetPos_y()), 0, 2, 10, true));
			}
			else
				m_effect.push_back(new cEffect(m_Deadimage, D3DXVECTOR2((*iter)->GetPos_x(), (*iter)->GetPos_y()), 0, 4, 10));
			if ((*iter)->GetType() == Chest) {
				b_Chest = true;
			}
			if (!b_Chest) {
				SpawnItem(rand() % 100, D3DXVECTOR2((*iter)->GetPos_x(), (*iter)->GetPos_y()));
				SpawnfunctionItem(rand() % 100, D3DXVECTOR2((*iter)->GetPos_x(), (*iter)->GetPos_y()));
			}
			else {
				for (int i = 0; i < 8; i++)
					SpawnItem(RuBy_probability, D3DXVECTOR2((*iter)->GetPos_x(), (*iter)->GetPos_y()));
				b_Chest = false;
			}
			if (b_DoubleScore)
				Score += (*iter)->GetScore() * 2;
			else
				Score += (*iter)->GetScore();
			SAFE_DELETE((*iter));
			iter = enemy.erase(iter);
		}
		else 
		++iter;
	}
	BombColl(enemy, m_FDely);
}

void cCollision::CheckMonsterColl(vector<cEnemy*>& enemy, vector<cPlayerBullet*>& bullet)
{
	bool bColl;
	int Hp;
	bool bDel;

	for (auto Eiter = enemy.begin(); Eiter != enemy.end();) {
		bColl = false;
		bDel = false;
		Hp = (*Eiter)->GetHp();
		for (auto Biter = bullet.begin(); Biter != bullet.end(); ) {

			RECT Erange = { 
				(*Eiter)->GetPos_x() - (*Eiter)->GetTexture()->info.Width / 2 ,
				(*Eiter)->GetPos_y() - (*Eiter)->GetTexture()->info.Height /2 ,
				(*Eiter)->GetPos_x() + (*Eiter)->GetTexture()->info.Width / 2,
				(*Eiter)->GetPos_y() + (*Eiter)->GetTexture()->info.Height/2};
			RECT Brange = {
				(*Biter)->GetPos().x - (*Biter)->GetTexture()->info.Width / 2,
				(*Biter)->GetPos().y - (*Biter)->GetTexture()->info.Height / 2,
				(*Biter)->GetPos().x + (*Biter)->GetTexture()->info.Width / 2,
				(*Biter)->GetPos().y + (*Biter)->GetTexture()->info.Height / 2};
			
			if (Erange.right - 100 > Brange.left &&
				Erange.left < Brange.right - 100 &&
				Erange.top < Brange.bottom &&
				Erange.bottom > Brange.top) {
				bColl = true;
				(*Eiter)->b_hp = true;
			}
			if (bColl) {
				Hp -= (*Biter)->GetDmg();

				m_effect.push_back(new cEffect(m_image, D3DXVECTOR2((*Biter)->GetPos()), 0, 3, 10));

				SAFE_DELETE(*Biter);
				Biter = bullet.erase(Biter);
				(*Eiter)->InputHp(Hp);

				bColl = false;
				bDel = true;
			}
			else {
				++Biter;
			}
		}

		if (bDel) {
			if (Hp <= 0) {
				if ((*Eiter)->GetType() == Bomb) {
					m_FDely = (*Eiter)->GetPos_y();
					m_effect.push_back(new cEffect(m_Bombimage, D3DXVECTOR2((*Eiter)->GetPos_x(), (*Eiter)->GetPos_y()), 0, 2, 10, true));
				}
				else 
					m_effect.push_back(new cEffect(m_Deadimage, D3DXVECTOR2((*Eiter)->GetPos_x(), (*Eiter)->GetPos_y()), 0, 4, 10));
				if ((*Eiter)->GetType() == Chest) {
					b_Chest = true;
				}
				if (!b_Chest) {
					SpawnItem(rand() % 100, D3DXVECTOR2((*Eiter)->GetPos_x(), (*Eiter)->GetPos_y()));
					SpawnfunctionItem(rand() % 100, D3DXVECTOR2((*Eiter)->GetPos_x(), (*Eiter)->GetPos_y()));
				}
				else {
					for (int i = 0; i < 8; i++)
					SpawnItem(RuBy_probability, D3DXVECTOR2((*Eiter)->GetPos_x(), (*Eiter)->GetPos_y()));
					
					b_Chest = false;
				}
				if(b_DoubleScore)
					Score += (*Eiter)->GetScore() * 2;
				else
				    Score += (*Eiter)->GetScore();
				SAFE_DELETE(*Eiter);
				Eiter = enemy.erase(Eiter);
			}
			bDel = false;
		}
		else
			++Eiter;
		
	}
	BombColl(enemy, m_FDely);
}

void cCollision::CheckItemColl(cTexture * image, float x, float y)
{
	for (auto iter = m_item.begin(); iter != m_item.end(); ) {
		D3DXVECTOR2 pos = (*iter)->GetPos();

		float w = image->info.Width;
		float h = image->info.Height;

		// CENTER RENDER
		RECT range = { x - w / 2, y - h / 2,x + w / 2,y + h / 2 };
		// DEFAULT RENDER
		//RECT range = { x,y,x + w,y + h };
		if ((*iter)->GetMove()) {
			if (range.left < pos.x &&
				range.right > pos.x &&
				range.top < pos.y &&
				range.bottom > pos.y)
			{
				if ((*iter)->GetType() == Coin) {
					coin += 1;
				}
				else if ((*iter)->GetType() == Ruby) {
					coin += 10;
				}
				else if ((*iter)->GetType() == Emerald) {
					coin += 20;
				}
				else if ((*iter)->GetType() == Diamond) {
					coin += 30;
				}
				else if ((*iter)->GetType() == HyperFlight) {
					b_HyperFlight = true;
					HyperFlightTime = DX_Time;
				}
				else if ((*iter)->GetType() == Magnet) {
					b_Magnet = true;
					MagnetTime = DX_Time;
				}
				else if ((*iter)->GetType() == DoubleScore) {
					b_DoubleScore = true;
					DoubleScoreTime = DX_Time;
				}
				else if ((*iter)->GetType() == DoubleShot) {
					b_DoubleShot = true;
					DoubleShotTime = DX_Time;
				}
				SAFE_DELETE(*iter);
				iter = m_item.erase(iter);
			}
			else
				++iter;
		}
		else ++iter;
	}

}

void cCollision::CheckMeteorColl(cTexture * image, float x, float y, vector<cMeteor*>& meteor , vector<cPlayerBullet*>& bullet)
{
	for (auto iter = meteor.begin(); iter != meteor.end(); ) {

		bool bDel = false;
		D3DXVECTOR2 pos = (*iter)->GetPos();

		float w = image->info.Width;
		float h = image->info.Height;

		// CENTER RENDER
		RECT range = { x - w / 2, y - h / 2,x + w / 2,y + h / 2 };
		// DEFAULT RENDER
		//RECT range = { x,y,x + w,y + h };

		if (range.left + 30 < pos.x &&
			range.right - 30 > pos.x &&
			range.top + 30 < pos.y &&
			range.bottom - 30> pos.y)
		{
			if (b_HyperFlight) {
				bDel = true;
			}
			else
				PostQuitMessage(0);
		}
		if (bDel) {
			SAFE_DELETE((*iter));
			iter = meteor.erase(iter);
		}
		else
			++iter;
	}

	bool bDel;
	for (auto Miter = meteor.begin(); Miter != meteor.end();) {
		bDel = false;
		if ((*Miter)->GetFail()) {
			for (auto Biter = bullet.begin(); Biter != bullet.end(); ) {

				RECT Erange = {
					(*Miter)->GetPos().x - (*Miter)->GetTexture()->info.Width / 2 ,
					(*Miter)->GetPos().y - (*Miter)->GetTexture()->info.Height / 2 ,
					(*Miter)->GetPos().x + (*Miter)->GetTexture()->info.Width / 2,
					(*Miter)->GetPos().y + (*Miter)->GetTexture()->info.Height / 2 };
				RECT Brange = {
					(*Biter)->GetPos().x - (*Biter)->GetTexture()->info.Width / 2,
					(*Biter)->GetPos().y - (*Biter)->GetTexture()->info.Height / 2,
					(*Biter)->GetPos().x + (*Biter)->GetTexture()->info.Width / 2,
					(*Biter)->GetPos().y + (*Biter)->GetTexture()->info.Height / 2 };

				if (Erange.right - 100 > Brange.left &&
					Erange.left < Brange.right - 100 &&
					Erange.top < Brange.bottom &&
					Erange.bottom > Brange.top && (*Biter)->GetPowerShot()) {
					{
						bDel = true;
						SAFE_DELETE(*Biter);
						Biter = bullet.erase(Biter);
					}
				}
				else {
					++Biter;
				}
			}

			if (bDel) {
				SAFE_DELETE(*Miter);
				Miter = meteor.erase(Miter);
				bDel = false;
			}
			else
				++Miter;
		}
		else ++Miter;
	}
}

void cCollision::BombColl(vector<cEnemy*>& enemy, float y)
{
	for (auto Eiter = enemy.begin(); Eiter != enemy.end();) {
		if ((*Eiter)->GetPos_y() == y) {
			m_effect.push_back(new cEffect(m_Deadimage, D3DXVECTOR2((*Eiter)->GetPos_x(), (*Eiter)->GetPos_y()), 0, 4, 10));
			SAFE_DELETE(*Eiter);
			Eiter = enemy.erase(Eiter);
		}
		else 
			++Eiter;
	}
}

void cCollision::CheckSlimeColl(cTexture * image, float x, float y, vector <cSlime*>& slime, vector<cPlayerBullet*>& bullet) {
	for (auto iter = slime.begin(); iter != slime.end(); ) {

		bool bDel = false;
		D3DXVECTOR2 pos = (*iter)->GetPos();

		float w = image->info.Width;
		float h = image->info.Height;

		// CENTER RENDER
		RECT range = { x - w / 2, y - h / 2,x + w / 2,y + h / 2 };
		// DEFAULT RENDER
		//RECT range = { x,y,x + w,y + h };

		if (range.left + 30 < pos.x &&
			range.right - 30 > pos.x &&
			range.top + 30 < pos.y &&
			range.bottom - 30> pos.y)
		{
			PostQuitMessage(0);
		}
		else
			++iter;
	}
	int Hp;
	bool bDel;
	bool bColl;
	for (auto Siter = slime.begin(); Siter != slime.end();) {
		bDel = false;
		bColl = false;
		Hp = (*Siter)->GetHp();
		for (auto Biter = bullet.begin(); Biter != bullet.end(); ) {

			RECT Erange = {
				(*Siter)->GetPos().x - (*Siter)->GetWidth() / 2 ,
				(*Siter)->GetPos().y - (*Siter)->GetHeight() / 2 ,
				(*Siter)->GetPos().x + (*Siter)->GetWidth() / 2,
				(*Siter)->GetPos().y + (*Siter)->GetHeight() / 2 };
			RECT Brange = {
				(*Biter)->GetPos().x - (*Biter)->GetTexture()->info.Width / 2,
				(*Biter)->GetPos().y - (*Biter)->GetTexture()->info.Height / 2,
				(*Biter)->GetPos().x + (*Biter)->GetTexture()->info.Width / 2,
				(*Biter)->GetPos().y + (*Biter)->GetTexture()->info.Height / 2 };
			
			if (Erange.right - 100 > Brange.left &&
				Erange.left < Brange.right - 100 &&
				Erange.top < Brange.bottom &&
				Erange.bottom > Brange.top) {
				    bColl = true;
				    (*Siter)->b_hp = true;

			}
			if (bColl) {
				Hp -= (*Biter)->GetDmg();

				m_effect.push_back(new cEffect(m_image, D3DXVECTOR2((*Biter)->GetPos()), 0, 3, 10));

				SAFE_DELETE(*Biter);
				Biter = bullet.erase(Biter);
				(*Siter)->InputHp(Hp);

				bColl = false;
				bDel = true;
			}
			else {
				++Biter;
			}
		}
			++Siter;
	}
}

void cCollision::Update(float x, float y, vector<cEnemy*>& enemy)
{
	if (INPUT->KeyUp('4')) {
		coin = 0;
	}
	if (INPUT->KeyUp('5')) {
		coin = 301;
	}
	if (INPUT->KeyUp('6')) {
		coin = 601;
	}
	if (INPUT->KeyUp('7')) {
		coin = 1501;
	}
	if (INPUT->KeyUp('8')) {
		coin = 2301;
	}
	if (INPUT->KeyUp('9')) {
		coin = 3201;
	}
	if (INPUT->KeyUp('0')) {
		b_HyperFlight = true;
		HyperFlightTime = DX_Time;
	}


	if (b_Magnet) {
		MagnetTime += DX_Time;
		if (MagnetTime > 10.f) {
			b_Magnet = false;
		}
	}

	if (b_DoubleScore) {
		DoubleScoreTime += DX_Time;
		if (DoubleScoreTime > 10.f) {
			b_DoubleScore = false;
		}
	}

	if (b_DoubleShot) {
		DoubleShotTime += DX_Time;
		if (DoubleShotTime > 10.f) {
			b_DoubleShot = false;
		}
	}
	if (b_HyperFlight) {
		HyperFlightTime += DX_Time;

		if (HyperFlightTime > 5.f) {
			m_effect.push_back(new cEffect(m_HyperFlightimage, D3DXVECTOR2(x,y), 0, 5, 10,false, true));
			for (auto iter : enemy) {
				if (iter->GetType() == Bomb) {
					m_FDely = iter->GetPos_y();
					m_effect.push_back(new cEffect(m_Bombimage, D3DXVECTOR2(iter->GetPos_x(), iter->GetPos_y()), 0, 2, 10, true));
				}
				else
					m_effect.push_back(new cEffect(m_Deadimage, D3DXVECTOR2(iter->GetPos_x(), iter->GetPos_y()), 0, 4, 10));
				if (iter->GetType() == Chest) {
					b_Chest = true;
				}
				if (!b_Chest) {
					SpawnItem(rand() % 100, D3DXVECTOR2(iter->GetPos_x(), iter->GetPos_y()));
					SpawnfunctionItem(rand() % 100, D3DXVECTOR2(iter->GetPos_x(), iter->GetPos_y()));
				}
				else {
					for (int i = 0; i < 8; i++)
						SpawnItem(RuBy_probability, D3DXVECTOR2(iter->GetPos_x(), iter->GetPos_y()));

					b_Chest = false;
				}

				SAFE_DELETE(iter);
			}
			enemy.clear();
			b_HyperFlight = false;
		}
	}

	for(auto iter : m_effect)
		iter->Update();
	for (auto iter : m_item) {
		if (b_Magnet == true)
			iter->b_Magnet = true;
		else
			iter->b_Magnet = false;

		iter->Update(D3DXVECTOR2(x, y));
	}

	for (auto iter = m_effect.begin(); iter != m_effect.end();) {
		if ((*iter)->GetDel()) {
			SAFE_DELETE(*iter);
			iter = m_effect.erase(iter);
		}
		else
			iter++;
	}

	for (auto iter = m_item.begin(); iter != m_item.end();) {
		if ((*iter)->IsOutMap()) {
			SAFE_DELETE(*iter);
			iter = m_item.erase(iter);
		}
		else
			iter++;
	}
}

void cCollision::Render()
{
	for(auto iter : m_effect)
		iter->Render();
	for (auto iter : m_item)
		iter->Render();

	char MagnetSize[128];
	char HyperFlightSize[128];
	char DoubleScoreSize[128];
	char DoubleShotSize[128];

	if (b_Magnet) {
		sprintf(MagnetSize, "%0.f", 10.f - MagnetTime);
		IMAGE->Render(IMAGE->FindImage("Magnet"), WINSIZEX /2 -200, 930, D3DXVECTOR3(0.6f, 0.6f, 0.6f), 0, D3DCOLOR_XRGB(255, 255, 255), true);
		IMAGE->PrintText(MagnetSize, WINSIZEX /2 - 200,950, 50, D3DCOLOR_XRGB(0, 0, 0) , true);
	}
	if (b_HyperFlight) {
		sprintf(HyperFlightSize, "%0.f", 5.f - HyperFlightTime);
		IMAGE->Render(IMAGE->FindImage("HyperFlight"), WINSIZEX / 2 - 100, 930, D3DXVECTOR3(0.6f, 0.6f, 0.6f), 0, D3DCOLOR_XRGB(255, 255, 255), true);
		IMAGE->PrintText(HyperFlightSize, WINSIZEX / 2 - 100, 950, 50, D3DCOLOR_XRGB(0,0,0), true);
	}
	if (b_DoubleScore) {
		sprintf(DoubleScoreSize, "%0.f", 10.f - DoubleScoreTime);
		IMAGE->Render(IMAGE->FindImage("DoubleScore"), WINSIZEX / 2 + 100, 930, D3DXVECTOR3(0.6f, 0.6f, 0.6f), 0, D3DCOLOR_XRGB(255, 255, 255), true);
		IMAGE->PrintText(DoubleScoreSize, WINSIZEX / 2 + 100, 950, 50, D3DCOLOR_XRGB(0,0,0), true);
	}
	if (b_DoubleShot) {
		sprintf(DoubleShotSize, "%0.f", 10.f - DoubleShotTime);
		IMAGE->Render(IMAGE->FindImage("DoubleShot"), WINSIZEX / 2 + 200, 930, D3DXVECTOR3(0.6f, 0.6f, 0.6f), 0, D3DCOLOR_XRGB(255, 255, 255), true);
		IMAGE->PrintText(DoubleShotSize, WINSIZEX / 2 + 200, 950, 50, D3DCOLOR_XRGB(0,0,0), true);
	}
}

void cCollision::SpawnItem(int RandNum , D3DXVECTOR2 pos)
{
	if (RandNum < 70) {
		m_item.push_back(new cItem(m_Coin, pos ,rand()%10 ,Coin, rand()%360, rand() % 2));
	}
	else if (RandNum >= RuBy_probability && RandNum < Emerald_probability)
	{
		m_item.push_back(new cItem(m_Ruby, pos, rand() % 10,Ruby, rand() % 360, rand() % 2));
	}
	else if (RandNum >= Emerald_probability && RandNum < Diamond_probability) {
		m_item.push_back(new cItem(m_Emerald, pos, rand() % 10,Emerald, rand() % 360, rand() % 2));
	}
	else if (RandNum >= Diamond_probability ) {
		m_item.push_back(new cItem(m_Diamond, pos, rand() % 10,Diamond, rand() % 360,rand() % 2));
	}
}

void cCollision::SpawnfunctionItem(int RandNum, D3DXVECTOR2 pos)
{
	//m_item.push_back(new cItem(m_HyperFlight, pos, rand() % 10, HyperFlight, 0, rand() % 2));

	if (RandNum < 88 && RandNum >= 40) {
		m_item.push_back(new cItem(m_Coin, pos, rand() % 10, Coin, rand() % 360 , rand() % 2));
	}
	else if (RandNum >= 88 && RandNum < 91) {
		m_item.push_back(new cItem(m_HyperFlight, pos, rand() % 10, HyperFlight, 0, rand() % 2));
	}
	else if (RandNum >= 91 && RandNum < 94) {
		m_item.push_back(new cItem(m_Magnet, pos, rand() % 10,Magnet, rand()%360, rand() % 2));
	}
	else if (RandNum >= 94 && RandNum < 97) {
		m_item.push_back(new cItem(m_DoubleScore, pos, rand() % 10, DoubleScore, 0, rand() % 2));
	}
	else if (RandNum >= 97) {
		m_item.push_back(new cItem(m_DoubleShot, pos, rand() % 10, DoubleShot, 0, rand() % 2));
	}
}
 