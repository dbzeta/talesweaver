#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}
////////////////////////////////////
//생성자 소멸자 빠이빠이
////////////////////////////////////

//초기화 해주는 함수
HRESULT mainGame::init(void)
{
	gameNode::init(true);
	
	_bgmVolume = 0.5f;
	_soundEffectVolume = 1.0f;

	SCENEMANAGER->addScene("로딩씬", new loadingScene);
	SCENEMANAGER->addScene("인트로씬", new introScene);
	SCENEMANAGER->addScene("오프닝무비씬", new openingVideoScene);
	SCENEMANAGER->addScene("맵툴씬", new maptoolScene);
	SCENEMANAGER->addScene("셀렉트씬", new selectScene);
	SCENEMANAGER->addScene("크리에이트씬", new createScene);
	SCENEMANAGER->addScene("게임씬", new gameScene);

	SCENEMANAGER->changeScene("로딩씬");


	IMAGEMANAGER->addPngFrameImage("마우스포인터", "image\\마우스포인터.png", 416, 31, 13, 1, false, false);
	IMAGEMANAGER->addPngFrameImage("마우스포인터클릭", "image\\마우스포인터클릭.png", 54, 25, 2, 1, false, false);

	_mousePointer = IMAGEMANAGER->findImage("마우스포인터");
	_count = 0;
	_frameX = _frameY = 0;
	_isPlayVideo = false;

	return S_OK;
}

//메모리 해제함수
void mainGame::release(void)
{
	gameNode::release();

	SCENEMANAGER->release();

}

//연산 하는 곳
void mainGame::update(void)
{
	gameNode::update();
	
	// 버튼 클릭
	if (_leftButtonDown)
	{
		_mousePointer = IMAGEMANAGER->findImage("마우스포인터클릭");
		_frameX = 0;
		_count = 0;
	}

	if (_mousePointer == IMAGEMANAGER->findImage("마우스포인터클릭"))
	{
		if (_mousePointer->getMaxFrameX() < _frameX)
		{
			_mousePointer = IMAGEMANAGER->findImage("마우스포인터");
			_frameX = 0;
			_count = 0;
		}
	}
	else
	{
		if (_mousePointer->getMaxFrameX() < _frameX) _frameX = 0;
	}

	if (++_count % 10 == 0) _frameX++;



	if (SCENEMANAGER->findScene("오프닝무비씬") == S_OK) _isPlayVideo = true;
	else _isPlayVideo = false;

	

	SCENEMANAGER->update();
}

//그려주는 곳
void mainGame::render()
{
	//흰색 도화지 한장이 필요함
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	
	SCENEMANAGER->render();
	
	_mousePointer->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _frameX, _frameY);
	
	if (_isPlayVideo) return;

	if (_debug) TIMEMANAGER->render(getMemDC());

	//백버퍼에 옮겨 그려줄 애 건들지마라 얘는
	this->getBackBuffer()->render(getHDC(), 0, 0);

}


