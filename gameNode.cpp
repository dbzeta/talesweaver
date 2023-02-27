#include "stdafx.h"
#include "gameNode.h"

gameNode::gameNode()
{
}

gameNode::~gameNode()
{
}

//초기화 하는 함수
HRESULT gameNode::init(void)
{
	ShowCursor(false);

	_hdc = GetDC(_hWnd);
	_managerInit = false;
	_debug = false;
	_isWrite = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	ShowCursor(false);

	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;
	_debug = false;
	_isUseBgm = true;
	_isUseSoundEffect = true;

	SetBkMode(getMemDC(), TRANSPARENT);

	if (_managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);

		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		EFFECTMANAGER->init();
		SOUNDMANAGER->init();
		SCENEMANAGER->init();
		KEYANIMANAGER->init();
		TXTDATA->init();
		DATABASE->init();

		DRAWMANAGER->init();
	}


	return S_OK;
}



//메모리 해제 함수
void gameNode::release(void)
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);

		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->releaseSingleton();
		EFFECTMANAGER->releaseSingleton();
		SOUNDMANAGER->releaseSingleton();
		SCENEMANAGER->releaseSingleton();
		KEYANIMANAGER->releaseSingleton();
		TXTDATA->releaseSingleton();
		DATABASE->releaseSingleton();

		DRAWMANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

//갱신해주는 함수
void gameNode::update(void)
{
	// 마우스 가두기
	RECT rect;
	GetWindowRect(_hWnd, &rect); //영역 얻어옴
	rect.left += 12;
	rect.right -= 15;
	rect.top += 30;
	rect.bottom -= 15;
	ClipCursor(&rect); // 영역 밖은 커서 이동못하게 막는다

	SOUNDMANAGER->update();

	if (_len == 0) strcpy_s(_str, "");
}

//그려주는 함수
void gameNode::render(void)
{
}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	// DEVMODE dm;

	switch (iMessage)
	{
		case WM_CREATE:
			//ZeroMemory(&dm, sizeof(DEVMODE));
			//dm.dmSize = sizeof(DEVMODE);
			//dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
			//dm.dmBitsPerPel = 32;
			//dm.dmPelsWidth = WINSIZEX;
			//dm.dmPelsHeight = WINSIZEY;
			//if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			//	ChangeDisplaySettings(&dm, 0);

		break;
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>LOWORD(lParam);
			_ptMouse.y = static_cast<float>HIWORD(lParam);
		break;

		case WM_LBUTTONDOWN:
			_leftButtonDown = true;
		break;

		case WM_LBUTTONUP:
			_leftButtonDown = false;
		break;

		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
					PostMessage(hWnd, WM_DESTROY, 0, 0);
				break;
				case VK_BACK:
					_debug = !_debug;
				break;
				//case VK_F1:
				//	ChangeDisplaySettings(NULL, 0);
				//break;
			}
		break;
		case WM_CHAR:
			_len = strlen(_str);
			_str[_len] = wParam;
			_str[_len + 1] = NULL;
			
		break;
		case WM_DESTROY:
			// ESC
			
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}