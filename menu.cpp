#include "stdafx.h"
#include "menu.h"
#include "player.h"

menu::menu()
{
}


menu::~menu()
{
}

HRESULT menu::init()
{
	_background = IMAGEMANAGER->addPngImage("메뉴창", "UI\\메뉴창\\메뉴창.png", 159, 232, false, false);
	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, _background->getWidth(), _background->getHeight());

	_isUse = false;

	setBtn();

	return S_OK;
}

void menu::release()
{

}

void menu::update()
{
	if (_isUse)
	{

	}
}

void menu::render()
{
	if (_isUse)
	{
		// 메뉴창 랜더
		_background->render(getMemDC(), _rc.left, _rc.top);

		// 버튼 랜더
		_showUtilizationClassBtn.btnImage->frameRender(getMemDC(), _showUtilizationClassBtn.rc.left, _showUtilizationClassBtn.rc.top, _showUtilizationClassBtn.frameX, _showUtilizationClassBtn.frameY);
		_settingOptionBtn.btnImage->frameRender(getMemDC(), _settingOptionBtn.rc.left, _settingOptionBtn.rc.top, _settingOptionBtn.frameX, _settingOptionBtn.frameY);
		_goSelectCharacterBtn.btnImage->frameRender(getMemDC(), _goSelectCharacterBtn.rc.left, _goSelectCharacterBtn.rc.top, _goSelectCharacterBtn.frameX, _goSelectCharacterBtn.frameY);
		_returnGameBtn.btnImage->frameRender(getMemDC(), _returnGameBtn.rc.left, _returnGameBtn.rc.top, _returnGameBtn.frameX, _returnGameBtn.frameY);
		_exitGameBtn.btnImage->frameRender(getMemDC(), _exitGameBtn.rc.left, _exitGameBtn.rc.top, _exitGameBtn.frameX, _exitGameBtn.frameY);

	}
}

bool menu::isOnceClick()
{

	if (_isUse)
	{
		// 메뉴창 버튼 클릭 시
		if (PtInRect(&_showUtilizationClassBtn.rc, _ptMouse))
		{
			_showUtilizationClassBtn.frameX = 1;
			return true;
		}
		else if (PtInRect(&_settingOptionBtn.rc, _ptMouse))
		{
			_settingOptionBtn.frameX = 1;
			return true;
		}
		else if (PtInRect(&_goSelectCharacterBtn.rc, _ptMouse))
		{
			_goSelectCharacterBtn.frameX = 1;
			return true;
		}
		else if (PtInRect(&_returnGameBtn.rc, _ptMouse))
		{
			_returnGameBtn.frameX = 1;
			return true;
		}
		else if (PtInRect(&_exitGameBtn.rc, _ptMouse))
		{
			_exitGameBtn.frameX = 1;
			return true;
		}
		// 메뉴창 선택 시
		else if (PtInRect(&_rc, _ptMouse))
		{
			return true;
		}
	}

	return false;
}

bool menu::isOnceClickUp()
{

	if (_showUtilizationClassBtn.frameX == 1)
	{
		_showUtilizationClassBtn.frameX = 0;
		if (PtInRect(&_showUtilizationClassBtn.rc, _ptMouse))
		{

		}
		return true;
	}
	else if (_settingOptionBtn.frameX == 1)
	{
		_settingOptionBtn.frameX = 0;
		if (PtInRect(&_settingOptionBtn.rc, _ptMouse))
		{

		}
		return true;
	}
	else if (_goSelectCharacterBtn.frameX == 1)
	{
		_goSelectCharacterBtn.frameX = 0;
		if (PtInRect(&_goSelectCharacterBtn.rc, _ptMouse))
		{
			_player->save();
			SOUNDMANAGER->stop(_currentBgm);
			SOUNDMANAGER->play("셀렉트씬", _bgmVolume);
			SCENEMANAGER->changeScene("셀렉트씬");
		}
		return true;
	}
	else if (_returnGameBtn.frameX == 1)
	{
		_returnGameBtn.frameX = 0;
		if (PtInRect(&_returnGameBtn.rc, _ptMouse))
		{
			_isUse = false;
		}
		return true;
	}
	else if (_exitGameBtn.frameX == 1)
	{
		_player->save();

		_exitGameBtn.frameX = 0;
		if (PtInRect(&_exitGameBtn.rc, _ptMouse))
		{
			PostQuitMessage(0);
		}
		return true;
	}

	return false;
}

void menu::setBtn()
{

	_showUtilizationClassBtn.btnImage = IMAGEMANAGER->addPngFrameImage("메뉴창이용등급확인버튼", "UI\\메뉴창\\이용등급확인버튼.png", 298, 21, 2, 1, false, false);
	_showUtilizationClassBtn.frameX = _showUtilizationClassBtn.frameY = 0;
	_showUtilizationClassBtn.rc = RectMake(_rc.left + 5, _rc.top + 6, _showUtilizationClassBtn.btnImage->getFrameWidth(), _showUtilizationClassBtn.btnImage->getFrameHeight());
	_settingOptionBtn.btnImage = IMAGEMANAGER->addPngFrameImage("메뉴창옵션설정버튼", "UI\\메뉴창\\옵션설정버튼.png", 298, 21, 2, 1, false, false);
	_settingOptionBtn.frameX = _settingOptionBtn.frameY = 0;
	_settingOptionBtn.rc = RectMake(_rc.left + 5, _rc.top + 62, _settingOptionBtn.btnImage->getFrameWidth(), _settingOptionBtn.btnImage->getFrameHeight());
	_goSelectCharacterBtn.btnImage = IMAGEMANAGER->addPngFrameImage("메뉴창캐릭터선택창으로버튼", "UI\\메뉴창\\캐릭터선택창으로버튼.png", 298, 21, 2, 1, false, false);
	_goSelectCharacterBtn.frameX = _goSelectCharacterBtn.frameY = 0;
	_goSelectCharacterBtn.rc = RectMake(_rc.left + 5, _rc.top + 118, _goSelectCharacterBtn.btnImage->getFrameWidth(), _goSelectCharacterBtn.btnImage->getFrameHeight());
	_returnGameBtn.btnImage = IMAGEMANAGER->addPngFrameImage("메뉴창게임복귀버튼", "UI\\메뉴창\\게임복귀버튼.png", 298, 21, 2, 1, false, false);
	_returnGameBtn.frameX = _returnGameBtn.frameY = 0;
	_returnGameBtn.rc = RectMake(_rc.left + 5, _rc.top + 174, _returnGameBtn.btnImage->getFrameWidth(), _returnGameBtn.btnImage->getFrameHeight());
	_exitGameBtn.btnImage = IMAGEMANAGER->addPngFrameImage("메뉴창프로그램종료버튼", "UI\\메뉴창\\프로그램종료버튼.png", 298, 21, 2, 1, false, false);
	_exitGameBtn.frameX = _exitGameBtn.frameY = 0;
	_exitGameBtn.rc = RectMake(_rc.left + 5, _rc.top + 202, _exitGameBtn.btnImage->getFrameWidth(), _exitGameBtn.btnImage->getFrameHeight());
}
