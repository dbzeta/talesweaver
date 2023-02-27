#include "stdafx.h"
#include "normalNpc.h"


maria::maria()
{
}


maria::~maria()
{
}

HRESULT maria::init()
{
	// ������ ( ����Ʈ )
	// npc �ѹ� ���� ( Ÿ�� + number )
	_npcNum = N_TYPE_NORMAL + 1;
	_image = IMAGEMANAGER->addPngFrameImage("������", "image\\���Ӿ�\\NPC�Ŵ���\\����Ʈnpc.png", 364, 344, 7, 4, false, false);
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

	return S_OK;
}

void maria::release()
{
}

void maria::update()
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
	else if (_state == N_STATE_IDLE) if (++_count % 15 == 0) _frameX++;

	DRAWMANAGER->addDrawList(DRAW_FRAMERENDER,"NPC", _image, _frameX, _frameY, _rc, 0);
}

void maria::render()
{
	if (!_isFocusing) return;

	if (_debug) Rectangle(getMemDC(), _rc.left - _focus.left, _rc.top - _focus.top, _rc.left + _image->getFrameWidth() - _focus.left, _rc.top + _image->getFrameHeight() - _focus.top);
	// _image->frameRender(getMemDC(), _rc.left - _focus.left, _rc.top - _focus.top, _frameX, _frameY);

}

void maria::changeDirection(RECT playerRC)
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
}

void maria::setNpc(int cx, int by)
{
	_cx = cx;
	_by = by;
	_rc = RectMakeCenter(_cx, _by - _image->getFrameHeight() / 2, _image->getFrameWidth(), _image->getFrameHeight());
}

bool maria::isOnceClick()
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
