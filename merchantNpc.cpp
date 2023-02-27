#include "stdafx.h"
#include "merchantNpc.h"
#include "uiManager.h"

wanderingCat::wanderingCat()
{
}

wanderingCat::~wanderingCat()
{
}

HRESULT wanderingCat::init()
{
	// 방랑고양이 ( 잡화점 )
	// npc 넘버 설정 ( 타입 + number )
	_npcNum = N_TYPE_MERCHANT + 1;
	_image = IMAGEMANAGER->addPngFrameImage("방랑고양이", "image\\게임씬\\NPC매니저\\방랑상인.png", 324, 208, 9, 4, false, false);
	_frameX = _frameY = 0;
	_count = 0;

	_state = N_STATE_STOP;

	// npc의 좌표는 centerX bottomY를 기준으로 한다.
	_rc = RectMakeCenter(0, 0, 0, 0);
	_cx = 0;
	_by = 0;

	// 포커싱영역 안에 있는가?
	_isFocusing = false;	
	
	// 클릭이 되었는가?
	_isClick = false;

	setItem();

	return S_OK;
}

void wanderingCat::release()
{
}

void wanderingCat::update()
{
	RECT temp;
	if (IntersectRect(&temp, &_focus, &_rc)) _isFocusing = true;
	else _isFocusing = false;

	// 클리핑처리
	if (!_isFocusing) return;
	
	// 이미지 돌리기 위한 기능
	if (_frameX > _image->getMaxFrameX()) _state = N_STATE_STOP;
	
	if (_state == N_STATE_STOP)
	{
		_frameX = 0;

		if (++_count % 700 == 0)
		{
			_state = N_STATE_IDLE;
			_count = 0;
		}
	}
	else if (_state == N_STATE_IDLE) if (++_count % 30 == 0) _frameX++;
	


	DRAWMANAGER->addDrawList(DRAW_FRAMERENDER,"NPC", _image, _frameX, _frameY, _rc, 0);

}

void wanderingCat::render()
{
	if (!_isFocusing) return;
	
	if (_debug) Rectangle(getMemDC(), _rc.left - _focus.left, _rc.top - _focus.top, _rc.left + _image->getFrameWidth() - _focus.left, _rc.top + _image->getFrameHeight() - _focus.top);
	// _image->frameRender(getMemDC(), _rc.left - _focus.left, _rc.top - _focus.top, _frameX, _frameY);

}

void wanderingCat::changeDirection(RECT playerRC)
{
	if (!_isFocusing) return;

	// 플레이어를 바라보는 기준을 bottom center로 한다.
	
	// npc가 플레이어보다 밑에 있을 경우
	if (_rc.bottom > playerRC.bottom)
	{
		// npc가 플레이어보다 오른쪽에 있을 경우
		if ((_rc.left + _rc.right) / 2 > (playerRC.left + playerRC.right) / 2)
		{
			_dir = N_DIR_LEFT_UP;
		}
		// npc가 플레이어보다 왼쪽에 있을경우
		else 
		{
			_dir = N_DIR_RIGHT_UP;
		}
	}
	// npc가 플레이어보다 위에 있을경우
	else
	{
		// npc가 플레이어보다 오른쪽에 있을 경우
		if ((_rc.left + _rc.right) / 2 > (playerRC.left + playerRC.right) / 2)
		{
			_dir = N_DIR_LEFT_DOWN;
		}
		// npc가 플레이어보다 왼쪽에 있을경우
		else
		{
			_dir = N_DIR_RIGHT_DOWN;
		}
	}

	switch (_dir)
	{
	case N_DIR_LEFT_DOWN:
		_frameY = 0;
		break;
	case N_DIR_LEFT_UP:
		_frameY = 1;
		break;
	case N_DIR_RIGHT_UP:
		_frameY = 2;
		break;
	case N_DIR_RIGHT_DOWN:
		_frameY = 3;
		break;
	default:
		break;
	}

	showItemList();
}

void wanderingCat::setNpc(int cx, int by)
{
	_cx = cx;
	_by = by;
	_rc = RectMakeCenter(_cx, _by - _image->getFrameHeight() / 2, _image->getFrameWidth(), _image->getFrameHeight());
}

bool wanderingCat::isOnceClick()
{
	// 피킹용 rect를 만든다 ( 실제 좌표와 피킹할때 포커싱되는 좌표를 맞춰주기위해 )
	RECT pickingRc = RectMake(_rc.left - _focus.left, _rc.top - _focus.top, _image->getFrameWidth(), _image->getFrameHeight());

	if (PtInRect(&pickingRc, _ptMouse))
	{
		_isClick = true;
		return true;
	}

	return false;
}

void wanderingCat::setItem()
{
	// 판매하는 아이템 목록

	// 201101 레드허브 
	_vOwnedItemNum.push_back(201101);
	// 201102 딸기시럽 
	_vOwnedItemNum.push_back(201102);

	// 201201 그린허브 
	_vOwnedItemNum.push_back(201201);
	// 201202 키위시럽 
	_vOwnedItemNum.push_back(201202);

	// 201301 스테미너포션 (소)
	_vOwnedItemNum.push_back(201301);

}

void wanderingCat::showItemList()
{
	if (_um->getStoreScreen()->getIsUse()) return;
	_um->getStoreScreen()->setSelliingItemList(_vOwnedItemNum);
	_um->getStoreScreen()->setIsUse(true);
}

kanakeu::kanakeu()
{
}

kanakeu::~kanakeu()
{
}

HRESULT kanakeu::init()
{
	// 카나크 ( 무기점 )
	// npc 넘버 설정 ( 타입 + number )
	_npcNum = N_TYPE_MERCHANT + 2;
	_image = IMAGEMANAGER->addPngFrameImage("카나크", "image\\게임씬\\NPC매니저\\장비상인.png", 704, 190, 11, 2, false, false);
	_frameX = _frameY = 0;
	_count = 0;

	_state = N_STATE_STOP;

	// npc의 좌표는 centerX bottomY를 기준으로 한다.
	_rc = RectMakeCenter(0, 0, 0, 0);
	_cx = 0;
	_by = 0;

	// 포커싱영역 안에 있는가?
	_isFocusing = false;

	// 클릭이 되었는가?
	_isClick = false;

	setItem();

	return S_OK;
}

void kanakeu::release()
{
}

void kanakeu::update()
{
	RECT temp;
	if (IntersectRect(&temp, &_focus, &_rc)) _isFocusing = true;
	else _isFocusing = false;

	// 클리핑처리
	if (!_isFocusing) return;

	// 이미지 돌리기 위한 기능
	if (_frameX > _image->getMaxFrameX()) _state = N_STATE_STOP;

	if (_state == N_STATE_STOP)
	{
		_frameX = 0;

		if (++_count % 700 == 0)
		{
			_state = N_STATE_IDLE;
			_count = 0;
		}
	}
	else if (_state == N_STATE_IDLE) if (++_count % 30 == 0) _frameX++;

	DRAWMANAGER->addDrawList(DRAW_FRAMERENDER,"NPC", _image, _frameX, _frameY, _rc, 0);
}

void kanakeu::render()
{
	if (!_isFocusing) return;

	if (_debug) Rectangle(getMemDC(), _rc.left - _focus.left, _rc.top - _focus.top, _rc.left + _image->getFrameWidth() - _focus.left, _rc.top + _image->getFrameHeight() - _focus.top);
	// _image->frameRender(getMemDC(), _rc.left - _focus.left, _rc.top - _focus.top, _frameX, _frameY);


}

void kanakeu::changeDirection(RECT playerRC)
{
	if (!_isFocusing) return;

	// 플레이어를 바라보는 기준을 bottom center로 한다.

	// npc가 플레이어보다 밑에 있을 경우
	if (_rc.bottom > playerRC.bottom)
	{
		// npc가 플레이어보다 오른쪽에 있을 경우
		if ((_rc.left + _rc.right) / 2 > (playerRC.left + playerRC.right) / 2)
		{
			_dir = N_DIR_LEFT_UP;
		}
		// npc가 플레이어보다 왼쪽에 있을경우
		else
		{
			_dir = N_DIR_RIGHT_UP;
		}
	}
	// npc가 플레이어보다 위에 있을경우
	else
	{
		// npc가 플레이어보다 오른쪽에 있을 경우
		if ((_rc.left + _rc.right) / 2 > (playerRC.left + playerRC.right) / 2)
		{
			_dir = N_DIR_LEFT_DOWN;
		}
		// npc가 플레이어보다 왼쪽에 있을경우
		else
		{
			_dir = N_DIR_RIGHT_DOWN;
		}
	}

	switch (_dir)
	{
	case N_DIR_LEFT_DOWN:
	case N_DIR_LEFT_UP:
		_frameY = 0;
	break;
	case N_DIR_RIGHT_UP:
	case N_DIR_RIGHT_DOWN:
		_frameY = 1;
	break;
	default:
	break;
	}

	showItemList();

}

void kanakeu::setNpc(int cx, int by)
{
	_cx = cx;
	_by = by;
	_rc = RectMakeCenter(_cx, _by - _image->getFrameHeight() / 2, _image->getFrameWidth(), _image->getFrameHeight());
}

bool kanakeu::isOnceClick()
{
	// 피킹용 rect를 만든다 ( 실제 좌표와 피킹할때 포커싱되는 좌표를 맞춰주기위해 )
	RECT pickingRc = RectMake(_rc.left - _focus.left, _rc.top - _focus.top, _image->getFrameWidth(), _image->getFrameHeight());

	if (PtInRect(&pickingRc, _ptMouse))
	{
		_isClick = true;
		return true;
	}
	return false;
}

void kanakeu::setItem()
{
	// 판매하는 아이템 목록

	// 102101 본메일	
	_vOwnedItemNum.push_back(102101);
	// 103201 타도
	_vOwnedItemNum.push_back(103201);
	// 104101 버클러
	_vOwnedItemNum.push_back(104101);
	// 104201 고속밴드
	_vOwnedItemNum.push_back(104201);
	// 105101 수습 마법사의 목걸이
	_vOwnedItemNum.push_back(105101);
	// 106101 나무 마법 빗자루
	_vOwnedItemNum.push_back(106101);


}

void kanakeu::showItemList()
{
	if (_um->getStoreScreen()->getIsUse()) return;
	_um->getStoreScreen()->setSelliingItemList(_vOwnedItemNum);
	_um->getStoreScreen()->setIsUse(true);
}