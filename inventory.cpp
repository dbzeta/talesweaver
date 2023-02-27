#include "stdafx.h"
#include "inventory.h"
#include "player.h"
#include "itemManager.h"

inventory::inventory()
{
}


inventory::~inventory()
{
}

HRESULT inventory::init()
{
	_background = IMAGEMANAGER->addPngImage("인벤토리창", "UI\\인벤토리창\\인벤토리창.png", 338, 443, false, false);
	_rc = RectMake(WINSIZEX - _background->getWidth() - 30, 100, _background->getWidth(), _background->getHeight());

	IMAGEMANAGER->addPngImage("아이템선택", "UI\\인벤토리창\\아이템선택.png", 30, 30, false, false);

	_isUse = false;

	setBtn();

	for (int i = 0; i < MAXINVENTORYBOX; ++i)
	{
		_arrInventoryItemList[i].boxRc = RectMake((_rc.left + 26) + (i % 8) * 35, (_rc.top + 82) + (i / 8) * 35, 30, 30);
		_arrInventoryItemList[i].boxNum = i;
	}

	IMAGEMANAGER->addImage("select", 30, 30)->getMemDC();

	_currentBoxNum = -1; // 피킹이 안되어있을 때 
	_isPickingItem = false;
	return S_OK;
}
void inventory::release()
{

}

void inventory::update()
{
	if (_isUse)
	{
		if (_dragBar.isPicking)
		{
			int moveY = (_divisionY - _ptMouse.y);

			_dragBar.rc.top = _tempDragBarRc.top - moveY;;
			_dragBar.rc.bottom = _tempDragBarRc.bottom - moveY;

			if (_dragBar.rc.top <= _upBtn.rc.bottom)
			{
				_dragBar.rc.top = _upBtn.rc.bottom + 1;
				_dragBar.rc.bottom = _dragBar.rc.top + _dragBar.btnImage->getHeight();
			}
			if (_dragBar.rc.bottom >= _downBtn.rc.top)
			{
				_dragBar.rc.top = _downBtn.rc.top - 1 - _dragBar.btnImage->getHeight();
				_dragBar.rc.bottom = _downBtn.rc.top - 1;
			}

		}

		checkPicking();

	}
}

void inventory::render()
{
	if (_isUse)
	{
		// 인벤토리 창
		_background->render(getMemDC(),_rc.left,_rc.top);

		// 장비 분류 버튼
		_totalBtn->btnImage->frameRender(getMemDC(), _totalBtn->rc.left, _totalBtn->rc.top, _totalBtn->frameX, _totalBtn->frameY);
		_equipBtn->btnImage->frameRender(getMemDC(), _equipBtn->rc.left, _equipBtn->rc.top, _equipBtn->frameX, _equipBtn->frameY);
		_consumBtn->btnImage->frameRender(getMemDC(), _consumBtn->rc.left, _consumBtn->rc.top, _consumBtn->frameX, _consumBtn->frameY);
		_etcBtn->btnImage->frameRender(getMemDC(), _etcBtn->rc.left, _etcBtn->rc.top, _etcBtn->frameX, _etcBtn->frameY);
		_eventBtn->btnImage->frameRender(getMemDC(), _eventBtn->rc.left, _eventBtn->rc.top, _eventBtn->frameX, _eventBtn->frameY);

		// 기타 버튼
		_upBtn.btnImage->frameRender(getMemDC(), _upBtn.rc.left, _upBtn.rc.top, _upBtn.frameX, _upBtn.frameY);
		_downBtn.btnImage->frameRender(getMemDC(), _downBtn.rc.left, _downBtn.rc.top, _downBtn.frameX, _downBtn.frameY);
		_exitBtn.btnImage->frameRender(getMemDC(), _exitBtn.rc.left, _exitBtn.rc.top, _exitBtn.frameX, _exitBtn.frameY);
				
		// 드래그바 
		_dragBar.btnImage->render(getMemDC(), _dragBar.rc.left, _dragBar.rc.top);

		if (_currentBoxNum != -1 && !_isPickingItem)
		{
			IMAGEMANAGER->findImage("아이템선택")->render(getMemDC(), _arrInventoryItemList[_currentBoxNum].boxRc.left, _arrInventoryItemList[_currentBoxNum].boxRc.top);
			
		}
		// 아이템 목록
		for (int i = 0; i < MAXINVENTORYBOX; ++i)
		{
			// 사용중인 칸만 출력
			if (_arrInventoryItemList[i].isUseBox)
			{
				// Rectangle(getMemDC(), _arrInventoryItemList[i].boxRc.left, _arrInventoryItemList[i].boxRc.top, _arrInventoryItemList[i].boxRc.right, _arrInventoryItemList[i].boxRc.bottom);
				
				int centerX = (_arrInventoryItemList[i].boxRc.left + _arrInventoryItemList[i].boxRc.right) / 2;
				int centerY = (_arrInventoryItemList[i].boxRc.top + _arrInventoryItemList[i].boxRc.bottom) / 2;
				image* tempImage = IMAGEMANAGER->findImage(_im->getItem(_arrInventoryItemList[i].itemNum)->getIconImageName());
				tempImage->render(getMemDC(), centerX - tempImage->getWidth() / 2, centerY - tempImage->getHeight() / 2);
				char str[128];
				sprintf_s(str, "%3d", _arrInventoryItemList[i].itemEA);
				TextOut(getMemDC(), centerX - 1, centerY, str, strlen(str));
			}

			char str[128];
			sprintf_s(str, "%10d", _player->getMoney());
			TextOut(getMemDC(), _rc.right - 90, _rc.bottom - 70, str, strlen(str));
			
		}

		// 아이템 드래그 시 랜더
		if (_currentBoxNum != -1 && _isPickingItem)
		{
			image* tempImage = IMAGEMANAGER->findImage(_im->getItem(_arrInventoryItemList[_currentBoxNum].itemNum)->getIconImageName());

			tempImage->render(getMemDC(), _ptMouse.x - tempImage->getWidth()/ 2, _ptMouse.y - tempImage->getHeight() /2);

		}

	}
}


bool inventory::isDoubleClick()
{
	if (_isUse)
	{

		for (int i = 0; i < MAXINVENTORYBOX; ++i)
		{
			if (PtInRect(&_arrInventoryItemList[i].boxRc, _ptMouse))
			{
				// 아이템이 있는 칸을 눌렀을 때
				if (_arrInventoryItemList[i].isUseBox)
				{
					// 장비템일 때
					if (_arrInventoryItemList[i].itemNum / TYPE_EQUIPMENT == 1)
					{
						_arrInventoryItemList[i].itemEA = 0;
						_player->addEquipment(_arrInventoryItemList[i].itemNum);
						_arrInventoryItemList[i].isUseBox = false;
						_arrInventoryItemList[i].itemNum = 0;
					}
					// 소비템일 때
					else if (_arrInventoryItemList[i].itemNum / TYPE_EQUIPMENT == 2)
					{

						if (_arrInventoryItemList[i].itemNum / TYPE_HP == 1)
						{
							_player->addHp(_im->getItem(_arrInventoryItemList[i].itemNum)->getConsumptionItem()._hp);
						
							for (int i = 0; i < _player->getInventory().size(); ++i)
							{
								if (_player->getInventory()[i] == _arrInventoryItemList[i].itemNum)
								{
									_player->getInventory().erase(_player->getInventory().begin() + i);
								}
							}
						}
						else if (_arrInventoryItemList[i].itemNum / TYPE_MP == 1)
						{
							_player->addMp(_im->getItem(_arrInventoryItemList[i].itemNum)->getConsumptionItem()._mp);
							for (int i = 0; i < _player->getInventory().size(); ++i)
							{
								if (_player->getInventory()[i] == _arrInventoryItemList[i].itemNum)
								{
									_player->getInventory().erase(_player->getInventory().begin() + i);
								}
							}
						}
						else if (_arrInventoryItemList[i].itemNum / TYPE_SP == 1)
						{
							_player->addSp(_im->getItem(_arrInventoryItemList[i].itemNum)->getConsumptionItem()._sp);
							for (int i = 0; i < _player->getInventory().size(); ++i)
							{
								if (_player->getInventory()[i] == _arrInventoryItemList[i].itemNum)
								{
									_player->getInventory().erase(_player->getInventory().begin() + i);
								}
							}
						}

						_arrInventoryItemList[i].itemEA--;
						if (_arrInventoryItemList[i].itemEA <= 0)
						{
							_arrInventoryItemList[i].isUseBox = false;
							_arrInventoryItemList[i].itemNum = 0;
						}
					}
					return true;
				}
			}
		}


	}


	return false;
}

bool inventory::isOnceClick()
{
	if (_isUse)
	{

		// 현재 마우스 좌표 및 _rc 값
		_divisionX = _ptMouse.x;
		_divisionY = _ptMouse.y;
		_tempRc = { _rc.left, _rc.top, _rc.right, _rc.bottom };
		_tempDragBarRc = { _dragBar.rc.left, _dragBar.rc.top, _dragBar.rc.right,_dragBar.rc.bottom };

		
		for (int i = 0; i < MAXINVENTORYBOX; ++i)
		{
			if (PtInRect(&_arrInventoryItemList[i].boxRc, _ptMouse))
			{
				
				if (_currentBoxNum == i)
				{
					_isPickingItem = true;
				}
				else if (_currentBoxNum != i)
				{
					_currentBoxNum = i;
					if(_arrInventoryItemList[i].isUseBox) _isPickingItem = true;
					else _isPickingItem = false;
				}
				return true;
			}
		}

		// 장비 선택
		if (PtInRect(&_totalBtn->rc, _ptMouse))
		{
			_isPickingItem = false;

			setIsPicking(_totalBtn);
			return true;
		}
		else if (PtInRect(&_equipBtn->rc, _ptMouse))
		{
			_isPickingItem = false;

			setIsPicking(_equipBtn);

			return true;
		}
		else if (PtInRect(&_consumBtn->rc, _ptMouse))
		{
			_isPickingItem = false;

			setIsPicking(_consumBtn);

			return true;
		}
		else if (PtInRect(&_etcBtn->rc, _ptMouse))
		{
			_isPickingItem = false;

			setIsPicking(_etcBtn);

			return true;
		}
		else if (PtInRect(&_eventBtn->rc, _ptMouse))
		{
			_isPickingItem = false;

			setIsPicking(_eventBtn);

			return true;
		}
		// 기타 버튼 ( 종료 ) 나머지 기타버튼은 STAY로 조정
		else if (PtInRect(&_exitBtn.rc, _ptMouse))
		{
			_isPickingItem = false;

			_exitBtn.frameX = 2;
			_isUse = false;
			return true;
		}
		// 창 선택
		else if (PtInRect(&_rc, _ptMouse))
		{
			_isPickingItem = false;
			return true;
		}
	}

	return false;
}

bool inventory::isStayClick()
{
	if (_isUse)
	{
		if (_isPickingItem)
		{	
			
			return true;
		}

		if (PtInRect(&_upBtn.rc, _ptMouse) && !_dragBar.isPicking)
		{
			_upBtn.frameX = 2;
			return true;
		}
		else if (PtInRect(&_downBtn.rc, _ptMouse) && !_dragBar.isPicking)
		{
			_downBtn.frameX = 2;
			return true;
		}
		else if (PtInRect(&_dragBar.rc, _ptMouse))
		{
			_dragBar.isPicking = true;
			return true;
		}
		else if (PtInRect(&_rc, _ptMouse))
		{
			if (_dragBar.isPicking) return true;
			if (_isPickingItem) return true;

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

			// 현재 창 기준으로 rc값을 새로 맞추어준다.
			_totalBtn->rc = RectMake(_rc.left + 23, _rc.top + 44, _totalBtn->btnImage->getFrameWidth(), _totalBtn->btnImage->getFrameHeight());
			_equipBtn->rc = RectMake(_rc.left + 79, _rc.top + 44, _equipBtn->btnImage->getFrameWidth(), _equipBtn->btnImage->getFrameHeight());
			_consumBtn->rc = RectMake(_equipBtn->rc.right, _rc.top + 44, _consumBtn->btnImage->getFrameWidth(), _consumBtn->btnImage->getFrameHeight());
			_etcBtn->rc = RectMake(_consumBtn->rc.right, _rc.top + 44, _etcBtn->btnImage->getFrameWidth(), _etcBtn->btnImage->getFrameHeight());


			// 기타 버튼 위치 재설정
			_upBtn.rc = RectMake(_rc.right - 32, _rc.top + 77, _upBtn.btnImage->getFrameWidth(), _upBtn.btnImage->getFrameHeight());
			_downBtn.rc = RectMake(_rc.right - 32, _rc.bottom - 94, _downBtn.btnImage->getFrameWidth(), _downBtn.btnImage->getFrameHeight());
			_exitBtn.rc = RectMake(_rc.right - 24, _rc.top + 6, _exitBtn.btnImage->getFrameWidth(), _exitBtn.btnImage->getFrameHeight());
			_dragBar.rc = RectMake(_rc.right - 31, _rc.top + 90, _dragBar.btnImage->getWidth(), _dragBar.btnImage->getHeight());
			_eventBtn->rc = RectMake(_etcBtn->rc.right, _rc.top + 44, _eventBtn->btnImage->getFrameWidth(), _eventBtn->btnImage->getFrameHeight());

			for (int i = 0; i < MAXINVENTORYBOX; ++i)
			{
				_arrInventoryItemList[i].boxRc = RectMake((_rc.left + 26) + (i % 8) * 35, (_rc.top + 82) + (i / 8) * 35, 30, 30);
			}

			return true;
		}
	}

	return false;
}

bool inventory::isOnceClickUp()
{
	if (_isUse)
	{
		if (_isPickingItem)
		{
			for (int i = 0; i < MAXINVENTORYBOX; ++i)
			{
				if (PtInRect(&_arrInventoryItemList[i].boxRc, _ptMouse))
				{
					if (i == _currentBoxNum) continue;

					tagInventoryItem tempItem = _arrInventoryItemList[_currentBoxNum];
					_arrInventoryItemList[_currentBoxNum] = _arrInventoryItemList[i];
					_arrInventoryItemList[i] = tempItem;
					_isPickingItem = false;
					_arrInventoryItemList[i].boxRc = RectMake((_rc.left + 26) + (i % 8) * 35, (_rc.top + 82) + (i / 8) * 35, 30, 30);
					_arrInventoryItemList[_currentBoxNum].boxRc = RectMake((_rc.left + 26) + (_currentBoxNum % 8) * 35, (_rc.top + 82) + (_currentBoxNum / 8) * 35, 30, 30);
					_currentBoxNum = i;
					return true;
				}
				else
				{
					_isPickingItem = false;
					_arrInventoryItemList[_currentBoxNum].boxRc = RectMake((_rc.left + 26) + (_currentBoxNum % 8) * 35, (_rc.top + 82) + (_currentBoxNum / 8) * 35, 30, 30);
				}
			}
		}

		if (_dragBar.isPicking)
		{
			_dragBar.isPicking = false;
			return true;
		}
	}

	return false;
}

void inventory::checkPicking()
{	
	// 장비 종류 선택
	for (int i = 0; i < _vTotalInventoryList.size(); ++i)
	{
		if (_vTotalInventoryList[i]->isPicking) _vTotalInventoryList[i]->frameX = 2;
		else if (PtInRect(&_vTotalInventoryList[i]->rc, _ptMouse)) _vTotalInventoryList[i]->frameX = 1;
		else _vTotalInventoryList[i]->frameX = 0;
	}

	// 기타 버튼 
	if (PtInRect(&_upBtn.rc, _ptMouse) && !_dragBar.isPicking)
	{
		_upBtn.frameX = 1;
		_downBtn.frameX = 0;
		_exitBtn.frameX = 0;
	}
	else if (PtInRect(&_downBtn.rc, _ptMouse) && !_dragBar.isPicking)
	{
		_upBtn.frameX = 0;
		_downBtn.frameX = 1;
		_exitBtn.frameX = 0;
	}
	else if (PtInRect(&_exitBtn.rc, _ptMouse) && !_dragBar.isPicking)
	{
		_upBtn.frameX = 0;
		_downBtn.frameX = 0;
		_exitBtn.frameX = 1;
	}
	else
	{
		_upBtn.frameX = 0;
		_downBtn.frameX = 0;
		_exitBtn.frameX = 0;
	}

}

void inventory::setBtn()
{
	// 장비 종류 선택 버튼
	_totalBtn = new tagInventoryButton;
	_totalBtn->btnImage = IMAGEMANAGER->addPngFrameImage("인벤토리창전체버튼", "UI\\인벤토리창\\전체버튼.png", 153, 23, 3, 1, false, false);
	_totalBtn->frameX =	_totalBtn->frameY = 0;
	_totalBtn->rc = RectMake(_rc.left + 23, _rc.top + 44, _totalBtn->btnImage->getFrameWidth(), _totalBtn->btnImage->getFrameHeight());
	_totalBtn->isPicking = true;

	_equipBtn = new tagInventoryButton; 
	_equipBtn->btnImage = IMAGEMANAGER->addPngFrameImage("인벤토리창장비버튼", "UI\\인벤토리창\\장비버튼.png", 150, 23, 3, 1, false, false);
	_equipBtn->frameX = _equipBtn->frameY = 0;
	_equipBtn->rc = RectMake(_rc.left + 79, _rc.top + 44, _equipBtn->btnImage->getFrameWidth(), _equipBtn->btnImage->getFrameHeight());

	_consumBtn = new tagInventoryButton; 
	_consumBtn->btnImage = IMAGEMANAGER->addPngFrameImage("인벤토리창소모품버튼", "UI\\인벤토리창\\소모품버튼.png", 153, 23, 3, 1, false, false);
	_consumBtn->frameX = _consumBtn->frameY = 0;
	_consumBtn->rc = RectMake(_equipBtn->rc.right, _rc.top + 44, _consumBtn->btnImage->getFrameWidth(), _consumBtn->btnImage->getFrameHeight());

	_etcBtn = new tagInventoryButton; 
	_etcBtn->btnImage = IMAGEMANAGER->addPngFrameImage("인벤토리창기타버튼", "UI\\인벤토리창\\기타버튼.png", 153, 23, 3, 1, false, false);
	_etcBtn->frameX = _etcBtn->frameY = 0;
	_etcBtn->rc = RectMake(_consumBtn->rc.right, _rc.top + 44, _etcBtn->btnImage->getFrameWidth(), _etcBtn->btnImage->getFrameHeight());

	_eventBtn = new tagInventoryButton; 
	_eventBtn->btnImage = IMAGEMANAGER->addPngFrameImage("인벤토리창이벤트버튼", "UI\\인벤토리창\\이벤트버튼.png", 150, 23, 3, 1, false, false);
	_eventBtn->frameX = _eventBtn->frameY = 0;
	_eventBtn->rc = RectMake(_etcBtn->rc.right, _rc.top + 44, _eventBtn->btnImage->getFrameWidth(), _eventBtn->btnImage->getFrameHeight());

	_vTotalInventoryList.push_back(_totalBtn);
	_vTotalInventoryList.push_back(_equipBtn);
	_vTotalInventoryList.push_back(_consumBtn);
	_vTotalInventoryList.push_back(_etcBtn);
	_vTotalInventoryList.push_back(_eventBtn);

	// 기타 버튼
	_upBtn.btnImage = IMAGEMANAGER->addPngFrameImage("인벤토리창UP버튼","UI\\인벤토리창\\UP버튼.png",33,11,3,1,false,false);
	_upBtn.frameX = _upBtn.frameY = 0;
	_upBtn.rc = RectMake(_rc.right - 32, _rc.top + 77, _upBtn.btnImage->getFrameWidth(), _upBtn.btnImage->getFrameHeight());
	_downBtn.btnImage = IMAGEMANAGER->addPngFrameImage("인벤토리창DOWN버튼", "UI\\인벤토리창\\DOWN버튼.png", 33, 11, 3, 1, false, false);
	_downBtn.frameX = _downBtn.frameY = 0;
	_downBtn.rc = RectMake(_rc.right - 32, _rc.bottom - 94, _downBtn.btnImage->getFrameWidth(), _downBtn.btnImage->getFrameHeight());
	_exitBtn.btnImage = IMAGEMANAGER->addPngFrameImage("인벤토리창종료버튼", "UI\\인벤토리창\\종료버튼.png", 42, 14, 3, 1, false, false);
	_exitBtn.frameX = _exitBtn.frameY = 0;
	_exitBtn.rc = RectMake(_rc.right - 24, _rc.top + 6, _exitBtn.btnImage->getFrameWidth(), _exitBtn.btnImage->getFrameHeight());

	// 드래그바
	_dragBar.btnImage = IMAGEMANAGER->addPngImage("인벤토리창드래그바", "UI\\인벤토리창\\드래그바.png", 9, 64, false, false);
	_dragBar.rc = RectMake(_rc.right - 31, _rc.top + 90, _dragBar.btnImage->getWidth(), _dragBar.btnImage->getHeight());
}




void inventory::setIsPicking(tagInventoryButton* pickingBtn)
{

	// 전체, 장비, 소모품 등 현재 클릭되어있는 종류를 알기위한 함수
	for (int i = 0; i < _vTotalInventoryList.size(); ++i)
	{
		if (pickingBtn == _vTotalInventoryList[i])
		{
			_vTotalInventoryList[i]->isPicking = true;
		}
		else
		{
			_vTotalInventoryList[i]->isPicking = false;
		}
	}
}

void inventory::addInventoryItem(int itemNum)
{
	bool isConsumptionItem = false;			// 소모품인가

	// 중복확인
	for (int i = 0; i < MAXINVENTORYBOX; ++i)
	{
		if (_arrInventoryItemList[i].itemNum == itemNum)
		{
			// 장비인지 소모품인지 구분
			// 소모품
			if (itemNum / TYPE_EQUIPMENT == 2)
			{
				isConsumptionItem = true;
				_arrInventoryItemList[i].itemEA++;
			}

		}
	}
	// 소모품이 아니면 새로 추가
	if (!isConsumptionItem)
	{
		// 빈칸이 중간에 있는가?
		for (int i = 0; i < MAXINVENTORYBOX; ++i)
		{
			if (_arrInventoryItemList[i].isUseBox == false)
			{
				_arrInventoryItemList[i].itemNum = itemNum;
				_arrInventoryItemList[i].isUseBox = true;
				_arrInventoryItemList[i].itemEA = 1;
				break;
			}
		}
	}

}
