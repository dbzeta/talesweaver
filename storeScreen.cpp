#include "stdafx.h"
#include "storeScreen.h"
#include "itemManager.h"
#include "player.h"

storeScreen::storeScreen()
{
}


storeScreen::~storeScreen()
{
}



HRESULT storeScreen::init()
{
	_background = IMAGEMANAGER->addPngImage("����â", "UI\\����â\\����â.png", 400, 423, false, false);
	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, _background->getWidth(), _background->getHeight());

	_isUse = false;
	_isSetItem = false;

	_paymentMoney = 0;

	setBtn();

	return S_OK;
}

void storeScreen::release()
{

}

void storeScreen::update()
{
	if (!_isUse)
	{
		while(_vSellingItemList.size() > 0)
		{
			_vSellingItemList.erase(_vSellingItemList.begin());
			_vStoreItem.erase(_vStoreItem.begin());
			_isSetItem = false;
			_paymentMoney = 0;
		}

		return;
	}

	for (int i = 0; i < _vTabButton.size(); ++i)
	{
		if (_vTabButton[i]->isClick)
		{
			swap(_vTabButton[i], _vTabButton[_vTabButton.size() - 1]);
		}
	}

	if (_vSellingItemList.size() > 0 && !_isSetItem)
	{
		setItem();
	}


}

void storeScreen::render()
{
	if (!_isUse) return;

	// ����â
	_background->render(getMemDC(), _rc.left, _rc.top);

	// ��ư
	for (int i = 0; i < _vTabButton.size(); ++i)
	{
		_vTabButton[i]->btnImage->frameRender(getMemDC(), _vTabButton[i]->rc.left, _vTabButton[i]->rc.top, _vTabButton[i]->frameX, _vTabButton[i]->frameY);
	}

	_closeBtn.btnImage->frameRender(getMemDC(), _closeBtn.rc.left, _closeBtn.rc.top, _closeBtn.frameX, _closeBtn.frameY);

	// ���� ��ư�� ������ ���� �� 
	if (_purchaseBtn->isClick)
	{
		// NPC�� �Ǹ��ϴ� ���� ����
		for (int i = 0; i < _vStoreItem.size(); ++i)
		{
			// Rectangle(getMemDC(), _vStoreItem[i].pickingRc.left, _vStoreItem[i].pickingRc.top, _vStoreItem[i].pickingRc.right, _vStoreItem[i].pickingRc.bottom);

			_vStoreItem[i].itemIconImage->render(getMemDC(), _vStoreItem[i].imageRc.left, _vStoreItem[i].imageRc.top);
			char str[128];
			sprintf_s(str, "%s", _vStoreItem[i].itemName);
			TextOut(getMemDC(), _vStoreItem[i].imageRc.left + 100, _vStoreItem[i].imageRc.top + 2, str, strlen(str));
			sprintf_s(str, "%d", _vStoreItem[i].cost);
			TextOut(getMemDC(), _vStoreItem[i].imageRc.left + 300, _vStoreItem[i].imageRc.top + 2, str, strlen(str));
		
		}
	}

	// �÷��̾ �����ִ� MONEY ����
	char str[128];
	sprintf_s(str, "%10d", _player->getMoney());
	TextOut(getMemDC(), _rc.left + 100, _rc.bottom - 47, str, strlen(str));
	// ���� �ݾ� ����
	sprintf_s(str, "%10d", _paymentMoney);
	TextOut(getMemDC(), _rc.left + 100, _rc.bottom - 24, str, strlen(str));
	
	// Rectangle(getMemDC(), _buyBtn.rc.left, _buyBtn.rc.top, _buyBtn.rc.right, _buyBtn.rc.bottom);

}

void storeScreen::setBtn()
{
	// ���Թ�ư
	_purchaseBtn = new tagTabButton;
	_purchaseBtn->btnImage = IMAGEMANAGER->addPngFrameImage("����â���Թ�ư", "UI\\����â\\���Թ�ư.png", 38, 70, 2, 1, false, false);
	_purchaseBtn->frameX = 1;
	_purchaseBtn->frameY = 0;
	_purchaseBtn->isClick = true;
	_purchaseBtn->rc = RectMake(_rc.left, _rc.top + 30, _purchaseBtn->btnImage->getFrameWidth(), _purchaseBtn->btnImage->getFrameHeight());
	
	// �ǸŹ�ư
	_saleBtn = new tagTabButton;
	_saleBtn->btnImage = IMAGEMANAGER->addPngFrameImage("����â�ǸŹ�ư", "UI\\����â\\�ǸŹ�ư.png", 38, 70, 2, 1, false, false);	
	_saleBtn->frameX = _saleBtn->frameY = 0;
	_saleBtn->isClick = false;
	_saleBtn->rc = RectMake(_rc.left, _purchaseBtn->rc.bottom - 4, _saleBtn->btnImage->getFrameWidth(), _saleBtn->btnImage->getFrameHeight());
	
	_vTabButton.push_back(_purchaseBtn);
	_vTabButton.push_back(_saleBtn);
	
	// �������ư
	_closeBtn.btnImage = IMAGEMANAGER->addPngFrameImage("����â�������ư", "UI\\����â\\�������ư.png", 84, 17, 2, 1, false, false);
	_closeBtn.frameX = _closeBtn.frameY = 0;
	_closeBtn.rc = RectMake(_rc.right - 54, _rc.top + 5, _closeBtn.btnImage->getFrameWidth(),_closeBtn.btnImage->getFrameHeight());

	_buyBtn.btnImage;
	_buyBtn.frameX = _buyBtn.frameY = 0;
	_buyBtn.rc = RectMake(_rc.right - 54, _rc.bottom - 26, 42, 20);

}

void storeScreen::setItem()
{
	for (int i = 0; i < _vSellingItemList.size(); ++i)
	{
		tagStoreItem item;
		item.itemIconImage = IMAGEMANAGER->findImage(_im->getItem(_vSellingItemList[i])->getIconImageName());
		item.imageRc = RectMakeCenter(_rc.left + 42, _rc.top + 65 + (25 * i), item.itemIconImage->getWidth(), item.itemIconImage->getHeight());
		item.pickingRc = RectMakeCenter((_rc.left + _rc.right) / 2, _rc.top + 66 + (25 * i), _background->getWidth() - 60, 18);
		strcpy(item.itemName, _im->getItem(_vSellingItemList[i])->getItemName());
		item.cost = _im->getItem(_vSellingItemList[i])->getCost();

		_vStoreItem.push_back(item);

	}

	_isSetItem = true;

}

bool storeScreen::isDoubleClick()
{
	// ���� Ŭ��
	if (_vSellingItemList.size() > 0)
	{
		for (int i = 0; i < _vSellingItemList.size(); ++i)
		{
			if (PtInRect(&_vStoreItem[i].pickingRc, _ptMouse))
			{
				if ((_paymentMoney + _vStoreItem[i].cost) > _player->getMoney()) return true;
				_paymentMoney += _vStoreItem[i].cost;
				_vBuyingItemList.push_back(_vSellingItemList[i]);
				return true;
			}
		}
	}
	return false;
}

bool storeScreen::isOnceClick()
{
	if (!_isUse) return false;

	// ���� ��ư
	if (PtInRect(&_purchaseBtn->rc, _ptMouse))
	{
		_purchaseBtn->isClick = true;
		_purchaseBtn->frameX = 1;
		_saleBtn->isClick = !_purchaseBtn->isClick;
		_saleBtn->frameX = !_purchaseBtn->frameX; 
		return true;
	}
	// �Ǹ� ��ư
	else if (PtInRect(&_saleBtn->rc, _ptMouse))
	{
		_saleBtn->isClick = true;
		_saleBtn->frameX = 1;
		_purchaseBtn->isClick = !_saleBtn->isClick;
		_purchaseBtn->frameX = !_saleBtn->frameX;	
		return true;
	}
	// ����
	else if (PtInRect(&_buyBtn.rc, _ptMouse))
	{
		_player->addMoney(-_paymentMoney);
		_paymentMoney = 0;
		while (_vBuyingItemList.size() > 0)
		{
			_player->addInventory(*_vBuyingItemList.begin());
			_vBuyingItemList.erase(_vBuyingItemList.begin());
		}
		SOUNDMANAGER->play("ȿ��������â���Ǳ���", _soundEffectVolume);
		return true;
	}
	// x ��ư
	else if (PtInRect(&_closeBtn.rc, _ptMouse))
	{
		_closeBtn.frameX = 1;
		return true;
	}
	
	else if (PtInRect(&_rc, _ptMouse))
	{
		return true;
	}

	return false;
}

bool storeScreen::isOnceClickUp()
{
	if (!_isUse) return false;

	if (PtInRect(&_closeBtn.rc, _ptMouse))
	{
		_closeBtn.frameX = 0;
		_isUse = false;
		return true;
	}

	return false;
}

