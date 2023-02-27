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
	// 동영상용 윈도우를 생성하게되면 wm_lbuttonup이 안먹혀서 약간의 대기시간 후 생성 시켜주었다.
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
		SCENEMANAGER->changeScene("인트로씬");

	}
}

void openingVideo::render()								
{
}
								