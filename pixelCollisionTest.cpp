#include "stdafx.h"
#include "pixelCollisionTest.h"


pixelCollisionTest::pixelCollisionTest()
{
}


pixelCollisionTest::~pixelCollisionTest()
{
}

HRESULT pixelCollisionTest::init()
{
	//???? ?̹??? ????
	IMAGEMANAGER->addImage("????", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_ball = IMAGEMANAGER->addImage("??", "ball.bmp", 60, 60, true, RGB(255, 0, 255));

	_x = WINSIZEX / 2 - 100;
	_y = WINSIZEY / 2 + 100;

	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	//Ž???? -> 
	_probeY = _y + _ball->getHeight() / 2;



	return S_OK;
}

void pixelCollisionTest::release()
{

}

void pixelCollisionTest::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 2.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 2.0f;
	}

	//Ž?? ???? ???? ??ǥ?? ?????? ???? ???????ش?
	_probeY = _y + _ball->getHeight() / 2;

	for (int i = _probeY - 50; i < _probeY + 50; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("????")->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _ball->getHeight() / 2;
			break;
		}
	}




	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

}

void pixelCollisionTest::render()
{
	IMAGEMANAGER->findImage("????")->render(getMemDC());

	_ball->render(getMemDC(), _rc.left, _rc.top);
}