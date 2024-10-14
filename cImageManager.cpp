#include "DXUT.h"
#include "cImageManager.h"

#include "cSingleTexture.h"
#include "cMultiTexture.h"
#include "cTexture.h"

cImageManager::cImageManager()
	:m_sprite(nullptr)
{

}


cImageManager::~cImageManager()
{
	Release();
}

void cImageManager::Init()
{
	D3DXCreateSprite(g_device, &m_sprite);
}

void cImageManager::Release()
{
	SAFE_RELEASE(m_sprite);

	for (auto iter : m_image) {
		SAFE_DELETE(iter.second);
	}
	m_image.clear();
}

cTexture * cImageManager::AddImage(const string & key, const string & path, int count)
{
	auto find = m_image.find(key);

	if (find == m_image.end()) {
		cTexture* ret;
		if (count == 0) {
			ret = new cSingleTexture();
		}
		else {
			ret = new cMultiTexture();
		}
		ret->AddImage(path, count);

		m_image.insert(make_pair(key, ret));

		return ret;
	}
	else
		return find->second;
	return nullptr;

}

cTexture * cImageManager::FindImage(const string & key, int count)
{
	auto find = m_image.find(key);

	if (find != m_image.end()) {
		return find->second->FindImage(count);
	}
	else {
		return nullptr;
	}
}

void cImageManager::Begin()
{
	m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void cImageManager::End()
{
	m_sprite->End();
}

void cImageManager::PrintText(const string & str, float x, float y, float size, D3DCOLOR color, bool Center)
{
	D3DXMATRIX mat;
	if (!Center) {
		D3DXCreateFontA(g_device, size, 0, 10, 1, FALSE, HANGUL_CHARSET, 0, 0, 0, "Fixedsys", &pFont);

		D3DXMatrixTranslation(&mat, x, y, 0);
	}
	else {
		D3DXCreateFontA(g_device, size, 0, 0, 1, FALSE, HANGUL_CHARSET, 0, 0, 0, "Fixedsys", &pFont);

		D3DXMatrixTranslation(&mat, x - size * (str.size() * 0.25), y - size / 2.f, 0);
	}
	m_sprite->SetTransform(&mat);
	pFont->DrawTextA(m_sprite, str.c_str(), str.size(), NULL, DT_NOCLIP, color);

	SAFE_RELEASE(pFont);
}

void cImageManager::Render(cTexture * pTexture, float x, float y, const D3DXVECTOR3 & size, float rot, D3DCOLOR color, bool Center)
{
	if (pTexture) {
		D3DXMATRIX mat;
		D3DXMATRIX matS, matT, matR;

		D3DXMatrixScaling(&matS, size.x, size.y, size.z);
		D3DXMatrixTranslation(&matT, x, y, 0.f);
		D3DXMatrixRotationZ(&matR, D3DXToRadian(rot));

		mat = matS * matR * matT;

		m_sprite->SetTransform(&mat);
		if (Center) {
			m_sprite->Draw(pTexture->texturePtr, NULL,
				&D3DXVECTOR3(pTexture->info.Width / 2.f, pTexture->info.Height / 2.f, 0.f), NULL, color);
		}
		else {
			m_sprite->Draw(pTexture->texturePtr, NULL, NULL, NULL, color);
		}
	}
}

void cImageManager::Render(cTexture * pTexture, float x, float y, float rot, bool Center)
{
	if (pTexture) {
		D3DXMATRIX mat;
		//Vector3 vCenter(pTexture->info.Width / 2.f, pTexture->info.Height / 2.f, 0);

		D3DXMatrixAffineTransformation2D(&mat, 1.0f, NULL, D3DXToRadian(rot), &D3DXVECTOR2(x, y));

		m_sprite->SetTransform(&mat);
		if (!Center) {
			m_sprite->Draw(pTexture->texturePtr, NULL, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else
			m_sprite->Draw(pTexture->texturePtr, NULL,
				&D3DXVECTOR3(pTexture->info.Width / 2.f, pTexture->info.Height / 2.f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void cImageManager::CropRender(cTexture * pTexture, float x, float y, const D3DXVECTOR3 & size,const RECT & rcRange)
{
	D3DXMATRIX mat;
	D3DXMATRIX matS, matT, matR;

	D3DXMatrixScaling(&matS, size.x, size.y, size.z);
	D3DXMatrixTranslation(&matT, x, y, 0.f);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(0));

	mat = matS * matR * matT;

	m_sprite->SetTransform(&mat);
	m_sprite->Draw(pTexture->texturePtr, &rcRange, &D3DXVECTOR3(
		pTexture->info.Width / 2, pTexture->info.Height / 2, 0), nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));

}

void cImageManager::DrawLine(D3DXVECTOR2 * vecList, int count, float width, bool bIsAntialias, D3DCOLOR color)
{
	ID3DXLine* ILine;

	D3DXCreateLine(DXUTGetD3D9Device(), &ILine);

	ILine->SetWidth(width);
	ILine->SetAntialias(bIsAntialias);
	ILine->Begin();

	ILine->Draw(vecList, count, color);

	ILine->End();
	SAFE_RELEASE(ILine);
}

void cImageManager::LostDevice()
{
	m_sprite->OnLostDevice();
}

void cImageManager::ResetDevice()
{
	m_sprite->OnResetDevice();
}

void cFrame::SetFrame(int start, int end, unsigned long delay)
{
	NowFrame = StartFrame = start;
	EndFrame = end;
	FrameDelay = delay;
	FrameSkip = FrameDelay + timeGetTime();
}

bool cFrame::Frame()
{
	if (FrameSkip <= timeGetTime())
	{
		if (NowFrame >= EndFrame)
		{
			NowFrame = StartFrame;
		}
		else NowFrame++;

		FrameSkip = FrameDelay + timeGetTime();
		return true;
	}
	return false;
}
