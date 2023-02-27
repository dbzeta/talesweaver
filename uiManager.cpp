#include "stdafx.h"
#include "UIManager.h"



uiManager::uiManager()
{
}


uiManager::~uiManager()
{

}

HRESULT uiManager::init()		   
{
	// ��ư ���� init
	setBtn();

	// â ���� init
	//setUi();


	return S_OK;
}

void uiManager::release()		   
{
	_statusInfomation->release();
	_quickSlot->release();

	for (int i = 0; i < _vUiScreen.size(); ++i)
	{
		_vUiScreen[i]->release();
	}
}

void uiManager::update()		   
{
	pushButton();

	_statusInfomation->update();
	_quickSlot->update();

	for (int i = 0; i < _vUiScreen.size(); ++i)
	{
		_vUiScreen[i]->update();
	}

	_storeScreen->update();
}

void uiManager::render()		   
{
	
	if (_isShow) 
	{
		_identityBtn.btnImage->render(getMemDC(), _identityBtn.rc.left, _identityBtn.rc.top);
		_comboBtn.btnImage->render(getMemDC(), _comboBtn.rc.left, _comboBtn.rc.top);
		_equipBtn.btnImage->render(getMemDC(), _equipBtn.rc.left, _equipBtn.rc.top);
		_inventoryBtn.btnImage->render(getMemDC(), _inventoryBtn.rc.left, _inventoryBtn.rc.top);
		_skillBtn.btnImage->render(getMemDC(), _skillBtn.rc.left, _skillBtn.rc.top);
		_questBtn.btnImage->render(getMemDC(), _questBtn.rc.left, _questBtn.rc.top);
		_menuBtn.btnImage->render(getMemDC(), _menuBtn.rc.left, _menuBtn.rc.top);
		_hideBtn.btnImage->render(getMemDC(), _hideBtn.rc.left, _hideBtn.rc.top);
	}
	else
	{
		_showBtn.btnImage->render(getMemDC(), _showBtn.rc.left, _showBtn.rc.top);
	}

	_statusInfomation->render();
	_quickSlot->render();

	for (int i = 0; i < _vUiScreen.size(); ++i)
	{
		_vUiScreen[i]->render();
	}

	

}

void uiManager::setUi()
{
	
	// �������� ��� â�� ���� �͵� �ƴϰ� �׻� ���̹Ƿ� ���Ϳ� �߰����� �ʰ� ������ ���
	_quickSlot = new quickSlot;
	_quickSlot->init();

	// ��������â ���� �ݾ��ִ� â�� �ƴϹǷ� ���� ����.
	_statusInfomation = new statusInfomation;
	_statusInfomation->init();
	_statusInfomation->setPlayerAddressLink(_player);
	_statusInfomation->setEmAddressLink(_em);

		
	_skill = new skillScreen;
	_skill->init();
	_vUiScreen.push_back(_skill);

	_inventory = new inventory;
	_inventory->init();
	_inventory->setImAddressLink(_im);
	_inventory->setPlayerAddressLink(_player);
	_vUiScreen.push_back(_inventory);

	_quest = new questScreen;
	_quest->init();
	_vUiScreen.push_back(_quest);

	_menu = new menu;
	_menu->init();
	_menu->setPlayerAddressLink(_player);
	_vUiScreen.push_back(_menu);

	_identity = new status;
	_identity->init();
	_identity->setPlayerAddressLink(_player);
	_vUiScreen.push_back(_identity);

	_equipment = new equipment;
	_equipment->init();
	_equipment->setPlayerAddressLink(_player);
	_equipment->setImAddressLink(_im);
	_vUiScreen.push_back(_equipment);

	_storeScreen = new storeScreen;
	_storeScreen->init();
	_storeScreen->setImAddressLink(_im);
	_storeScreen->setPlayerAddressLink(_player);
	_vUiScreen.push_back(_storeScreen);

	_combo = new combo;
	_combo->init();
	_combo->setPlayerAddressLink(_player);
	_vUiScreen.push_back(_combo);

}

void uiManager::setBtn()
{
	_identityBtn.btnImage = IMAGEMANAGER->addPngImage("ĳ����������ư", "UI\\ĳ����������ư.png", 30, 29, false, false);
	_identityBtn.rc = RectMake(WINSIZEX - _identityBtn.btnImage->getWidth(), 0, _identityBtn.btnImage->getWidth(), _identityBtn.btnImage->getHeight());
	_identityBtn.frameX = _identityBtn.frameY = 0;

	_comboBtn.btnImage = IMAGEMANAGER->findImage("�޺�â��ư");
	_comboBtn.rc = RectMake(WINSIZEX - _comboBtn.btnImage->getWidth(), _identityBtn.rc.bottom, _comboBtn.btnImage->getWidth(), _comboBtn.btnImage->getHeight());
	_comboBtn.frameX = _comboBtn.frameY = 0;

	_equipBtn.btnImage = IMAGEMANAGER->addPngImage("���â��ư", "UI\\���â��ư.png", 30, 29, false, false);
	_equipBtn.rc = RectMake(WINSIZEX - _equipBtn.btnImage->getWidth(), _comboBtn.rc.bottom, _equipBtn.btnImage->getWidth(), _equipBtn.btnImage->getHeight());
	_equipBtn.frameX = _equipBtn.frameY = 0;

	_inventoryBtn.btnImage = IMAGEMANAGER->addPngImage("�κ��丮��ư", "UI\\�κ��丮��ư.png", 30, 29, false, false);
	_inventoryBtn.rc = RectMake(WINSIZEX - _inventoryBtn.btnImage->getWidth(), _equipBtn.rc.bottom, _inventoryBtn.btnImage->getWidth(), _inventoryBtn.btnImage->getHeight());
	_inventoryBtn.frameX = _inventoryBtn.frameY = 0;

	_skillBtn.btnImage = IMAGEMANAGER->addPngImage("��ųâ��ư", "UI\\��ųâ��ư.png", 30, 29, false, false);
	_skillBtn.rc = RectMake(WINSIZEX - _skillBtn.btnImage->getWidth(), _inventoryBtn.rc.bottom, _skillBtn.btnImage->getWidth(), _skillBtn.btnImage->getHeight());
	_skillBtn.frameX = _skillBtn.frameY = 0;

	_questBtn.btnImage = IMAGEMANAGER->addPngImage("����Ʈâ��ư", "UI\\����Ʈâ.png", 30, 29, false, false);
	_questBtn.rc = RectMake(WINSIZEX - _questBtn.btnImage->getWidth(), _skillBtn.rc.bottom, _questBtn.btnImage->getWidth(), _questBtn.btnImage->getHeight());
	_questBtn.frameX = _questBtn.frameY = 0;

	_menuBtn.btnImage = IMAGEMANAGER->addPngImage("�޴�â��ư", "UI\\�޴�â��ư.png", 30, 29, false, false);
	_menuBtn.rc = RectMake(WINSIZEX - _menuBtn.btnImage->getWidth(), _questBtn.rc.bottom, _menuBtn.btnImage->getWidth(), _menuBtn.btnImage->getHeight());
	_menuBtn.frameX = _menuBtn.frameY = 0;

	_hideBtn.btnImage = IMAGEMANAGER->addPngImage("������ư", "UI\\������ư.png", 30, 18, false, false);
	_hideBtn.rc = RectMake(WINSIZEX - _hideBtn.btnImage->getWidth(), _menuBtn.rc.bottom, _hideBtn.btnImage->getWidth(), _hideBtn.btnImage->getHeight());
	_hideBtn.frameX = _hideBtn.frameY = 0;

	_showBtn.btnImage = IMAGEMANAGER->addPngImage("���̱��ư", "UI\\���̱��ư.png", 30, 18, false, false);
	_showBtn.rc = RectMake(WINSIZEX - _showBtn.btnImage->getWidth(), 0, _showBtn.btnImage->getWidth(), _showBtn.btnImage->getHeight());
	_showBtn.frameX = _showBtn.frameY = 0;

	_isShow = true;
}

void uiManager::pushButton()
{
	if (KEYMANAGER->isOnceKeyDown('P'))					// ĳ���� ���� â
	{
		_identity->changeIsUse();
		zOrder(_identity);
	}
	else if (KEYMANAGER->isOnceKeyDown('A'))			// �޺�â
	{
		_combo->changeIsUse();
		zOrder(_combo);
	}
	else if (KEYMANAGER->isOnceKeyDown('E'))			// ���â
	{
		_equipment->changeIsUse();
		zOrder(_equipment);
	}
	else if (KEYMANAGER->isOnceKeyDown('I'))			// �κ��丮
	{
		_inventory->changeIsUse();
		zOrder(_inventory);
		
	}
	else if (KEYMANAGER->isOnceKeyDown('S'))			// ��ųâ
	{
		_skill->changeIsUse();
		zOrder(_skill);
	}
	else if (KEYMANAGER->isOnceKeyDown('V'))			// ����Ʈ
	{
		_quest->changeIsUse();
		zOrder(_quest);
	}
	else if (KEYMANAGER->isOnceKeyDown('Q'))			// ������
	{
		_quickSlot->changeQuickSlot();
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))		// ESC
	{
		for (int i = _vUiScreen.size() - 1; i >= 0; --i)
		{
			// ���� �����ִ� â�� �ϳ��� �������� break���.
			if (_vUiScreen[i]->getIsUse())
			{
				_vUiScreen[i]->changeIsUse();
				return;
			}
		}

		_menu->changeIsUse();
		zOrder(_menu);

	}
}

bool uiManager::isDoubleClick()
{

	for (int i = 0; i < _vUiScreen.size(); ++i)
	{
		if (_vUiScreen[i]->isDoubleClick()) return true;
	}
	return false;
}

bool uiManager::isOnceClick()
{
	// ������ ui��ư ( ������ )
	if (_isShow)
	{
		// ĳ���� ����â ��ư
		if (PtInRect(&_identityBtn.rc, _ptMouse))
		{
			_identity->changeIsUse();
			zOrder(_identity);
			return true;
		}
		// �޺�â ��ư
		else if (PtInRect(&_comboBtn.rc, _ptMouse))
		{
			_combo->changeIsUse();
			zOrder(_equipment);
			return true;
		}
		// ���â ��ư
		else if (PtInRect(&_equipBtn.rc, _ptMouse))
		{
			_equipment->changeIsUse();
			zOrder(_equipment);
			return true;
		}
		// �κ��丮â ��ư
		else if (PtInRect(&_inventoryBtn.rc, _ptMouse))
		{
			_inventory->changeIsUse();
			zOrder(_inventory);
			return true;
		}
		// ��ųâ ��ư
		else if (PtInRect(&_skillBtn.rc, _ptMouse))
		{
			_skill->changeIsUse();
			zOrder(_skill);
			return true;
		}
		// ����Ʈâ ��ư
		else if (PtInRect(&_questBtn.rc, _ptMouse))
		{
			_quest->changeIsUse();
			zOrder(_quest);
			return true;
		}
		// �޴�â ��ư
		else if (PtInRect(&_menuBtn.rc, _ptMouse))
		{
			_menu->changeIsUse();
			zOrder(_menu);
			return true;
		}
		// ����� ��ư
		else if (PtInRect(&_hideBtn.rc, _ptMouse))
		{
			_isShow = false;
			return true;
		}
		
	}
	else
	{
		// ���̱� ��ư
		if (PtInRect(&_showBtn.rc, _ptMouse))
		{
			_isShow = true;
			return true;
		}
	}

	// ui â ���� Ŭ��
	for (int i = _vUiScreen.size() - 1; i >= 0; --i)
	{
		if (_vUiScreen[i]->isOnceClick())
		{
			zOrder(_vUiScreen[i]);
			return true;
		}
	}

	if (_statusInfomation->isOnceClick())
	{
		return true;
	}

	return false;

}

bool uiManager::isOnceClickUp()
{
	for (int i = _vUiScreen.size() - 1; i >= 0; --i)
	{
		if (_vUiScreen[i]->isOnceClickUp())
		{
			return true;
		}
	}

	return false;
}

bool uiManager::isStayClick()
{
	for (int i = 0; i < _vUiScreen.size(); ++i)
	{
		if (_vUiScreen[_vUiScreen.size() - 1]->isStayClick())
		{
			return true;
		}
	}

	return false;
}

void uiManager::zOrder(uiScreen* ui)
{
	for (int i = 0; i < _vUiScreen.size(); ++i)
	{
		if (ui == _vUiScreen[i])
		{
			uiScreen* tempUiScreen = _vUiScreen[i];
			_vUiScreen.erase(_vUiScreen.begin() + i);
			_vUiScreen.push_back(tempUiScreen);
			break;
		}
	}
}
