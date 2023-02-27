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
	// �������� ( ��ȭ�� )
	// npc �ѹ� ���� ( Ÿ�� + number )
	_npcNum = N_TYPE_MERCHANT + 1;
	_image = IMAGEMANAGER->addPngFrameImage("��������", "image\\���Ӿ�\\NPC�Ŵ���\\�������.png", 324, 208, 9, 4, false, false);
	_frameX = _frameY = 0;
	_count = 0;

	_state = N_STATE_STOP;

	// npc�� ��ǥ�� centerX bottomY�� �������� �Ѵ�.
	_rc = RectMakeCenter(0, 0, 0, 0);
	_cx = 0;
	_by = 0;

	// ��Ŀ�̿��� �ȿ� �ִ°�?
	_isFocusing = false;	
	
	// Ŭ���� �Ǿ��°�?
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

	// Ŭ����ó��
	if (!_isFocusing) return;
	
	// �̹��� ������ ���� ���
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

	// �÷��̾ �ٶ󺸴� ������ bottom center�� �Ѵ�.
	
	// npc�� �÷��̾�� �ؿ� ���� ���
	if (_rc.bottom > playerRC.bottom)
	{
		// npc�� �÷��̾�� �����ʿ� ���� ���
		if ((_rc.left + _rc.right) / 2 > (playerRC.left + playerRC.right) / 2)
		{
			_dir = N_DIR_LEFT_UP;
		}
		// npc�� �÷��̾�� ���ʿ� �������
		else 
		{
			_dir = N_DIR_RIGHT_UP;
		}
	}
	// npc�� �÷��̾�� ���� �������
	else
	{
		// npc�� �÷��̾�� �����ʿ� ���� ���
		if ((_rc.left + _rc.right) / 2 > (playerRC.left + playerRC.right) / 2)
		{
			_dir = N_DIR_LEFT_DOWN;
		}
		// npc�� �÷��̾�� ���ʿ� �������
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
	// ��ŷ�� rect�� ����� ( ���� ��ǥ�� ��ŷ�Ҷ� ��Ŀ�̵Ǵ� ��ǥ�� �����ֱ����� )
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
	// �Ǹ��ϴ� ������ ���

	// 201101 ������� 
	_vOwnedItemNum.push_back(201101);
	// 201102 ����÷� 
	_vOwnedItemNum.push_back(201102);

	// 201201 �׸���� 
	_vOwnedItemNum.push_back(201201);
	// 201202 Ű���÷� 
	_vOwnedItemNum.push_back(201202);

	// 201301 ���׹̳����� (��)
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
	// ī��ũ ( ������ )
	// npc �ѹ� ���� ( Ÿ�� + number )
	_npcNum = N_TYPE_MERCHANT + 2;
	_image = IMAGEMANAGER->addPngFrameImage("ī��ũ", "image\\���Ӿ�\\NPC�Ŵ���\\������.png", 704, 190, 11, 2, false, false);
	_frameX = _frameY = 0;
	_count = 0;

	_state = N_STATE_STOP;

	// npc�� ��ǥ�� centerX bottomY�� �������� �Ѵ�.
	_rc = RectMakeCenter(0, 0, 0, 0);
	_cx = 0;
	_by = 0;

	// ��Ŀ�̿��� �ȿ� �ִ°�?
	_isFocusing = false;

	// Ŭ���� �Ǿ��°�?
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

	// Ŭ����ó��
	if (!_isFocusing) return;

	// �̹��� ������ ���� ���
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

	// �÷��̾ �ٶ󺸴� ������ bottom center�� �Ѵ�.

	// npc�� �÷��̾�� �ؿ� ���� ���
	if (_rc.bottom > playerRC.bottom)
	{
		// npc�� �÷��̾�� �����ʿ� ���� ���
		if ((_rc.left + _rc.right) / 2 > (playerRC.left + playerRC.right) / 2)
		{
			_dir = N_DIR_LEFT_UP;
		}
		// npc�� �÷��̾�� ���ʿ� �������
		else
		{
			_dir = N_DIR_RIGHT_UP;
		}
	}
	// npc�� �÷��̾�� ���� �������
	else
	{
		// npc�� �÷��̾�� �����ʿ� ���� ���
		if ((_rc.left + _rc.right) / 2 > (playerRC.left + playerRC.right) / 2)
		{
			_dir = N_DIR_LEFT_DOWN;
		}
		// npc�� �÷��̾�� ���ʿ� �������
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
	// ��ŷ�� rect�� ����� ( ���� ��ǥ�� ��ŷ�Ҷ� ��Ŀ�̵Ǵ� ��ǥ�� �����ֱ����� )
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
	// �Ǹ��ϴ� ������ ���

	// 102101 ������	
	_vOwnedItemNum.push_back(102101);
	// 103201 Ÿ��
	_vOwnedItemNum.push_back(103201);
	// 104101 ��Ŭ��
	_vOwnedItemNum.push_back(104101);
	// 104201 ��ӹ��
	_vOwnedItemNum.push_back(104201);
	// 105101 ���� �������� �����
	_vOwnedItemNum.push_back(105101);
	// 106101 ���� ���� ���ڷ�
	_vOwnedItemNum.push_back(106101);


}

void kanakeu::showItemList()
{
	if (_um->getStoreScreen()->getIsUse()) return;
	_um->getStoreScreen()->setSelliingItemList(_vOwnedItemNum);
	_um->getStoreScreen()->setIsUse(true);
}