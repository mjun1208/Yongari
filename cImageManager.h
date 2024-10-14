#pragma once
#include "singleton.h"
class cTexture;

class cFrame {
public:
	int NowFrame = 0;
	int StartFrame = 0;
	int EndFrame = 0;
	
	unsigned long FrameSkip = 0;
	unsigned long FrameDelay = 0;

	void SetFrame(int start, int end, unsigned long delay);
	
	bool Frame();
};
class cImageManager : public singleton<cImageManager>
{
private:
	LPD3DXSPRITE m_sprite = nullptr;
	map<string, cTexture*> m_image;
	LPD3DXFONT pFont = nullptr;
public:
	cImageManager();
	virtual ~cImageManager();
	
	void Init();
	void Release();

	cTexture* AddImage(const string& key, const string& path , int count = 0);
	cTexture* FindImage(const string& key, int count = -1);

	void Begin();
	void End();

	void ReBegin() { End(); Begin(); };

	void PrintText(const string& str, float x, float y, float size, D3DCOLOR color, bool Center = false);

	void Render(cTexture * pTexture, float x, float y, const D3DXVECTOR3& size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255), bool Center = false);
	void Render(cTexture * pTexture, float x, float y, float rot = 0, bool Center = false);

	void CropRender(cTexture * pTexture, float x, float y, const D3DXVECTOR3 & size,const RECT& rcRange);

	void DrawLine(D3DXVECTOR2* vecList, int count, float width, bool bIsAntialias, D3DCOLOR color);

	void LostDevice();
	void ResetDevice();
};

#define IMAGE cImageManager::GetInstance()
