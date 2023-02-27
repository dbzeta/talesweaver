#include "stdafx.h"
#include "status.h"
#include "player.h"

status::status()
{
}


status::~status()
{
}

HRESULT status::init()
{
	_background = IMAGEMANAGER->findImage("캐릭터스탯창");
	_frameX = _frameY = 0;
	_rc = RectMake(WINSIZEX - _background->getFrameWidth() - 30, 100, _background->getFrameWidth(), _background->getFrameHeight());

	_isUse = false;
	_isClick = false;

	// 버튼 세팅

	setBtn();

	return S_OK;
}

void status::release()
{

}

void status::update()
{
	if (_isUse)
	{
		if (!_isClick)
		{
			if (_player->getIsPossibleLevelUp()) _levelUpBtn.frameX = 1;
			else if (!_player->getIsPossibleLevelUp()) _levelUpBtn.frameX = 0;

			for (int i = 0; i < 7; ++i)
			{
				if (PtInRect(&_upBtn[i].rc, _ptMouse))
				{
					if (_upBtn[i].isUse)
					{
						_upBtn[i].frameX = 1;
					}
				}
				else
				{
					_upBtn[i].frameX = 0;
				}
			}


			// 초기화를 먼저 해준다
			for (int i = 0; i < 7; ++i)
			{
				_upBtn[i].isUse = false;
			}

			// 현재 포인트가 필요 포인트량과 같거나 많아야 use로 해준다.
			if (_player->getPoint() >= _player->getRequirePoint(true, false, false, false, false, false, false)) _upBtn[0].isUse = true;
			if (_player->getPoint() >= _player->getRequirePoint(false, true, false, false, false, false, false)) _upBtn[1].isUse = true;
			if (_player->getPoint() >= _player->getRequirePoint(false, false, true, false, false, false, false)) _upBtn[2].isUse = true;
			if (_player->getPoint() >= _player->getRequirePoint(false, false, false, true, false, false, false)) _upBtn[3].isUse = true;
			if (_player->getPoint() >= _player->getRequirePoint(false, false, false, false, true, false, false)) _upBtn[4].isUse = true;
			if (_player->getPoint() >= _player->getRequirePoint(false, false, false, false, false, true, false)) _upBtn[5].isUse = true;
			if (_player->getPoint() >= _player->getRequirePoint(false, false, false, false, false, false, true)) _upBtn[6].isUse = true;
			

			
		}
	}
}

void status::render()
{
	if (_isUse)
	{
		_background->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, _frameY);

		_levelUpBtn.btnImage->frameRender(getMemDC(), _levelUpBtn.rc.left, _levelUpBtn.rc.top, _levelUpBtn.frameX, _levelUpBtn.frameY);

		char str[128];
		sprintf_s(str, "%3d", _player->getLevel());
		TextOut(getMemDC(), _rc.left + 280, _rc.top + 53 - 20, str, strlen(str));
		sprintf_s(str, "%16s", _player->getNickName());
		TextOut(getMemDC(), _rc.left + 230, _rc.top + 53, str, strlen(str));
		
		// 베기
		if (_player->getType() == P_TYPE_HACK) sprintf_s(str, "%16s", "베기 타입" );
		// 찌르기
		else if (_player->getType() == P_TYPE_STAB) sprintf_s(str, "%16s","찌르기 타입") ;
		// 물리 복합
		else if (_player->getType() == P_TYPE_MIX) sprintf_s(str, "%16s", "물리복합 타입");
		TextOut(getMemDC(), _rc.left + 230, _rc.top + 53 + 20, str, strlen(str));

		// 경험치
		sprintf_s(str, "%10d", _player->getCurrentExp());
		TextOut(getMemDC(), _rc.left + 60, _rc.top + 138, str, strlen(str));
		sprintf_s(str, "%10d", _player->getRequireExp());
		TextOut(getMemDC(), _rc.left + 160, _rc.top + 138, str, strlen(str));
		sprintf_s(str, "%10d", _player->getMaxExp());
		TextOut(getMemDC(), _rc.left + 260, _rc.top + 138, str, strlen(str));

		if (_statBtn.isClick)
		{
			char str[128];
			sprintf_s(str, "%3d", _player->getStab() + _player->getEquipStab());
			TextOut(getMemDC(), _rc.left + 80, _rc.top + 198, str, strlen(str));
			sprintf_s(str, "%3d", _player->getHack() + _player->getEquipHack());
			TextOut(getMemDC(), _rc.left + 80, _rc.top + 217, str, strlen(str));
			sprintf_s(str, "%3d", _player->getInt() + _player->getEquipInt());
			TextOut(getMemDC(), _rc.left + 80, _rc.top + 236, str, strlen(str));
			sprintf_s(str, "%3d", _player->getDef() + _player->getEquipDef());
			TextOut(getMemDC(), _rc.left + 80, _rc.top + 255, str, strlen(str));
			sprintf_s(str, "%3d", _player->getMr() + _player->getEquipMr());
			TextOut(getMemDC(), _rc.left + 80, _rc.top + 274, str, strlen(str));
			sprintf_s(str, "%3d", _player->getDex() + _player->getEquipDex());
			TextOut(getMemDC(), _rc.left + 80, _rc.top + 293, str, strlen(str));
			sprintf_s(str, "%3d", _player->getAgi() + _player->getEquipAgi());
			TextOut(getMemDC(), _rc.left + 80, _rc.top + 312, str, strlen(str));

			
			// up 버튼
			for (int i = 0; i < 7; ++i)
			{
				if (_upBtn[i].isUse) _upBtn[i].image->frameRender(getMemDC(), _upBtn[i].rc.left, _upBtn[i].rc.top, _upBtn[i].frameX, _upBtn[i].frameY);
			}

			sprintf_s(str, "%2d", _player->getRequirePoint(true, false, false, false, false, false, false));
			TextOut(getMemDC(), _upBtn[0].rc.right + 11, _upBtn[0].rc.top - 3, str, strlen(str));
			sprintf_s(str, "%2d", _player->getRequirePoint(false, true, false, false, false, false, false));
			TextOut(getMemDC(), _upBtn[1].rc.right + 11, _upBtn[1].rc.top - 3, str, strlen(str));
			sprintf_s(str, "%2d", _player->getRequirePoint(false, false, true, false, false, false, false));
			TextOut(getMemDC(), _upBtn[2].rc.right + 11, _upBtn[2].rc.top - 3, str, strlen(str));
			sprintf_s(str, "%2d", _player->getRequirePoint(false, false, false, true, false, false, false));
			TextOut(getMemDC(), _upBtn[3].rc.right + 11, _upBtn[3].rc.top - 3, str, strlen(str));
			sprintf_s(str, "%2d", _player->getRequirePoint(false, false, false, false, true, false, false));
			TextOut(getMemDC(), _upBtn[4].rc.right + 11, _upBtn[4].rc.top - 3, str, strlen(str));
			sprintf_s(str, "%2d", _player->getRequirePoint(false, false, false, false, false, true, false));
			TextOut(getMemDC(), _upBtn[5].rc.right + 11, _upBtn[5].rc.top - 3, str, strlen(str));
			sprintf_s(str, "%2d", _player->getRequirePoint(false, false, false, false, false, false, true));
			TextOut(getMemDC(), _upBtn[6].rc.right + 11, _upBtn[6].rc.top - 3, str, strlen(str));

			sprintf_s(str, "%4d / %4d", _player->getCurrentHp(), _player->getMaxHp());
			TextOut(getMemDC(), _rc.left + 280, _rc.top + 198, str, strlen(str));
			sprintf_s(str, "%4d / %4d", _player->getCurrentMp(), _player->getMaxMp());
			TextOut(getMemDC(), _rc.left + 280, _rc.top + 217, str, strlen(str));
			sprintf_s(str, "%4d / %4d", _player->getCurrentSp(), _player->getMaxSp());
			TextOut(getMemDC(), _rc.left + 280, _rc.top + 236, str, strlen(str));
			sprintf_s(str, "%10d", _player->getMoney());
			TextOut(getMemDC(), _rc.left + 280, _rc.top + 255, str, strlen(str));
			sprintf_s(str, "%10d", _player->getPoint());
			TextOut(getMemDC(), _rc.left + 280, _rc.top + 274, str, strlen(str));

		}
		else if (_battleBtn.isClick)
		{
			char str[128];
			sprintf_s(str, "%3d", (_player->getMinDamage() + _player->getMaxDamage()) / 2);
			TextOut(getMemDC(), _rc.left + 100, _rc.top + 193, str, strlen(str));
			sprintf_s(str, "%3d", (int)((_player->getMinDamage() + _player->getMaxDamage()) * 0.45));
			TextOut(getMemDC(), _rc.left + 100, _rc.top + 211, str, strlen(str));
			sprintf_s(str, "%3d", _player->getDefense());
			TextOut(getMemDC(), _rc.left + 100, _rc.top + 229, str, strlen(str));
			sprintf_s(str, "%3d", _player->getMagicRegidense());
			TextOut(getMemDC(), _rc.left + 100, _rc.top + 247, str, strlen(str));
			sprintf_s(str, "%3d / %3d", _player->getDexterity(), _player->getAvoidability());
			TextOut(getMemDC(), _rc.left + 100, _rc.top + 265, str, strlen(str));
			sprintf_s(str, "%3d / %3d", _player->getWalkSpeed(),_player->getRunningSpeed());
			TextOut(getMemDC(), _rc.left + 100, _rc.top + 283, str, strlen(str));


			sprintf_s(str, "%3d / %3d", _player->getStab(), _player->getEquipStab());
			TextOut(getMemDC(), _rc.left + 285, _rc.top + 193, str, strlen(str));
			sprintf_s(str, "%3d / %3d", _player->getHack(), _player->getEquipHack());
			TextOut(getMemDC(), _rc.left + 285, _rc.top + 211, str, strlen(str));
			sprintf_s(str, "%3d / %3d", _player->getInt(), _player->getEquipInt());
			TextOut(getMemDC(), _rc.left + 285, _rc.top + 229, str, strlen(str));
			sprintf_s(str, "%3d / %3d", _player->getDef(), _player->getEquipDef());
			TextOut(getMemDC(), _rc.left + 285, _rc.top + 247, str, strlen(str));
			sprintf_s(str, "%3d / %3d", _player->getMr(), _player->getEquipMr());
			TextOut(getMemDC(), _rc.left + 285, _rc.top + 265, str, strlen(str));
			sprintf_s(str, "%3d / %3d", _player->getDex(), _player->getEquipDex());
			TextOut(getMemDC(), _rc.left + 285, _rc.top + 283, str, strlen(str));
			sprintf_s(str, "%3d / %3d", _player->getAgi(), _player->getEquipAgi());
			TextOut(getMemDC(), _rc.left + 285, _rc.top + 301, str, strlen(str));
			sprintf_s(str, "%3d / %3d", 
				_player->getStab() + 
				_player->getHack() +
				_player->getInt() +
				_player->getDef() +
				_player->getMr() +
				_player->getDex() +
				_player->getAgi(),
				_player->getEquipStab() +
				_player->getEquipHack() +
				_player->getEquipInt() +
				_player->getEquipDef() +
				_player->getEquipMr() +
				_player->getEquipDex() + 
				_player->getEquipAgi()
			);
			TextOut(getMemDC(), _rc.left + 285, _rc.top + 319, str, strlen(str));
		}

	}
}


bool status::isOnceClick() 
{
	if (_isUse)
	{

		_isClick = true;

		// 현재 마우스 좌표 및 _rc 값
		_divisionX = _ptMouse.x;
		_divisionY = _ptMouse.y;
		_tempRc = { _rc.left, _rc.top, _rc.right, _rc.bottom };

		for (int i = 0; i < 7; ++i)
		{
			if (PtInRect(&_upBtn[i].rc, _ptMouse))
			{
				if (_upBtn[i].isUse)
				{
					_upBtn[i].frameX = 2;
					return true;
				}
			}
			else
			{
				_upBtn[i].frameX = 0;
			}
		}
		

		if (PtInRect(&_statBtn.rc,_ptMouse))
		{
			_frameX = 0;
			_statBtn.isClick = true;
			_battleBtn.isClick = !_statBtn.isClick;
			return true;
		}
		else if (PtInRect(&_battleBtn.rc,_ptMouse))
		{
			_frameX = 1;
			_battleBtn.isClick = true;
			_statBtn.isClick = !_battleBtn.isClick;
			return true;
		}
		else if (PtInRect(&_exitBtn.rc, _ptMouse))
		{
			_isUse = false;
			return true;
		}
		else if (PtInRect(&_levelUpBtn.rc, _ptMouse))
		{
			if (_player->getIsPossibleLevelUp())
			{
				_levelUpBtn.frameX = 2;
				return true;
			}
		}
		else if (PtInRect(&_rc, _ptMouse))
		{
			return true;
		}
	}

	return false; 
}

bool status::isOnceClickUp() 
{
	if (_isUse)
	{
		_isClick = false;
		for (int i = 0; i < 7; ++i)
		{
			_upBtn[i].frameX = 0;
			if (PtInRect(&_upBtn[i].rc, _ptMouse))
			{
				if (_upBtn[i].isUse)
				{
					if (i == 0) { _player->addStab(); }
					else if (i == 1) { _player->addHack(); }
					else if (i == 2) { _player->addInt(); }
					else if (i == 3) { _player->addDef(); }
					else if (i == 4) { _player->addMr(); }
					else if (i == 5) { _player->addDex(); }
					else if (i == 6) { _player->addAgi(); }
					return true;
				}
			}
		}

		if (PtInRect(&_levelUpBtn.rc, _ptMouse))
		{
			if (_player->getIsPossibleLevelUp())
			{
				_levelUpBtn.frameX = 0;
				_player->levelUp();
			}
			return true;
		}
	}
	return false;
}

bool status::isStayClick()
{
	
	if (_isUse)
	{
		for (int i = 0; i < 7; ++i)
		{
			if (_upBtn[i].isUse)
			{
				if (PtInRect(&_upBtn[i].rc, _ptMouse)) return true;
			}
		}

		if (PtInRect(&_rc, _ptMouse))
		{

			int moveX = (_divisionX - _ptMouse.x);
			int moveY = (_divisionY - _ptMouse.y);

			_rc.left = _tempRc.left - moveX;
			_rc.right = _tempRc.right - moveX;
			_rc.top = _tempRc.top - moveY;;
			_rc.bottom = _tempRc.bottom - moveY;

			if (_rc.left <= 0) { _rc.left = 1; _rc.right = _rc.left + _background->getFrameWidth(); }
			if (_rc.right >= WINSIZEX) { _rc.left = WINSIZEX - 1 - _background->getFrameWidth(); _rc.right = WINSIZEX - 1; }
			if (_rc.top <= 0) { _rc.top = 1; _rc.bottom = _rc.top + _background->getFrameHeight(); }
			if (_rc.bottom >= WINSIZEY) { _rc.top = WINSIZEY - 1 - _background->getFrameHeight(); _rc.bottom = WINSIZEY - 1; }

			// 현재 창 기준으로 rc값을 새로 맞추어준다.
			_statBtn.rc = RectMake(_rc.left + 7, (_rc.bottom + _rc.top) / 2 - 5, 78, 19);
			_battleBtn.rc = RectMake(_rc.left + 88, (_rc.bottom + _rc.top) / 2 - 5, 78, 19);
			_exitBtn.rc = RectMake(_rc.left + 345, _rc.top + 5, 14, 14);
			_levelUpBtn.rc = RectMake(_rc.right - 50, _rc.top + 33, _levelUpBtn.btnImage->getFrameWidth(), _levelUpBtn.btnImage->getFrameHeight());
			for (int i = 0; i < 7; ++i)
			{
				_upBtn[i].rc = RectMake(_rc.left + 122, _rc.top + 201 + (i * 19), 11, 11);
			}
			return true;
		}
	}

	return false; 
}

void status::setBtn()
{
	// 캐릭터 상태창 각 세부 버튼
	_statBtn.rc = RectMake(_rc.left + 7, (_rc.bottom + _rc.top) / 2 - 5, 78, 19);
	_frameX = 1;
	_statBtn.isClick = true;

	_battleBtn.rc = RectMake(_rc.left + 88, (_rc.bottom + _rc.top) / 2 - 5, 78, 19);
	_frameX = 0;
	_battleBtn.isClick = false;

	// 그외 버튼
	_exitBtn.rc = RectMake(_rc.left + 345, _rc.top + 5, 14, 14);

	_levelUpBtn.btnImage = IMAGEMANAGER->addPngFrameImage("캐릭터상태창레벨업버튼", "UI\\캐릭터상태창\\레벨업.png", 120, 17, 3, 1, false, false);
	_levelUpBtn.frameX = _levelUpBtn.frameY = 0;
	_levelUpBtn.rc = RectMake(_rc.right - 50, _rc.top + 33, _levelUpBtn.btnImage->getFrameWidth(), _levelUpBtn.btnImage->getFrameHeight());

	for (int i = 0; i < 7; ++i)
	{
		_upBtn[i].image = IMAGEMANAGER->findImage("게임씬up버튼");
		_upBtn[i].frameX = _upBtn[i].frameY = 0;
		_upBtn[i].rc = RectMake(_rc.left + 122, _rc.top + 201 + (i * 19), 11, 11);
		_upBtn[i].isUse = false;
	}

}