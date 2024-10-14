#include "DXUT.h"
#include "cButton.h"


cButton::cButton(float x, float y, const string& key, const string& path)
	:m_pos(x, y)
{
	m_Nomal = IMAGE->AddImage(key + ("Nomal"), path + ("Nomal.png"));
	m_OnCursor = IMAGE->AddImage(key + ("OnCursor"), path + ("OnCursor.png"));
	m_Click = IMAGE->AddImage(key + ("Click"), path + ("Click.png"));
	SettingRect();

}


cButton::~cButton()
{
	SAFE_DELETE(this->m_frame);
}

bool cButton::Update() {
	POINT ptMouse;
	HWND m_hWnd = DXUTGetHWND();
	GetCursorPos(&ptMouse);
	ScreenToClient(m_hWnd, &ptMouse);

	if (PtInRect(&m_rc, ptMouse)) {
		b_OnCursor = true;

		if (INPUT->MouseLPress()) {
			b_Click = true;
		}
		else if (INPUT->MouseLUp()) {
			return true;
		}
		else
			b_Click = false;
	}
	else {
		b_OnCursor = false;
		b_Click = false;
	}

	return false;
}
void cButton::Render() {
	if (!b_OnCursor) {
		IMAGE->Render(m_Nomal, m_pos.x, m_pos.y, 0, true);
	}
	if (b_Click) {
		IMAGE->Render(m_Click, m_pos.x, m_pos.y, 0, true);
	}
	else if (b_OnCursor) {
		IMAGE->Render(m_OnCursor, m_pos.x, m_pos.y, 0, true);
	}
}

