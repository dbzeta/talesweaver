#include "stdafx.h"
#include "poisonJellyppi.h"
#include "player.h"
#include "mapManager.h"

poisonJellyppi::poisonJellyppi()
{
}


poisonJellyppi::~poisonJellyppi()
{
}

HRESULT poisonJellyppi::init()
{

	_image = IMAGEMANAGER->addPngFrameImage("������������_MOVE", "image\\enemy\\������������_�̵�.png", 180, 176, 5, 4, false, false);
	IMAGEMANAGER->addPngFrameImage("������������_ATTACK", "image\\enemy\\������������_����.png", 648, 176, 18, 4, false, false);
	IMAGEMANAGER->addPngFrameImage("������������_COLLISOON", "image\\enemy\\������������_�浹.png", 108, 176, 3, 4, false, false);


	return S_OK;
}

void poisonJellyppi::release()
{

}

void poisonJellyppi::update()
{
	// Ŭ���� ó�� ��Ŀ������ ��� ������ �������� �ʴ´�.
	RECT temp;
	if (!IntersectRect(&temp, &_rc, &_focus)) return;

	if (!_isLive)
	{
		++_reSpawnCount;

		if (_reSpawnCount % 1000 == 0)
		{
			_isLive = true;
			_reSpawnCount = 0;
			setMinion(500, 500);
		}
	}
	else
	{

		move();
		attack();
		setImage();


		// �̹��� �������� �����ش�.
		if (++_count % 10 == 0)
		{
			_frameX++;
			if (_frameX > _image->getMaxFrameX()) _frameX = 0;
		}

		_rc = RectMakeCenter(_cx, _by - _image->getFrameHeight() / 2, _image->getFrameWidth(), _image->getFrameHeight());

	}
}

void poisonJellyppi::render()
{

	// Ŭ���� ó�� ��Ŀ������ ��� ������ �������� �ʴ´�.
	RECT temp;
	if (!IntersectRect(&temp, &_rc, &_focus)) return;

	DRAWMANAGER->addDrawList(DRAW_FRAMERENDER, "ENEMY", _image, _frameX, _frameY, _rc, 0);
}

void poisonJellyppi::attack()
{
	if (_isAttack)
	{
		_state = E_ATTACK;
		if (_frameX >= _image->getMaxFrameX())
		{
			if (_count % 10 == 0) _player->addDamage(_atk);
			if (_by < _target.y)
			{
				if (getDistance(_cx, _by, _player->getX(), _player->getY()) >= 65)
				{
					_state = E_MOVE;
					_frameX = 0;
					_isAttack = false;
					_isMove = true;
				}
			}
			else
			{
				if (getDistance(_cx, _by, _player->getX(), _player->getY()) >= 50)
				{
					_state = E_MOVE;
					_frameX = 0;
					_isAttack = false;
					_isMove = true;
				}
			}
		}
	}
}

void poisonJellyppi::move()
{
	if (_isTarget)
	{
		if (!_isAttack) _isMove = true;

		// �������� ���� Ÿ�� �ε����� ���� ���� ����
		int currentTileX, currentTileY = 0;
		// �÷��̾��� Ÿ�� Ž��
		int playerTileX, playerTileY = 0;

		// ���� Ÿ���� ��ŷ�� �Ǵ����� Ȯ���� �� �ε����� �����´�
		if (_mm->isPickTile(_cx, _by, true))
		{
			// �������� ���� Ÿ�ϰ� �÷��̾��� Ÿ�ϰ��� �˾Ƴ��� �������� �÷��̾��� ��ǥ�� Ÿ������ ���Ѵ�.
			currentTileX = _mm->getTargetTileX();
			currentTileY = _mm->getTargetTileY();
			playerTileX = _mm->getCurrentTileX();
			playerTileY = _mm->getCurrentTileY();

			_mm->getAstar()->setTile(currentTileX, currentTileY, playerTileX, playerTileY);
			_vPath = _mm->getAstar()->pathFinder(_mm->getAstar()->getCurrentTile());

			_target = _mm->getTile(_vPath[_vPath.size() - 1])->center;

			_angle = getAngle(_cx, _by, _mm->getTile(_vPath[_vPath.size() - 1])->center.x,
				_mm->getTile(_vPath[_vPath.size() - 1])->center.y);
			checkDirection(_angle);

			_vPath.clear();

		}
	}
	else
	{
		if (!_isMove)
		{
			++_changeDirectionCount;
			if (_changeDirectionCount % 500 == 0)
			{
				_changeDirectionCount = 0;
				// ���������� ������ ���� �� �� ���⿡ ���� Ÿ���ε����� ���� �ִ����� Ȯ�� �� ���� ������ �� Ÿ����
				// ������ǥ�� ���� �̵� �ƴ϶�� �������ִ´�.

				// �������� ���� Ÿ�� �ε����� ���� ���� ����
				int currentTileX = 0;
				int currentTileY = 0;

				// ���� Ÿ���� ��ŷ�� �Ǵ����� Ȯ���� �� �ε����� �����´�
				if (_mm->isPickTile(_cx, _by, false))
				{


					currentTileX = _mm->getTargetTileX();
					currentTileY = _mm->getTargetTileY();

					// �ֺ� Ÿ���� �˻��� �� �� Ÿ���� ���� �ִ� Ÿ������ �˻�
					for (int i = -1; i < 2; ++i)
					{
						for (int k = -1; k < 2; ++k)
						{
							// ����ó��
							if (currentTileX + k < 0 || currentTileX + k > _mm->getTileX() - 1) continue;
							if (currentTileY + i < 0 || currentTileY + i > _mm->getTileY() - 1) continue;
							if (i == 0 && k == 0) continue;

							if (_mm->getTile((currentTileY + i) * _mm->getTileX() + currentTileX + k)->obj == OBJ_NONE)
							{
								_vPath.push_back((currentTileY + i) * _mm->getTileX() + currentTileX + k);
							}

						}
					}

					if (_vPath.size() > 0)
					{
						int path = _vPath[RND->getFromIntTo(0, _vPath.size() - 1)];
						_vPath.clear();

						_target = _mm->getTile(path)->center;

						_angle = getAngle(_cx, _by, _target.x, _target.y);
						checkDirection(_angle);
						_isMove = true;
					}
					else
						_isMove = false;
				}
				else _isMove = false;
			}
		}
	}

	if (_isMove)
	{
		_cx += cosf(_angle) * TIMEMANAGER->getElapsedTime() * 80;
		_by += -sinf(_angle) * TIMEMANAGER->getElapsedTime() * 80;

		if (_isTarget)
		{
			if (getDistance(_cx, _by, _player->getX(), _player->getY()) <= 65)
			{
				_isAttack = true;
				_isMove = false;
				_frameX = 0;
			}
		}
		else
		{
			if (getDistance(_cx, _by, _target.x, _target.y) <= 100)
			{
				_isMove = false;
				_changeDirectionCount = 0;
			}
		}


	}


}


void poisonJellyppi::checkDirection(float angle)
{

	// RIGHT
	if ((0 <= angle &&  angle < PI2 / 16) || (15 * (PI2 / 16) <= angle && angle < PI2))
	{
		_dir = E_DIR_RIGHT;
		_frameY = 1;
	}
	// RIGHT UP
	else if (PI2 / 16 <= angle &&  angle < 3 * (PI2 / 16))
	{
		_dir = E_DIR_RIGHT_UP;
		_frameY = 3;
	}
	// UP
	else if (3 * (PI2 / 16) <= angle &&  angle < 5 * (PI2 / 16))
	{
		_dir = E_DIR_UP;
		_frameY = 3;
	}
	// LEFT UP
	else if (5 * (PI2 / 16) <= angle &&  angle < 7 * (PI2 / 16))
	{
		_dir = E_DIR_LEFT_UP;
		_frameY = 2;
	}
	// LEFT
	else if (7 * (PI2 / 16) <= angle &&  angle < 9 * (PI2 / 16))
	{
		_dir = E_DIR_LEFT;
		_frameY = 0;
	}
	// LEFT DOWN
	else if (9 * (PI2 / 16) <= angle &&  angle < 11 * (PI2 / 16))
	{
		_dir = E_DIR_LEFT_DOWN;
		_frameY = 0;
	}
	// DOWN
	else if (11 * (PI2 / 16) <= angle &&  angle < 13 * (PI2 / 16))
	{
		_dir = E_DIR_DOWN;
		_frameY = 1;
	}
	// RIGHT DOWN
	else if (13 * (PI2 / 16) <= angle &&  angle < 15 * (PI2 / 16))
	{
		_dir = E_DIR_RIGHT_DOWN;
		_frameY = 1;
	}
}

void poisonJellyppi::setMinion(int cx, int by)
{
	_cx = cx;
	_by = by;

	_dir = E_DIR_RIGHT_DOWN;
	_state = E_MOVE;

	_frameX = _frameY = 0;

	_enemyNum = 1;

	_range = 2;

	_isTarget = false;
	_isMove = false;
	_isAttack = false;
	_isLive = true;

	_reSpawnCount = 0;

	_currentHp = _maxHp = 500;
	_currentMp = _maxMp = 50;

	_atk = 50;
	_phisicalDefense = _magicDefense = 10;

	_rc = RectMakeCenter(_cx, _by - _image->getFrameHeight() / 2, _image->getFrameWidth(), _image->getFrameHeight());
}

void poisonJellyppi::setImage()
{
	switch (_state)
	{
	case E_MOVE:
		_image = IMAGEMANAGER->findImage("������������_MOVE");
		break;
	case E_ATTACK:
		_image = IMAGEMANAGER->findImage("������������_ATTACK");
		break;
	case E_COLLISION:
		_image = IMAGEMANAGER->findImage("������������_COLLISION");
		break;
	default:
		break;
	}
}

void poisonJellyppi::addDamage(int damage)
{
	if (damage < (_phisicalDefense + _magicDefense)) return;
	_currentHp -= (damage - (_phisicalDefense + _magicDefense));
	_isTarget = true;
	if (_currentHp <= 0) _isLive = false;
}

bool poisonJellyppi::isOnceClick()
{

	RECT pickingRc = RectMake(_rc.left - _focus.left, _rc.top - _focus.top, _image->getFrameWidth(), _image->getFrameHeight());

	// �����߸� �� �����ٸ�
	if (PtInRect(&pickingRc, _ptMouse))
	{
		return true;
	}

	return false;
}
