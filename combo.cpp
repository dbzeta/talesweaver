#include "stdafx.h"
#include "combo.h"
#include "player.h"

combo::combo()
{
}


combo::~combo()
{
}

HRESULT combo::init()
{
	_background = IMAGEMANAGER->findImage("ÄÞº¸Ã¢");
	_rc = RectMake(WINSIZEX - _background->getWidth() - 30, 30, _background->getWidth(), _background->getHeight());

	// _selectComboImage = IMAGEMANAGER->findImage("ÄÞº¸½ºÅ³¼±ÅÃ");

	_isUse = false;

	// _isSelectAttackType = false;
	// _isClickCombo1 = false;
	// _isClickCombo2 = false;
	// _isClickCombo3 = false;
	
	// setBtn();
	// 
	// _stabRc = RectMake(_rc.left + 4, _rc.bottom + 3, 24, 24);
	// _verticalHackRc = RectMake(_rc.left + 36, _rc.bottom + 3, 24, 24);
	// _horizonHackRc = RectMake(_rc.left + 67, _rc.bottom + 3, 24, 24);

	return S_OK;
}

void combo::release()
{
	
}

void combo::update()
{
	if (!_isUse) return;
}

void combo::render()
{
	if (!_isUse) return;
	_background->render(getMemDC(), _rc.left, _rc.top);

	// if (_isSelectAttackType) _selectComboImage->render(getMemDC(), _rc.right, _rc.bottom);
}

bool combo::isOnceClick()
{
	// if (!_isSelectAttackType)
	// {
	// 	if (PtInRect(&_comboBtn[0].rc, _ptMouse))
	// 	{
	// 		_isClickCombo1 = true;
	// 		_isSelectAttackType = true;
	// 		return true;
	// 	}
	// 	else if (PtInRect(&_comboBtn[1].rc, _ptMouse))
	// 	{
	// 
	// 		return true;
	// 	}
	// 	else if (PtInRect(&_comboBtn[2].rc, _ptMouse))
	// 	{
	// 
	// 		return true;
	// 	}
	// }
	// else
	// {
	// 	if (PtInRect(&_stabRc, _ptMouse))
	// 	{
	// 		_isSelectAttackType = false;
	// 		if (_isClickCombo1) _player->setCombo(1, P_ATTACK_STAB);
	// 		else if (_isClickCombo2) _player->setCombo(2, P_ATTACK_STAB);
	// 		else if (_isClickCombo3) _player->setCombo(3, P_ATTACK_STAB);
	// 		_isClickCombo1 = false;
	// 		_isClickCombo2 = false;
	// 		_isClickCombo3 = false;
	// 		return true;
	// 	}
	// 	else if (PtInRect(&_verticalHackRc, _ptMouse))
	// 	{
	// 		_isSelectAttackType = false;
	// 		if (_isClickCombo1) _player->setCombo(1, P_ATTACK_VERTICAL_HACK );
	// 		else if (_isClickCombo2) _player->setCombo(2, P_ATTACK_VERTICAL_HACK );
	// 		else if (_isClickCombo3) _player->setCombo(3, P_ATTACK_VERTICAL_HACK );
	// 		_isClickCombo1 = false;
	// 		_isClickCombo2 = false;
	// 		_isClickCombo3 = false;
	// 		return true;
	// 	}
	// 	else if (PtInRect(&_horizonHackRc, _ptMouse))
	// 	{
	// 		_isSelectAttackType = false;
	// 		if (_isClickCombo1) _player->setCombo(1, P_ATTACK_HORIZONTAL_HACK);
	// 		else if (_isClickCombo2) _player->setCombo(2, P_ATTACK_HORIZONTAL_HACK);
	// 		else if (_isClickCombo3) _player->setCombo(3, P_ATTACK_HORIZONTAL_HACK);
	// 		_isClickCombo1 = false;
	// 		_isClickCombo2 = false;
	// 		_isClickCombo3 = false;
	// 		return true;
	// 	}
	// }
	// 
	// 
	return false;
}

void combo::setBtn()
{
	//_comboBtn[0].rc = RectMake(_rc.left + 14, _rc.top + 39, 25, 25);
	//_comboBtn[1].rc = RectMake(_rc.left + 46, _rc.top + 84, 25, 25);
	//_comboBtn[2].rc = RectMake(_rc.left + 77, _rc.top + 130, 25, 25);
}
