#pragma once
#include "cScene.h"
class cEndScene : public cScene
{
private:
	cTexture * m_BackGround;
	cButton * m_Ok;
public:
	cEndScene();
	virtual ~cEndScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

