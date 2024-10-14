#include "DXUT.h"
#include "cSceneManager.h"

#include "cScene.h"
cSceneManager::cSceneManager()
	:m_NextScene(nullptr), m_NowScene(nullptr)
{
}


cSceneManager::~cSceneManager()
{
	Release();
}

cScene * cSceneManager::AddScene(const string & key, cScene * scenePtr)
{
	if (!scenePtr)
		return nullptr;
	if (m_Scene.find(key) != m_Scene.end())
		return nullptr;
	m_Scene.insert(make_pair(key, scenePtr));
	return scenePtr;
}

cScene * cSceneManager::ChangeScene(const string & key)
{
	auto find = m_Scene.find(key);
	if (find == m_Scene.end())
		return nullptr;

	m_NextScene = find->second;
	return m_NextScene;
}

void cSceneManager::Update()
{
	if (m_NextScene) {
		if (m_NowScene)
			m_NowScene->Release();
		m_NextScene->Init();
		m_NowScene = m_NextScene;
		m_NextScene = nullptr;
	}
	if (m_NowScene)
		m_NowScene->Update();

}

void cSceneManager::Render()
{
	if (m_NowScene)
		m_NowScene->Render();
}

void cSceneManager::Release()
{
	if (m_NowScene)
		m_NowScene->Release();
	for (auto iter : m_Scene) {
		SAFE_DELETE(iter.second);
	}
	m_Scene.clear();
}
