#include "DXUT.h"
#include "cSlimeAdmin.h"
#include "cSlime.h"

cSlimeAdmin::cSlimeAdmin()
{
	m_image = IMAGE->AddImage("Slime", "./Image/Boss/Slime/Slime(%d).png", 3);
}


cSlimeAdmin::~cSlimeAdmin()
{
	for (auto iter : m_Slime)
		SAFE_DELETE(iter);
	m_Slime.clear();
}

void cSlimeAdmin::Update()
{
	if (!FirstSpawn) {
		m_Slime.push_back(new cSlime(m_image, D3DXVECTOR2(WINSIZEX / 2, -100), 1));
		FirstSpawn = true;
	}

	for (auto iter : m_Slime)
		iter->Update();

	for (auto iter = m_Slime.begin(); iter != m_Slime.end();) {
		if ((*iter)->GetHp() <= 0) {
			if ((*iter)->GetDan() <= 6) {
				m_Slime.push_back(new cSlime(m_image, D3DXVECTOR2((*iter)->GetPos().x - 40, (*iter)->GetPos().y), (*iter)->GetDan() + 1));
				m_Slime.push_back(new cSlime(m_image, D3DXVECTOR2((*iter)->GetPos().x + 40, (*iter)->GetPos().y), (*iter)->GetDan() + 1));
			}
			SAFE_DELETE(*iter);
			iter = m_Slime.erase(iter);
		}
		else ++iter;
	}
}

void cSlimeAdmin::Render()
{
	for (auto iter : m_Slime)
		iter->Render();
}
