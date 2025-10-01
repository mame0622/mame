#include "Mouse.h"

static const int KeyMap[] =
{
	VK_LBUTTON,		// ���{�^��
	VK_MBUTTON,		// ���{�^��
	VK_RBUTTON,		// �E�{�^��
};

// �R���X�g���N�^
Mouse::Mouse(const HWND& hwnd)
	: hwnd_(hwnd)
{
}

// �X�V
void Mouse::Update()
{
	MouseButton newButtonState = 0;

	for (int i = 0; i < ARRAYSIZE(KeyMap); ++i)
	{
		if (GetAsyncKeyState(KeyMap[i]) & 0x8000)
		{
			newButtonState |= (1 << i);
		}
	}

	// �z�C�[��
	wheel_[1] = wheel_[0];
	wheel_[0] = 0;

	// �{�^��
	buttonState_[1] = buttonState_[0];
	buttonState_[0] = newButtonState;
	buttonDown_		= ~buttonState_[1] & newButtonState; // �������u��
	buttonUp_		= ~newButtonState & buttonState_[1]; // �������u��

	POINT cursor;
	GetCursorPos(&cursor);
	ScreenToClient(hwnd_, &cursor);

	// ��ʂ̃T�C�Y���擾
	RECT rc;
	GetClientRect(hwnd_, &rc);
	UINT screenW = screenWidth_;
	UINT screenH = screenHeight_;
	UINT viewportW = rc.right - rc.left;
	UINT viewportH = rc.bottom - rc.top;

	// ��ʕ␳
	positionX_[1] = positionX_[0];
	positionY_[1] = positionY_[0];
	positionX_[0] = (LONG)(cursor.x / static_cast<float>(viewportW) * static_cast<float>(screenW));
	positionY_[0] = (LONG)(cursor.y / static_cast<float>(viewportH) * static_cast<float>(screenH));
}