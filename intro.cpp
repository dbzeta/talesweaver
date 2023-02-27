#include "stdafx.h"
#include "intro.h"


intro::intro()
{
}


intro::~intro()
{
}

HRESULT intro::init()
{
	_isPlaySound = false;

	_background = IMAGEMANAGER->findImage("인트로씬배경");

	_exitBtn.btnImage = IMAGEMANAGER->findImage("종료버튼");
	_exitBtn.rc = RectMake(11, WINSIZEY - 53, _exitBtn.btnImage->getFrameWidth(), _exitBtn.btnImage->getFrameHeight());
	_exitBtn.frameX = _exitBtn.frameY = 0;

	_startBtn.btnImage = IMAGEMANAGER->findImage("시작버튼");
	_startBtn.rc = RectMake(WINSIZEX - 13 - _startBtn.btnImage->getFrameWidth(), WINSIZEY - 61, _startBtn.btnImage->getFrameWidth(), _startBtn.btnImage->getFrameHeight());
	_startBtn.frameX = _startBtn.frameY = 0;

	_optionBtn.btnImage = IMAGEMANAGER->findImage("환경설정버튼");
	_optionBtn.rc = RectMake(_startBtn.rc.left - _optionBtn.btnImage->getFrameWidth() - 17, _startBtn.rc.top + 6, _optionBtn.btnImage->getFrameWidth(), _optionBtn.btnImage->getFrameHeight());
	_optionBtn.frameX = _optionBtn.frameY = 0;

	_maptoolBtn.btnImage = IMAGEMANAGER->findImage("맵툴버튼");
	_maptoolBtn.frameX = _maptoolBtn.frameY = 0;
	_maptoolBtn.rc = RectMake(_exitBtn.rc.right + 16, _exitBtn.rc.top + 1, _maptoolBtn.btnImage->getFrameWidth(), _maptoolBtn.btnImage->getFrameHeight());

	_openingVideoBtn.btnImage = IMAGEMANAGER->findImage("오프닝비디오버튼");
	_openingVideoBtn.frameX = _openingVideoBtn.frameY = 0;
	_openingVideoBtn.rc = RectMake(_maptoolBtn.rc.right + 10, _maptoolBtn.rc.top, _openingVideoBtn.btnImage->getFrameWidth(), _openingVideoBtn.btnImage->getFrameHeight());

	_programExitScreen.background = IMAGEMANAGER->findImage("인트로씬프로그램종료창");
	_programExitScreen.rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, _programExitScreen.background->getWidth(), _programExitScreen.background->getHeight());
	_programExitScreen.noBtn.btnImage = IMAGEMANAGER->findImage("인트로씬프로그램종료창취소버튼");
	_programExitScreen.noBtn.frameX = _programExitScreen.noBtn.frameY = 0;
	_programExitScreen.noBtn.rc = RectMake(_programExitScreen.rc.right - 107, _programExitScreen.rc.top + 40, _programExitScreen.noBtn.btnImage->getFrameWidth(), _programExitScreen.noBtn.btnImage->getFrameHeight());
	_programExitScreen.yesBtn.btnImage = IMAGEMANAGER->findImage("인트로씬프로그램종료창확인버튼");
	_programExitScreen.yesBtn.frameX = _programExitScreen.yesBtn.frameY = 0;
	_programExitScreen.yesBtn.rc = RectMake(_programExitScreen.rc.left + 16, _programExitScreen.rc.top + 40, _programExitScreen.yesBtn.btnImage->getFrameWidth(), _programExitScreen.yesBtn.btnImage->getFrameHeight());
	_programExitScreen.isUse = false;

	_isClick = false;

	_isUseOption = false;

	_bgmValue = RectMake(WINSIZEX / 2 + 10, WINSIZEY / 2 - 90, 15, 15);
	_soundEffectValue = RectMake(WINSIZEX / 2 + 10, WINSIZEY / 2 - 65, 15, 15);

	return S_OK;
}

void intro::release()			  
{

}

void intro::update()
{
	if (!_isClick)
	{
		if (PtInRect(&_exitBtn.rc, _ptMouse))
		{
			if (!_isPlaySound) SOUNDMANAGER->play("효과음버튼충돌", _soundEffectVolume);
			_isPlaySound = true;
			_exitBtn.frameX = 1;
		}
		else if (PtInRect(&_maptoolBtn.rc, _ptMouse))
		{
			if (!_isPlaySound) SOUNDMANAGER->play("효과음버튼충돌", _soundEffectVolume);
			_isPlaySound = true;
			_maptoolBtn.frameX = 1;
		}
		else if (PtInRect(&_openingVideoBtn.rc, _ptMouse))
		{
			if (!_isPlaySound) SOUNDMANAGER->play("효과음버튼충돌", _soundEffectVolume);
			_isPlaySound = true;
			_openingVideoBtn.frameX = 1;
		}
		else if (PtInRect(&_optionBtn.rc, _ptMouse))
		{
			if (!_isPlaySound) SOUNDMANAGER->play("효과음버튼충돌", _soundEffectVolume);
			_isPlaySound = true;
			_optionBtn.frameX = 1;
		}
		else if (PtInRect(&_startBtn.rc, _ptMouse))
		{
			if (!_isPlaySound) SOUNDMANAGER->play("효과음버튼충돌", _soundEffectVolume);
			_isPlaySound = true;
			_startBtn.frameX = 1;
		}
		else if (PtInRect(&_programExitScreen.yesBtn.rc, _ptMouse))
		{
			if (!_isPlaySound) SOUNDMANAGER->play("효과음버튼충돌", _soundEffectVolume);
			_isPlaySound = true;
			_programExitScreen.yesBtn.frameX = 1;
		}
		else if (PtInRect(&_programExitScreen.noBtn.rc, _ptMouse))
		{
			if (!_isPlaySound) SOUNDMANAGER->play("효과음버튼충돌", _soundEffectVolume);
			_isPlaySound = true;
			_programExitScreen.noBtn.frameX = 1;
		}
		else
		{
			_isPlaySound = false;
			_exitBtn.frameX = 0;
			_maptoolBtn.frameX = 0;
			_openingVideoBtn.frameX = 0;
			_optionBtn.frameX = 0;
			_startBtn.frameX = 0;
			_programExitScreen.yesBtn.frameX = 0;
			_programExitScreen.noBtn.frameX = 0;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_isClick = true;

		if (PtInRect(&_exitBtn.rc, _ptMouse))
		{
			SOUNDMANAGER->play("효과음버튼클릭", _soundEffectVolume);
			_exitBtn.frameX = 2;
		}
		else if (PtInRect(&_maptoolBtn.rc, _ptMouse))
		{
			SOUNDMANAGER->play("효과음버튼클릭", _soundEffectVolume);
			_maptoolBtn.frameX = 2;
		}
		else if (PtInRect(&_openingVideoBtn.rc, _ptMouse))
		{
			SOUNDMANAGER->play("효과음버튼클릭", _soundEffectVolume);
			_openingVideoBtn.frameX = 2;
		}
		else if (PtInRect(&_optionBtn.rc, _ptMouse))
		{
			SOUNDMANAGER->play("효과음버튼클릭", _soundEffectVolume);
			_optionBtn.frameX = 2;
		}
		else if (PtInRect(&_startBtn.rc, _ptMouse))
		{
			SOUNDMANAGER->play("효과음스타트버튼클릭", _soundEffectVolume);
			_startBtn.frameX = 2;
		}

		if (_isUseOption)
		{
			if (PtInRect(&_bgmValue, _ptMouse))
			{
				_isUseBgm = !_isUseBgm;
				if (!_isUseBgm) 
				{ 
					_tempBgmVolume = _bgmVolume;
					_bgmVolume = 0;
					SOUNDMANAGER->stop("인트로씬");
				}
				else
				{
					_bgmVolume = _tempBgmVolume;
					_tempBgmVolume = 0;
					SOUNDMANAGER->play("인트로씬", _bgmVolume);
				}
			}
			else if (PtInRect(&_soundEffectValue, _ptMouse))
			{
				_isUseSoundEffect = !_isUseSoundEffect;
				if (!_isUseSoundEffect)
				{
					_tempSoundEffectVolume = _soundEffectVolume;
					_soundEffectVolume = 0;
				}
				else
				{
					_soundEffectVolume = _tempSoundEffectVolume;
					_tempSoundEffectVolume = 0;
				}
			}
		}

		if (_programExitScreen.isUse)
		{
			if (PtInRect(&_programExitScreen.yesBtn.rc, _ptMouse))
			{
				_programExitScreen.yesBtn.frameX = 2;
			}
			else if (PtInRect(&_programExitScreen.noBtn.rc, _ptMouse))
			{
				_programExitScreen.noBtn.frameX = 2;
			}
			else
			{
				_programExitScreen.yesBtn.frameX = 0;
				_programExitScreen.noBtn.frameX = 0;
			}
		}

	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_isClick = false;
		if (PtInRect(&_exitBtn.rc, _ptMouse))
		{
			PostQuitMessage(0);
		}
		else if (PtInRect(&_maptoolBtn.rc, _ptMouse))
		{
			SCENEMANAGER->changeScene("맵툴씬");
		}
		else if (PtInRect(&_openingVideoBtn.rc, _ptMouse))
		{
			SCENEMANAGER->changeScene("오프닝무비씬");
		}
		else if (PtInRect(&_optionBtn.rc, _ptMouse))
		{
			_isUseOption = !_isUseOption;
		}
		else if (PtInRect(&_startBtn.rc, _ptMouse))
		{
			SCENEMANAGER->changeScene("셀렉트씬");
			SOUNDMANAGER->play("셀렉트씬", _bgmVolume);
		}

		if (_programExitScreen.isUse)
		{
			if (_programExitScreen.yesBtn.frameX == 2)
			{
				_programExitScreen.yesBtn.frameX = 0;
				if (PtInRect(&_programExitScreen.yesBtn.rc, _ptMouse))
				{
					PostQuitMessage(0);
				}
			}
			else if (_programExitScreen.noBtn.frameX == 2)
			{
				_programExitScreen.noBtn.frameX = 0;
				if (PtInRect(&_programExitScreen.noBtn.rc, _ptMouse))
				{
					_programExitScreen.isUse = false;
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		if (_isUseOption) _isUseOption = false;
		else _programExitScreen.isUse = !_programExitScreen.isUse;
	}

	


}

void intro::render()			  
{
	_background->render(getMemDC());
	_exitBtn.btnImage->frameRender(getMemDC(), _exitBtn.rc.left, _exitBtn.rc.top, _exitBtn.frameX, _exitBtn.frameY);
	_maptoolBtn.btnImage->frameRender(getMemDC(), _maptoolBtn.rc.left, _maptoolBtn.rc.top, _maptoolBtn.frameX, _maptoolBtn.frameY);
	_openingVideoBtn.btnImage->frameRender(getMemDC(), _openingVideoBtn.rc.left, _openingVideoBtn.rc.top, _openingVideoBtn.frameX, _openingVideoBtn.frameY);
	_optionBtn.btnImage->frameRender(getMemDC(), _optionBtn.rc.left, _optionBtn.rc.top, _optionBtn.frameX, _optionBtn.frameY);
	_startBtn.btnImage->frameRender(getMemDC(), _startBtn.rc.left, _startBtn.rc.top, _startBtn.frameX, _startBtn.frameY);
	

	if (_isUseOption)
	{
		IMAGEMANAGER->findImage("인트로씬환경설정")->render(getMemDC(), WINSIZEX / 2 - IMAGEMANAGER->findImage("인트로씬환경설정")->getWidth() / 2, WINSIZEY / 2 - IMAGEMANAGER->findImage("인트로씬환경설정")->getHeight() / 2);
		IMAGEMANAGER->findImage("인트로씬환경설정클릭")->frameRender(getMemDC(), _bgmValue.left, _bgmValue.top, _isUseBgm, 0);
		IMAGEMANAGER->findImage("인트로씬환경설정클릭")->frameRender(getMemDC(), _soundEffectValue.left, _soundEffectValue.top, _isUseSoundEffect, 0);
	}
	if (_programExitScreen.isUse)
	{
		_programExitScreen.background->render(getMemDC(), _programExitScreen.rc.left, _programExitScreen.rc.top);
		_programExitScreen.yesBtn.btnImage->frameRender(getMemDC(), _programExitScreen.yesBtn.rc.left, _programExitScreen.yesBtn.rc.top, _programExitScreen.yesBtn.frameX, _programExitScreen.yesBtn.frameY);
		_programExitScreen.noBtn.btnImage->frameRender(getMemDC(), _programExitScreen.noBtn.rc.left, _programExitScreen.noBtn.rc.top, _programExitScreen.noBtn.frameX, _programExitScreen.noBtn.frameY);
	}

}