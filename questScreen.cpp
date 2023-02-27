#include "stdafx.h"
#include "questScreen.h"


questScreen::questScreen()
{
}


questScreen::~questScreen()
{
}

HRESULT questScreen::init()
{
	_background = IMAGEMANAGER->addPngImage("퀘스트창", "UI\\퀘스트창\\퀘스트창.png", 275, 348, false, false);
	_rc = RectMake(0, 100, _background->getWidth(), _background->getHeight());
	_subQuestScreen = IMAGEMANAGER->addPngImage("퀘스트내용창", "UI\\퀘스트창\\퀘스트내용창.png", 275, 348, false, false);
	_subQuestScreenRc = RectMake(_rc.right, _rc.top, _subQuestScreen->getWidth(), _subQuestScreen->getHeight());

	_isUse = false;

	setBtn();
	
	return S_OK;
}
void questScreen::release()
{

}

void questScreen::update()
{
	if (_isUse)
	{

	}
}

void questScreen::render()
{
	if (_isUse)
	{
		// 퀘스트창 퀘스트 내용창
		_background->render(getMemDC(), _rc.left, _rc.top);
		_subQuestScreen->render(getMemDC(), _subQuestScreenRc.left, _subQuestScreenRc.top);

		// 버튼
		_giveUpBtn.btnImage->frameRender(getMemDC(), _giveUpBtn.rc.left, _giveUpBtn.rc.top, _giveUpBtn.frameX, _giveUpBtn.frameY);
		_closeBtn.btnImage->frameRender(getMemDC(), _closeBtn.rc.left, _closeBtn.rc.top, _closeBtn.frameX, _closeBtn.frameY);
		_exitBtn.btnImage->frameRender(getMemDC(), _exitBtn.rc.left, _exitBtn.rc.top, _exitBtn.frameX, _exitBtn.frameY);
	}
}

bool questScreen::isOnceClick()
{
	if (_isUse)
	{
		if (PtInRect(&_giveUpBtn.rc, _ptMouse))
		{
			_giveUpBtn.frameX = 1;
			return true;
		}
		else if (PtInRect(&_closeBtn.rc, _ptMouse))
		{
			_closeBtn.frameX = 1;
			return true;
		}
		else if (PtInRect(&_exitBtn.rc, _ptMouse))
		{
			_exitBtn.frameX = 1;
			_isUse = false;
			return true;
		}
		else if (PtInRect(&_rc, _ptMouse))
		{
			return true;
		}
		else if (PtInRect(&_subQuestScreenRc, _ptMouse))
		{
			return true;
		}
	}

	return false;
}

bool questScreen::isOnceClickUp()
{
	if (_isUse)
	{
		if (_giveUpBtn.frameX == 1)
		{
			_giveUpBtn.frameX = 0;
			return true;
		}
		else if (_closeBtn.frameX == 1)
		{
			_closeBtn.frameX = 0;
			if (PtInRect(&_closeBtn.rc, _ptMouse)) _isUse = false;
			return true;
		}
		else if (_exitBtn.frameX == 1)
		{
			_exitBtn.frameX = 0;
			return true;
		}
	}

	return false;
}
void questScreen::setBtn()
{
	_giveUpBtn.btnImage = IMAGEMANAGER->addPngFrameImage("퀘스트포기버튼", "UI\\퀘스트창\\포기버튼.png", 140, 17, 2, 1, false, false);
	_giveUpBtn.frameX = _giveUpBtn.frameY = 0;
	_giveUpBtn.rc = RectMake(_subQuestScreenRc.right - 158, _subQuestScreenRc.bottom - 26, _giveUpBtn.btnImage->getFrameWidth(), _giveUpBtn.btnImage->getFrameHeight());

	_closeBtn.btnImage = IMAGEMANAGER->addPngFrameImage("퀘스트창닫기버튼", "UI\\퀘스트창\\닫기버튼.png", 140, 17, 2, 1, false, false);
	_closeBtn.frameX = _closeBtn.frameY = 0;
	_closeBtn.rc = RectMake(_subQuestScreenRc.right - 79, _subQuestScreenRc.bottom - 26, _closeBtn.btnImage->getFrameWidth(), _closeBtn.btnImage->getFrameHeight());

	_exitBtn.btnImage = IMAGEMANAGER->addPngFrameImage("퀘스트창종료버튼", "UI\\퀘스트창\\종료버튼.png", 28, 14, 2, 1, false, false);
	_exitBtn.frameX = _exitBtn.frameY = 0;
	_exitBtn.rc = RectMake(_rc.right - 25, _rc.top + 8, _exitBtn.btnImage->getFrameWidth(), _exitBtn.btnImage->getFrameHeight());


}