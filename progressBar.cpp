#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMakeCenter(x, y, width, height);

	_progressBarTop = IMAGEMANAGER->addImage("topBar", "hpBarTop.bmp", x, y, width, height, true, RGB(255, 0, 255));
	_progressBarBottom = IMAGEMANAGER->addImage("backBar", "hpBarBottom.bmp", x, y, width, height, true, RGB(255, 0, 255));

	_width = _progressBarTop->getWidth();


	return S_OK;
}

HRESULT progressBar::init(char* frontImage, char* backImage, float x, float y, int width, int height)
{
	_x = x;
	_y = y;


	char strFrontImageName[128];
	char strBackImageName[128];

	ZeroMemory(strFrontImageName, sizeof(strFrontImageName));
	ZeroMemory(strBackImageName, sizeof(strBackImageName));

	sprintf(strFrontImageName, "image\\로딩씬\\%s.png", frontImage);
	sprintf(strBackImageName, "image\\로딩씬\\%s.png", backImage);

	_progressBarBottom = IMAGEMANAGER->addPngImage(frontImage, "image\\로딩씬\\loadingBarBottom.png", 1024, 7, false, false);

	_progressBarTop = IMAGEMANAGER->addPngImage(backImage, "image\\로딩씬\\loadingBarTop.png", 1024, 7, false, false);

	_width = _progressBarTop->getWidth();

	_rcProgress = RectMakeCenter(_x, _y, _progressBarBottom->getWidth(), _progressBarBottom->getHeight());

	// _loadingImage = IMAGEMANAGER->addImage("loadingCharacter", "angryBird.bmp", 52, 52, true, RGB(255, 0, 255));

	_running = true;

	DWORD threadID = 0;
	CloseHandle(CreateThread(NULL, 0, threadFunc, (void*)this, 0, &threadID));

	return S_OK;
}


void progressBar::release()
{

}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y,
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight());
}

void progressBar::render()
{
	/*
	IMAGEMANAGER->render("backBar", getMemDC(),
	_rcProgress.left + _progressBarBottom->getWidth() / 2,
	_y + _progressBarBottom->getHeight() / 2,
	0, 0,
	_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

	IMAGEMANAGER->render("topBar", getMemDC(),
	_rcProgress.left + _progressBarTop->getWidth() / 2,
	_y + _progressBarTop->getHeight() / 2,
	0, 0,
	_width, _progressBarTop->getHeight());

	*/

	_progressBarBottom->render(getMemDC(), _rcProgress.left, _y, 0, 0,
		_progressBarBottom->getWidth(),
		_progressBarBottom->getHeight());

	_progressBarTop->render(getMemDC(), _rcProgress.left, _y, 0, 0,
		_width,
		_progressBarBottom->getHeight());

	int characterX = _rcProgress.left + _width;
	static int count = 0;
	static int characterFrameX = 0;
	//if (count % 13 == 0) characterFrameX++;
	//if (characterFrameX > IMAGEMANAGER->findImage("loadingCharacter")->getMaxFrameX()) characterFrameX = 0;


	//	_loadingImage->render(getMemDC());

}


void progressBar::threadProc(void)
{
	// _loadingImage->setX(_rcProgress.left + _width - _loadingImage->getWidth() + 15);
	// _loadingImage->setY(WINSIZEY - _loadingImage->getHeight() + 5);
}

DWORD progressBar::threadFunc(LPVOID lParam)
{
	progressBar* tt = (progressBar*)lParam;

	while (tt->getRunning())
	{
		tt->threadProc();

		Sleep(1);
	}

	return 0;
}


void progressBar::setGauge(float currentGauge, float maxGauge)
{
	//요거하면 백분율 나옴 왜그런지는 한 번 읽어보고 생각해바바
	_width = (currentGauge / maxGauge) * _progressBarBottom->getWidth();

}
