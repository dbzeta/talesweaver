#include "stdafx.h"
#include "skillScreen.h"


skillScreen::skillScreen()
{
}


skillScreen::~skillScreen()
{
}

HRESULT skillScreen::init()
{
	_divisionX = _divisionY = 0;

	_currentSkillType = SKILL_FIRE;
	_currentSkill = NULL;

	_background = IMAGEMANAGER->addPngImage("스킬창", "UI\\스킬창\\스킬창.png", 438, 400, false, false);
	_rc = RectMake(WINSIZEX - _background->getWidth() - 30, 100, _background->getWidth(), _background->getHeight());
	
	_isUse = false;

	setBtn();
	setSkill();

	return S_OK;
}

void skillScreen::release()
{

}

void skillScreen::update()
{

	if (_isUse)
	{
		// 현재 선택된 스킬의 레벨을 올릴수 있을 때 frameX = 0;
		// minus : 현재 선택된 스킬레벨이 0 이하면 frameX = 3로 지정
		// minus : 현재 선택된 스킬레벨이 1 이상이면 frameX = 0
		// plus / minus : frameX != 3 이면 PtInRect 로 검사 후 frameX는 2로 지정
		if (_plusBtn.frameX != 3 && PtInRect(&_plusBtn.rc, _ptMouse)) _plusBtn.frameX = 2;
		else if (_minusBtn.frameX != 3 && PtInRect(&_minusBtn.rc, _ptMouse)) _minusBtn.frameX = 2;
	}
}

void skillScreen::render()
{
	if (_isUse)
	{
		// 스킬창 랜더
		_background->render(getMemDC(), _rc.left, _rc.top);

		// 스킬 타입 버튼 랜더
		for (int i = 0; i < _vSkillBtnList.size(); ++i)
		{
			_vSkillBtnList[i]->btnImage->render(getMemDC(), _vSkillBtnList[i]->rc.left, _vSkillBtnList[i]->rc.top);
			_vSkillBtnList[i]->selectSkillImage->frameRender(getMemDC(), _vSkillBtnList[i]->rc.left - 4, _vSkillBtnList[i]->rc.top - 3, _vSkillBtnList[i]->selectSkillFrameX, 0);
		}

		// 스킬 타입 버튼에 따른 스킬 랜더


		// 그 외 버튼 랜더
		_minusBtn.btnImage->frameRender(getMemDC(), _minusBtn.rc.left, _minusBtn.rc.top, _minusBtn.frameX, _minusBtn.frameY);
		_plusBtn.btnImage->frameRender(getMemDC(), _plusBtn.rc.left, _plusBtn.rc.top, _plusBtn.frameX, _plusBtn.frameY);
		_exitBtn.btnImage->frameRender(getMemDC(), _exitBtn.rc.left, _exitBtn.rc.top, _exitBtn.frameX, _exitBtn.frameY);
	}

}

bool skillScreen::isOnceClick()
{
	if (_isUse)
	{
		// 현재 마우스 좌표 및 _rc 값
		_divisionX = _ptMouse.x;
		_divisionY = _ptMouse.y;
		_tempRc = { _rc.left, _rc.top, _rc.right, _rc.bottom };

		// 스킬 종류 버튼 클릭
		if (PtInRect(&_fireType->rc, _ptMouse))
		{
			_currentSkillType = SKILL_FIRE;
		}
		else if (PtInRect(&_windType->rc, _ptMouse))
		{
			_currentSkillType = SKILL_WIND;
		}
		else if (PtInRect(&_electricType->rc, _ptMouse))
		{
			_currentSkillType = SKILL_ELECTRIC;
		}
		else if (PtInRect(&_commonType->rc, _ptMouse))
		{
			_currentSkillType = SKILL_COMMON;
		}
		else if (PtInRect(&_swordType->rc, _ptMouse))
		{
			_currentSkillType = SKILL_SWORD;
		}
		else if (PtInRect(&_knifeType->rc, _ptMouse))
		{
			_currentSkillType = SKILL_KNIFE;
		}

		// 기타 버튼 클릭
		else if (PtInRect(&_plusBtn.rc, _ptMouse))
		{
			_plusBtn.frameX = 2;
			return true;
		}
		else if (PtInRect(&_minusBtn.rc, _ptMouse))
		{
			_minusBtn.frameX = 2;
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
		else
		{
			return false;
		}
		// 벡터안에 있는 스킬 타입과 비교해서 프레임 재설정.
		for (int i = 0; i < _vSkillBtnList.size(); ++i)
		{
			if (_currentSkillType == _vSkillBtnList[i]->skillType)
			{
				_vSkillBtnList[i]->selectSkillFrameX = 1;
			}
			else
			{
				_vSkillBtnList[i]->selectSkillFrameX = 0;
			}
		}
	}

	return false;
}

bool skillScreen::isStayClick()
{
	if (_isUse)
	{

		// 스킬창 옮길 때 사용

		if (PtInRect(&_rc, _ptMouse))
		{
			int moveX = (_divisionX - _ptMouse.x);
			int moveY = (_divisionY - _ptMouse.y);

			_rc.left = _tempRc.left - moveX;
			_rc.right = _tempRc.right - moveX;
			_rc.top = _tempRc.top - moveY;;
			_rc.bottom = _tempRc.bottom - moveY;

			if (_rc.left <= 0) { _rc.left = 1; _rc.right = _rc.left + _background->getWidth(); }
			if (_rc.right >= WINSIZEX) { _rc.left = WINSIZEX - 1 - _background->getWidth(); _rc.right = WINSIZEX - 1; }
			if (_rc.top <= 0) { _rc.top = 1; _rc.bottom = _rc.top + _background->getHeight(); }
			if (_rc.bottom >= WINSIZEY) { _rc.top = WINSIZEY - 1 - _background->getHeight(); _rc.bottom = WINSIZEY - 1; }

			// 현재 스킬창 기준으로 rc값을 새로 맞추어준다.
			_fireType->rc = RectMake(_rc.left + 24, _rc.top + 60, 24, 24);
			_windType->rc = RectMake(_fireType->rc.right + 9, _rc.top + 60, 24, 24);
			_electricType->rc = RectMake(_windType->rc.right + 9, _rc.top + 60, 24, 24);
			_commonType->rc = RectMake(_electricType->rc.right + 9, _rc.top + 60, 24, 24);
			_swordType->rc = RectMake(_commonType->rc.right + 9, _rc.top + 60, 24, 24);
			_knifeType->rc = RectMake(_swordType->rc.right + 9, _rc.top + 60, 24, 24);

			// 기타 버튼 위치 재설정
			_plusBtn.rc = RectMake(_rc.right - 196, _rc.top + 114, _plusBtn.btnImage->getFrameWidth(), _plusBtn.btnImage->getFrameHeight());
			_minusBtn.rc = RectMake(_rc.right - 196, _rc.top + 130, _minusBtn.btnImage->getFrameWidth(), _minusBtn.btnImage->getFrameHeight());
			_exitBtn.rc = RectMake(_rc.right - 25, _rc.top + 5, _exitBtn.btnImage->getFrameWidth(), _exitBtn.btnImage->getFrameHeight());

			return true;
		}
	}

	return false;
}

void skillScreen::setSkill()
{
}

void skillScreen::setBtn()
{
	IMAGEMANAGER->addPngFrameImage("스킬종류선택", "UI\\스킬창\\스킬종류선택.png", 64, 29, 2, 1, false, false);
	
	// 스킬 종류 버튼 세팅
	_fireType = new tagSkillButton;
	_fireType->btnImage = IMAGEMANAGER->addPngImage("화염계", "UI\\스킬창\\화염계.png", 24, 24, false, false);
	_fireType->rc = RectMake(_rc.left + 24, _rc.top + 60, 24, 24);
	_fireType->selectSkillImage = IMAGEMANAGER->findImage("스킬종류선택");
	_fireType->selectSkillFrameX = 1;
	_fireType->selectSkillFrameY = 0;
	_fireType->skillType = SKILL_FIRE;
	_vSkillBtnList.push_back(_fireType);
	
	_windType = new tagSkillButton;
	_windType->btnImage = IMAGEMANAGER->addPngImage("바람계", "UI\\스킬창\\바람계.png", 24, 24, false, false);
	_windType->rc = RectMake(_fireType->rc.right + 9, _rc.top + 60, 24, 24);
	_windType->selectSkillImage = IMAGEMANAGER->findImage("스킬종류선택");
	_windType->selectSkillFrameX = _windType->selectSkillFrameY = 0;
	_windType->skillType = SKILL_WIND;
	_vSkillBtnList.push_back(_windType);

	_electricType = new tagSkillButton;
	_electricType->btnImage = IMAGEMANAGER->addPngImage("전격계", "UI\\스킬창\\전격계.png", 24, 24, false, false);
	_electricType->rc = RectMake(_windType->rc.right + 9, _rc.top + 60, 24, 24);
	_electricType->selectSkillImage = IMAGEMANAGER->findImage("스킬종류선택");
	_electricType->selectSkillFrameX = _electricType->selectSkillFrameY = 0;
	_electricType->skillType = SKILL_ELECTRIC;
	_vSkillBtnList.push_back(_electricType);

	_commonType = new tagSkillButton;
	_commonType->btnImage = IMAGEMANAGER->addPngImage("공통계열", "UI\\스킬창\\공통계열.png", 24, 24, false, false);
	_commonType->rc = RectMake(_electricType->rc.right + 9, _rc.top + 60, 24, 24);
	_commonType->selectSkillImage = IMAGEMANAGER->findImage("스킬종류선택");
	_commonType->selectSkillFrameX = _commonType->selectSkillFrameY = 0;
	_commonType->skillType = SKILL_COMMON;
	_vSkillBtnList.push_back(_commonType);

	_swordType = new tagSkillButton;
	_swordType->btnImage = IMAGEMANAGER->addPngImage("검계열", "UI\\스킬창\\검계열.png", 24, 24, false, false);
	_swordType->rc = RectMake(_commonType->rc.right + 9, _rc.top + 60, 24, 24);
	_swordType->selectSkillImage = IMAGEMANAGER->findImage("스킬종류선택");
	_swordType->selectSkillFrameX = _swordType->selectSkillFrameY = 0;
	_swordType->skillType = SKILL_SWORD;
	_vSkillBtnList.push_back(_swordType);

	_knifeType = new tagSkillButton;
	_knifeType->btnImage = IMAGEMANAGER->addPngImage("도계열", "UI\\스킬창\\도계열.png", 24, 24, false, false);
	_knifeType->rc = RectMake(_swordType->rc.right + 9, _rc.top + 60, 24, 24);
	_knifeType->selectSkillImage = IMAGEMANAGER->findImage("스킬종류선택");
	_knifeType->selectSkillFrameX = _knifeType->selectSkillFrameY = 0;
	_knifeType->skillType = SKILL_KNIFE;
	_vSkillBtnList.push_back(_knifeType);

	// 그 외 버튼 세팅
	_levelUpBtn.btnImage = IMAGEMANAGER->addPngFrameImage("스킬레벨업버튼", "UI\\스킬창\\레벨업버튼.png", 164, 17, 4, 1, false, false);
	_levelUpBtn.frameX = _levelUpBtn.frameY = 0;
	_levelUpBtn.rc = RectMake(0, 0, _levelUpBtn.btnImage->getFrameWidth(), _levelUpBtn.btnImage->getFrameHeight());

	_selectSkillBtn.btnImage = IMAGEMANAGER->addPngFrameImage("스킬선택버튼", "UI\\스킬창\\스킬선택버튼.png", 528, 38, 3, 1, false, false);
	_selectSkillBtn.frameX = _selectSkillBtn.frameY = 0;
	_selectSkillBtn.rc = RectMake(0, 0, _selectSkillBtn.btnImage->getFrameWidth(), _selectSkillBtn.btnImage->getFrameHeight());

	_plusBtn.btnImage = IMAGEMANAGER->addPngFrameImage("스킬레벨증가버튼", "UI\\스킬창\\스킬레벨증가버튼.png", 60, 15, 4, 1, false, false);
	_plusBtn.frameX = 3;
	_plusBtn.frameY = 0;
	_plusBtn.rc = RectMake(_rc.right - 196, _rc.top + 114, _plusBtn.btnImage->getFrameWidth(), _plusBtn.btnImage->getFrameHeight());
	
	_minusBtn.btnImage = IMAGEMANAGER->addPngFrameImage("스킬레벨감소버튼", "UI\\스킬창\\스킬레벨감소버튼.png", 60, 15, 4, 1, false, false);
	_minusBtn.frameX = 3;
	_minusBtn.frameY = 0;
	_minusBtn.rc = RectMake(_rc.right - 196, _rc.top + 130, _minusBtn.btnImage->getFrameWidth(), _minusBtn.btnImage->getFrameHeight());

	_exitBtn.btnImage = IMAGEMANAGER->addPngFrameImage("스킬창종료버튼", "UI\\스킬창\\종료버튼.png", 28, 14, 2, 1, false, false);
	_exitBtn.frameX = _exitBtn.frameY = 0;
	_exitBtn.rc = RectMake(_rc.right - 25, _rc.top + 5, _exitBtn.btnImage->getFrameWidth(), _exitBtn.btnImage->getFrameHeight());




}
