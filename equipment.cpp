#include "stdafx.h"
#include "equipment.h"
#include "player.h"
#include "itemManager.h"

equipment::equipment()
{
}


equipment::~equipment()
{
}

HRESULT equipment::init()
{
	_background = IMAGEMANAGER->addPngImage("장비창", "UI\\장비창\\장비창.png", 223, 445, false, false);
	_rc = RectMake(WINSIZEX - _background->getWidth() - 30, 120, _background->getWidth(), _background->getHeight());

	_isUse = false;

	for (int i = 0; i < MAXEQUIPMENTITEM; ++i)
	{
		int boxX = _rc.right - 217;
		int boxY = _rc.top + 27 + (i * 30) + (i * 2);
		_arrEquipmentItemList[i].boxNum = i;
		_arrEquipmentItemList[i].boxRc = RectMake(boxX, boxY, 28, 28);
		_arrEquipmentItemList[i].isUseBox = false;
		_arrEquipmentItemList[i].itemNum = 0;
	}

	return S_OK;
}

void equipment::release()
{

}

void equipment::update() 
{
	if (_isUse)
	{
	}
}

void equipment::render() 
{
	if (_isUse)
	{
		_background->render(getMemDC(), _rc.left, _rc.top);


		for (int i = 0; i < MAXEQUIPMENTITEM; ++i)
		{
			// Rectangle(getMemDC(), _arrEquipmentItemList[i].boxRc.left, _arrEquipmentItemList[i].boxRc.top, _arrEquipmentItemList[i].boxRc.right, _arrEquipmentItemList[i].boxRc.bottom);

			 if (!_arrEquipmentItemList[i].isUseBox) continue;
			 IMAGEMANAGER->findImage(_im->getItem(_arrEquipmentItemList[i].itemNum)->getIconImageName())
			 	->render(getMemDC(), _arrEquipmentItemList[i].boxRc.left, _arrEquipmentItemList[i].boxRc.top);
		}

	}
}

void equipment::updateEquipmentItem()
{
	// 장비 칸 초기화
	for (int i = 0; i < MAXEQUIPMENTITEM; ++i)
	{
		_arrEquipmentItemList[i].isUseBox = false;
		_arrEquipmentItemList[i].itemNum = 0;
	}

	// 장비 타입 확인
	for (int i = 0; i < _player->getEquipment().size(); ++i)
	{
		if ((_player->getEquipment()[i] % TYPE_EQUIPMENT) / (TYPE_HEAD - TYPE_EQUIPMENT) == 1)
		{
			_arrEquipmentItemList[0].isUseBox = true;
			_arrEquipmentItemList[0].itemNum = _player->getEquipment()[i];
		}
		else if ((_player->getEquipment()[i] % TYPE_EQUIPMENT) / (TYPE_HEAD - TYPE_EQUIPMENT) == 2)
		{

			_arrEquipmentItemList[1].isUseBox = true;
			_arrEquipmentItemList[1].itemNum = _player->getEquipment()[i];
		}
		else if ((_player->getEquipment()[i] % TYPE_EQUIPMENT) / (TYPE_HEAD - TYPE_EQUIPMENT) == 3)
		{

			_arrEquipmentItemList[2].isUseBox = true;
			_arrEquipmentItemList[2].itemNum = _player->getEquipment()[i];
		}
		else if ((_player->getEquipment()[i] % TYPE_EQUIPMENT) / (TYPE_HEAD - TYPE_EQUIPMENT) == 4)
		{

			_arrEquipmentItemList[3].isUseBox = true;
			_arrEquipmentItemList[3].itemNum = _player->getEquipment()[i];
		}
		else if ((_player->getEquipment()[i] % TYPE_EQUIPMENT) / (TYPE_HEAD - TYPE_EQUIPMENT) == 5)
		{

			_arrEquipmentItemList[4].isUseBox = true;
			_arrEquipmentItemList[4].itemNum = _player->getEquipment()[i];
		}
		else if ((_player->getEquipment()[i] % TYPE_EQUIPMENT) / (TYPE_HEAD - TYPE_EQUIPMENT) == 6)
		{

			_arrEquipmentItemList[5].isUseBox = true;
			_arrEquipmentItemList[5].itemNum = _player->getEquipment()[i];
		}
		else if ((_player->getEquipment()[i] % TYPE_EQUIPMENT) / (TYPE_HAND - TYPE_EQUIPMENT) == 7)
		{

			_arrEquipmentItemList[6].isUseBox = true;
			_arrEquipmentItemList[6].itemNum = _player->getEquipment()[i];
		}
		else if ((_player->getEquipment()[i] % TYPE_EQUIPMENT) / (TYPE_HEAD - TYPE_EQUIPMENT) == 8)
		{
			_arrEquipmentItemList[7].isUseBox = true;
			_arrEquipmentItemList[7].itemNum = _player->getEquipment()[i];
		}
		else if ((_player->getEquipment()[i] % TYPE_EQUIPMENT) / (TYPE_HEAD - TYPE_EQUIPMENT) == 9)
		{
			_arrEquipmentItemList[8].isUseBox = true;
			_arrEquipmentItemList[8].itemNum = _player->getEquipment()[i];
		}
		else if ((_player->getEquipment()[i] % TYPE_EQUIPMENT) / (TYPE_HEAD - TYPE_EQUIPMENT) == 10)
		{
			_arrEquipmentItemList[9].isUseBox = true;
			_arrEquipmentItemList[9].itemNum = _player->getEquipment()[i];
		}
		else if ((_player->getEquipment()[i] % TYPE_EQUIPMENT) / (TYPE_HEAD - TYPE_EQUIPMENT) == 11)
		{
			_arrEquipmentItemList[10].isUseBox = true;
			_arrEquipmentItemList[10].itemNum = _player->getEquipment()[i];
		}
		else if ((_player->getEquipment()[i] % TYPE_EQUIPMENT) / (TYPE_HEAD - TYPE_EQUIPMENT) == 12)
		{
			_arrEquipmentItemList[11].isUseBox = true;
			_arrEquipmentItemList[11].itemNum = _player->getEquipment()[i];
		}
		else if ((_player->getEquipment()[i] % TYPE_EQUIPMENT) / (TYPE_HEAD - TYPE_EQUIPMENT) == 13)
		{
			_arrEquipmentItemList[12].isUseBox = true;
			_arrEquipmentItemList[12].itemNum = _player->getEquipment()[i];
		}
	}
}

bool equipment::isDoubleClick()
{

	if (_isUse)
	{
		for (int i = 0; i < MAXEQUIPMENTITEM; ++i)
		{
			if (PtInRect(&_arrEquipmentItemList[i].boxRc, _ptMouse))
			{
				// 장비창에 장비가 있으면	
				if (_arrEquipmentItemList[i].isUseBox)
				{
					_player->removeEquipment(_arrEquipmentItemList[i].itemNum);
					updateEquipmentItem();
				}
			}
		}
	}

	return false;
}

bool equipment::isOnceClick()
{
	if (_isUse)
	{
		if (PtInRect(&_rc, _ptMouse))
		{
			return true;
		}
	}

	return false;
}