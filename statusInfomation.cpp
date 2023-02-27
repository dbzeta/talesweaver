#include "stdafx.h"
#include "statusInfomation.h"
#include "player.h"
#include "enemyManager.h"

statusInfomation::statusInfomation()
{
}


statusInfomation::~statusInfomation()
{
}

HRESULT statusInfomation::init()
{
	// 플레이어 상태 정보 init
	_background = IMAGEMANAGER->findImage("상태정보창");
	_rc = RectMake(0, 0, _background->getWidth(), _background->getHeight());

	_hpBar = IMAGEMANAGER->findImage("상태정보창HP바");
	_mpBar = IMAGEMANAGER->findImage("상태정보창MP바");
	_spBar = IMAGEMANAGER->findImage("상태정보창SP바");
	_expBar = IMAGEMANAGER->findImage("상태정보창경험치바");
	_comboScreen = IMAGEMANAGER->findImage("상태정보창콤보창");

	_hpRc = RectMake(_rc.left + 97, _rc.top + 18, _hpBar->getWidth(), _hpBar->getHeight());
	_mpRc = RectMake(_rc.left + 97, _rc.top + 33, _mpBar->getWidth(), _mpBar->getHeight());
	_spRc = RectMake(_rc.left + 97, _rc.top + 48, _spBar->getWidth(), _spBar->getHeight());
	_expRc = RectMake(_rc.left + 70, _rc.top + 64, _expBar->getWidth(), _expBar->getHeight());

	_isHpPercent = false;
	_isHpValue = true;
	_isMpPercent = false;
	_isMpValue = true;
	_isSpPercent = false;
	_isSpValue = true;

	// 에너미 상태 정보 init
	_targetEnemy = NULL;

	return S_OK;
}

void statusInfomation::release()
{

}

void statusInfomation::update()	
{
	if (_targetEnemy != NULL) if (!_targetEnemy->getIsLive()) _targetEnemy = NULL;
}

void statusInfomation::render()	
{

	// HP MP SP 경험치바는 상태정보창 보다 먼저 나와야 하므로 먼저 랜더해준다.

	_hpBar->render(getMemDC(), _rc.left + 97, _rc.top + 18, 0, 0,
		_player->getCurrentHp() * _hpBar->getWidth() / _player->getMaxHp(),
		_hpBar->getHeight());
	_mpBar->render(getMemDC(), _rc.left + 97, _rc.top + 33, 0, 0,
		_player->getCurrentMp() * _mpBar->getWidth() / _player->getMaxMp(),
		_mpBar->getHeight());
	_spBar->render(getMemDC(), _rc.left + 97, _rc.top + 48, 0, 0,
		_player->getCurrentSp() * _spBar->getWidth() / _player->getMaxSp(),
		_spBar->getHeight());
	_expBar->render(getMemDC(), _rc.left + 70, _rc.top + 64, 0, 0,
		_player->getCurrentExp() * _expBar->getWidth() / _player->getMaxExp(),
		_expBar->getHeight());
	
	char str[128];
	if(_isHpPercent) sprintf_s(str, "%5d%%", _player->getCurrentHp() * 100 / _player->getMaxHp());
	else if(_isHpValue)  sprintf_s(str, "%5d", _player->getCurrentHp());
	else if(!_isHpPercent && !_isHpValue) strcpy_s(str, "");
	TextOut(getMemDC(), _hpRc.left + 8, _hpRc.top, str, strlen(str));
	
	if (_isMpPercent) sprintf_s(str, "%5d%%", _player->getCurrentMp() * 100 / _player->getMaxMp());
	else if (_isMpValue)  sprintf_s(str, "%5d", _player->getCurrentMp());
	else strcpy_s(str, "");
	TextOut(getMemDC(), _mpRc.left + 8, _mpRc.top, str, strlen(str));
	
	if (_isSpPercent) sprintf_s(str, "%5d%%", _player->getCurrentSp() * 100 / _player->getMaxSp());
	else if (_isSpValue)  sprintf_s(str, "%5d", _player->getCurrentSp());
	else strcpy_s(str, "");
	TextOut(getMemDC(), _spRc.left + 8, _spRc.top, str, strlen(str));

	
	// 백그라운드 ( 상태정보창 )
	_background->render(getMemDC(), _rc.left, _rc.top);

	// 콤보창
	_comboScreen->render(getMemDC(), _rc.left + 83, _rc.top + 70);


	// 에너미 상태 정보창
	if (_targetEnemy != NULL)
	{
		char str[128];

		// 에너미 상태 정보창 출력
		IMAGEMANAGER->findImage("에너미상태정보창")->render(getMemDC(),
			WINSIZEX / 2 - IMAGEMANAGER->findImage("에너미상태정보창")->getWidth() / 2, 0);
		// 에너미 이미지
		// RECT tempRc = RectMake(WINSIZEX / 2 - IMAGEMANAGER->findImage("에너미상태정보창")->getWidth() / 2 + 5, 5, 40, 35);
		// _targetEnemy->getImage()->frameRender(getMemDC(),
		// 	tempRc.left, tempRc.top, 0, 0);
		
		// 에너미 HP바
		IMAGEMANAGER->findImage("에너미상태정보창HP바")->render(getMemDC(),
			WINSIZEX / 2 - IMAGEMANAGER->findImage("에너미상태정보창HP바")->getWidth() / 2 + 31, 19, 0, 0,
			_targetEnemy->getCurrentHp() * IMAGEMANAGER->findImage("에너미상태정보창HP바")->getWidth() / _targetEnemy->getMaxHp() ,
			IMAGEMANAGER->findImage("에너미상태정보창HP바")->getHeight());
		
		// 에너미 이름
		sprintf_s(str, "%s", _targetEnemy->getEnemyName());
		TextOut(getMemDC(),
			WINSIZEX / 2 - IMAGEMANAGER->findImage("에너미상태정보창")->getWidth() / 2 + 100, 0, str, strlen(str));
		// 에너미 HP퍼센트
		sprintf_s(str, "( %3d%% )", _targetEnemy->getCurrentHp() * 100 / _targetEnemy->getMaxHp());
		TextOut(getMemDC(),
			WINSIZEX / 2 - IMAGEMANAGER->findImage("에너미상태정보창HP바")->getWidth() / 2 + 81, 19, str, strlen(str));

	}

}

bool statusInfomation::isOnceClick()
{
	if (PtInRect(&_hpRc, _ptMouse))
	{
		if (!_isHpPercent && !_isHpValue) _isHpValue = true;
		else if (!_isHpPercent && _isHpValue)
		{
			_isHpPercent = true; 
			_isHpValue = false;
		}
		else if (_isHpPercent && !_isHpValue)
		{
			_isHpValue = false;
			_isHpPercent = false;
		}

		return true;
	}
	else if (PtInRect(&_mpRc, _ptMouse))
	{
		if (!_isMpPercent && !_isMpValue) _isMpValue = true;
		else if (!_isHpPercent && _isMpValue)
		{
			_isMpPercent = true;
			_isMpValue = false;
		}
		else if (_isMpPercent && !_isMpValue)
		{
			_isMpValue = false;
			_isMpPercent = false;
		}

		return true;
	}
	else if (PtInRect(&_spRc, _ptMouse))
	{
		if (!_isSpPercent && !_isSpValue) _isSpValue = true;
		else if (!_isSpPercent && _isSpValue)
		{
			_isSpPercent = true;
			_isSpValue = false;
		}
		else if (_isSpPercent && !_isSpValue)
		{
			_isSpValue = false;
			_isSpPercent = false;
		}

		return true;
	}
	else if (PtInRect(&_expRc, _ptMouse))
	{
		return true;
	}
	else if (PtInRect(&_rc, _ptMouse))
	{
		return true;
	}

	return false;
}

bool statusInfomation::isOnceClickUp()
{
	return false;
}
