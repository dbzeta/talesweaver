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
	// 버튼 관련 init
	setBtn();

	// 창 관련 init
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
	
	// 퀵슬롯의 경우 창을 닫을 것도 아니고 항상 보이므로 벡터에 추가하지 않고 별개로 사용
	_quickSlot = new quickSlot;
	_quickSlot->init();

	// 상태정보창 또한 닫아주는 창이 아니므로 따로 구분.
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
	_identityBtn.btnImage = IMAGEMANAGER->addPngImage("캐릭터정보버튼", "UI\\캐릭터정보버튼.png", 30, 29, false, false);
	_identityBtn.rc = RectMake(WINSIZEX - _identityBtn.btnImage->getWidth(), 0, _identityBtn.btnImage->getWidth(), _identityBtn.btnImage->getHeight());
	_identityBtn.frameX = _identityBtn.frameY = 0;

	_comboBtn.btnImage = IMAGEMANAGER->findImage("콤보창버튼");
	_comboBtn.rc = RectMake(WINSIZEX - _comboBtn.btnImage->getWidth(), _identityBtn.rc.bottom, _comboBtn.btnImage->getWidth(), _comboBtn.btnImage->getHeight());
	_comboBtn.frameX = _comboBtn.frameY = 0;

	_equipBtn.btnImage = IMAGEMANAGER->addPngImage("장비창버튼", "UI\\장비창버튼.png", 30, 29, false, false);
	_equipBtn.rc = RectMake(WINSIZEX - _equipBtn.btnImage->getWidth(), _comboBtn.rc.bottom, _equipBtn.btnImage->getWidth(), _equipBtn.btnImage->getHeight());
	_equipBtn.frameX = _equipBtn.frameY = 0;

	_inventoryBtn.btnImage = IMAGEMANAGER->addPngImage("인벤토리버튼", "UI\\인벤토리버튼.png", 30, 29, false, false);
	_inventoryBtn.rc = RectMake(WINSIZEX - _inventoryBtn.btnImage->getWidth(), _equipBtn.rc.bottom, _inventoryBtn.btnImage->getWidth(), _inventoryBtn.btnImage->getHeight());
	_inventoryBtn.frameX = _inventoryBtn.frameY = 0;

	_skillBtn.btnImage = IMAGEMANAGER->addPngImage("스킬창버튼", "UI\\스킬창버튼.png", 30, 29, false, false);
	_skillBtn.rc = RectMake(WINSIZEX - _skillBtn.btnImage->getWidth(), _inventoryBtn.rc.bottom, _skillBtn.btnImage->getWidth(), _skillBtn.btnImage->getHeight());
	_skillBtn.frameX = _skillBtn.frameY = 0;

	_questBtn.btnImage = IMAGEMANAGER->addPngImage("퀘스트창버튼", "UI\\퀘스트창.png", 30, 29, false, false);
	_questBtn.rc = RectMake(WINSIZEX - _questBtn.btnImage->getWidth(), _skillBtn.rc.bottom, _questBtn.btnImage->getWidth(), _questBtn.btnImage->getHeight());
	_questBtn.frameX = _questBtn.frameY = 0;

	_menuBtn.btnImage = IMAGEMANAGER->addPngImage("메뉴창버튼", "UI\\메뉴창버튼.png", 30, 29, false, false);
	_menuBtn.rc = RectMake(WINSIZEX - _menuBtn.btnImage->getWidth(), _questBtn.rc.bottom, _menuBtn.btnImage->getWidth(), _menuBtn.btnImage->getHeight());
	_menuBtn.frameX = _menuBtn.frameY = 0;

	_hideBtn.btnImage = IMAGEMANAGER->addPngImage("숨기기버튼", "UI\\숨기기버튼.png", 30, 18, false, false);
	_hideBtn.rc = RectMake(WINSIZEX - _hideBtn.btnImage->getWidth(), _menuBtn.rc.bottom, _hideBtn.btnImage->getWidth(), _hideBtn.btnImage->getHeight());
	_hideBtn.frameX = _hideBtn.frameY = 0;

	_showBtn.btnImage = IMAGEMANAGER->addPngImage("보이기버튼", "UI\\보이기버튼.png", 30, 18, false, false);
	_showBtn.rc = RectMake(WINSIZEX - _showBtn.btnImage->getWidth(), 0, _showBtn.btnImage->getWidth(), _showBtn.btnImage->getHeight());
	_showBtn.frameX = _showBtn.frameY = 0;

	_isShow = true;
}

void uiManager::pushButton()
{
	if (KEYMANAGER->isOnceKeyDown('P'))					// 캐릭터 정보 창
	{
		_identity->changeIsUse();
		zOrder(_identity);
	}
	else if (KEYMANAGER->isOnceKeyDown('A'))			// 콤보창
	{
		_combo->changeIsUse();
		zOrder(_combo);
	}
	else if (KEYMANAGER->isOnceKeyDown('E'))			// 장비창
	{
		_equipment->changeIsUse();
		zOrder(_equipment);
	}
	else if (KEYMANAGER->isOnceKeyDown('I'))			// 인벤토리
	{
		_inventory->changeIsUse();
		zOrder(_inventory);
		
	}
	else if (KEYMANAGER->isOnceKeyDown('S'))			// 스킬창
	{
		_skill->changeIsUse();
		zOrder(_skill);
	}
	else if (KEYMANAGER->isOnceKeyDown('V'))			// 퀘스트
	{
		_quest->changeIsUse();
		zOrder(_quest);
	}
	else if (KEYMANAGER->isOnceKeyDown('Q'))			// 퀵슬롯
	{
		_quickSlot->changeQuickSlot();
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))		// ESC
	{
		for (int i = _vUiScreen.size() - 1; i >= 0; --i)
		{
			// 현재 열려있는 창을 하나씩 끄기위해 break사용.
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
	// 오른쪽 ui버튼 ( 아이콘 )
	if (_isShow)
	{
		// 캐릭터 정보창 버튼
		if (PtInRect(&_identityBtn.rc, _ptMouse))
		{
			_identity->changeIsUse();
			zOrder(_identity);
			return true;
		}
		// 콤보창 버튼
		else if (PtInRect(&_comboBtn.rc, _ptMouse))
		{
			_combo->changeIsUse();
			zOrder(_equipment);
			return true;
		}
		// 장비창 버튼
		else if (PtInRect(&_equipBtn.rc, _ptMouse))
		{
			_equipment->changeIsUse();
			zOrder(_equipment);
			return true;
		}
		// 인벤토리창 버튼
		else if (PtInRect(&_inventoryBtn.rc, _ptMouse))
		{
			_inventory->changeIsUse();
			zOrder(_inventory);
			return true;
		}
		// 스킬창 버튼
		else if (PtInRect(&_skillBtn.rc, _ptMouse))
		{
			_skill->changeIsUse();
			zOrder(_skill);
			return true;
		}
		// 퀘스트창 버튼
		else if (PtInRect(&_questBtn.rc, _ptMouse))
		{
			_quest->changeIsUse();
			zOrder(_quest);
			return true;
		}
		// 메뉴창 버튼
		else if (PtInRect(&_menuBtn.rc, _ptMouse))
		{
			_menu->changeIsUse();
			zOrder(_menu);
			return true;
		}
		// 숨기기 버튼
		else if (PtInRect(&_hideBtn.rc, _ptMouse))
		{
			_isShow = false;
			return true;
		}
		
	}
	else
	{
		// 보이기 버튼
		if (PtInRect(&_showBtn.rc, _ptMouse))
		{
			_isShow = true;
			return true;
		}
	}

	// ui 창 관련 클릭
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
