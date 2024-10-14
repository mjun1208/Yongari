#include "DXUT.h"
#include "cSlime.h"


cSlime::cSlime(cTexture * image, D3DXVECTOR2 pos,int Dan)
	:m_image(image),m_pos(pos) , m_Dan(Dan)
{
	m_frame = new cFrame;
	m_frame->SetFrame(0, 3, 50);
	m_Width = m_image->info.Width / Dan;
	m_Height = m_image->info.Height / Dan;
	m_Hp = 100 / Dan;
}


cSlime::~cSlime()
{
	SAFE_DELETE(m_frame);
}

void cSlime::Update()
{
	m_frame->Frame();
	m_pos.y += 12 * m_Dan * DX_Time;
}

void cSlime::Render()
{
	IMAGE->Render(m_image->FindImage(m_frame->NowFrame), m_pos.x, m_pos.y,  D3DXVECTOR3(1.f / m_Dan, 1.f / m_Dan, 1.f/ m_Dan),0, D3DCOLOR_XRGB(255,255,255), true);
}
