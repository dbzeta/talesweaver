#include "stdafx.h"
#include "openingVideo.h"

openingVideo::openingVideo()
{
}


openingVideo::~openingVideo()
{
}

HRESULT openingVideo::init()
{

	
	_playcount = 0;


	return S_OK;
}

void openingVideo::release()							
{

}

void openingVideo::update()								
{
	// ������� �����츦 �����ϰԵǸ� wm_lbuttonup�� �ȸ����� �ణ�� ���ð� �� ���� �����־���.
	// if (_playcount++ == 1)
	// {
	// 	_hWndVideo = MCIWndCreate(_hWnd, _hInstance, MCIWNDF_NOTIFYMODE | MCIWNDF_NOTIFYPOS
	// 		| MCIWNDF_NOPLAYBAR | MCIWNDF_NOMENU,
	// 		"movie\\OpeningMovie.avi");
	// 	MoveWindow(_hWndVideo, 0, 0, WINSIZEX, WINSIZEY, NULL);
	// 	MCIWndPlay(_hWndVideo);
	// 
	// }

	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		MCIWndStop(_hWndVideo); 
		MCIWndDestroy(_hWndVideo);
		SCENEMANAGER->changeScene("��Ʈ�ξ�");

	}
}

void openingVideo::render()								
{
}
								