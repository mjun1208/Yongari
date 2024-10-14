#include "DXUT.h"
#include "cSingleTexture.h"


cSingleTexture::cSingleTexture()
{
}


cSingleTexture::~cSingleTexture()
{
	SAFE_RELEASE(texturePtr);
}

cTexture * cSingleTexture::AddImage(const string & path, int count)
{
	D3DXGetImageInfoFromFileA(path.c_str(), &info);

	D3DXCreateTextureFromFileExA(g_device, path.c_str(), info.Width, info.Height, info.MipLevels, 0, info.Format,
		D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(10, 10, 10, 10), &info, NULL, &texturePtr);

	return this;
}

cTexture * cSingleTexture::FindImage(int count)
{
	return this;
}

int cSingleTexture::Length()
{
	return 1;
}
