#include "stdafx.h"
#include "mapManager.h"
#include "player.h"


mapManager::mapManager()
{
}


mapManager::~mapManager()
{
}

HRESULT mapManager::init()				
{
	_tileX, _tileY = 0;
	_focus = RectMake(0, 0, WINSIZEX, WINSIZEY);
	
	_currentBgm = "�ʵ�_��";
	SOUNDMANAGER->play(_currentBgm, _bgmVolume);
	_currentMap = MAP_TUTORIAL01;
	changeMap(_currentMap);

	_width = _vIsoTiles[0]->width;
	_height = _vIsoTiles[0]->height;

	_currentTileX = _currentTileY = 0;
	_targetTileX = _targetTileY = 0;

	_ast = new aStarTest;
	_ast->init(_tileX, _tileY);

	for (int y = 0; y < _tileY; ++y)
	{
		for (int x = 0; x < _tileX; ++x)
		{
			bool isWall = false;

			if (_vIsoTiles[_tileX * y + x]->obj != OBJ_NONE) isWall = true;
			else isWall = false;

			_ast->setTile(x,y, isWall);
		}
	}

	int a = 0;
	return S_OK;
}

void mapManager::release()				
{

}

void mapManager::update()				
{
	for (int i = 0; i < _vIsoTiles.size(); ++i)
	{
		image* objImage = NULL;

		if (_vIsoTiles[i]->obj == OBJ_WALL) objImage = IMAGEMANAGER->findImage("�⺻������Ʈ");
		else if (_vIsoTiles[i]->obj == OBJ_FLAG) objImage = IMAGEMANAGER->findImage("�⺻������Ʈ2");
		else if (_vIsoTiles[i]->obj == OBJ_NONE) continue;
		RECT objRect = RectMake(_vIsoTiles[i]->rc.left, _vIsoTiles[i]->rc.top - objImage->getFrameHeight() + IMAGEMANAGER->findImage("�⺻Ÿ��")->getFrameHeight(),
			objImage->getFrameWidth(), objImage->getFrameHeight());

		DRAWMANAGER->addDrawList(DRAW_FRAMERENDER, "OBJECT", objImage, _vIsoTiles[i]->objFrameX, _vIsoTiles[i]->objFrameY, objRect, 0);
	}
}

void mapManager::render()				
{
	for (int i = 0; i < _vIsoTiles.size(); ++i)
	{
		// Ŭ���� ����� ����Ͽ� ȭ�鿡 �Ⱥ��̴� �ֵ��� ������ �����ش�
		RECT temp;
		// ��Ŀ���� rect�� Ÿ���� rect�� ���Ͽ� �����ϴ� �κ��� ������� continue�� �Ѱ��־� ������ �����ش�.
		if (!IntersectRect(&temp, &_focus, &_vIsoTiles[i]->rc)) continue;

		// ȭ�鿡 �������� Ÿ���� ���� ��ǥ�� �����̰� �߰��� ��Ŀ�� ��ǥ�� ���� ��������.
		if (_vIsoTiles[i]->terrain == TR_NONE || _debug)
		{
			LineMake(getMemDC(), _vIsoTiles[i]->center.x - _focus.left, _vIsoTiles[i]->center.y - _focus.top - _vIsoTiles[i]->height / 2,
				_vIsoTiles[i]->center.x - _vIsoTiles[i]->width / 2 - _focus.left, _vIsoTiles[i]->center.y - _focus.top);
			LineMake(getMemDC(), _vIsoTiles[i]->center.x - _focus.left, _vIsoTiles[i]->center.y - _focus.top - _vIsoTiles[i]->height / 2,
				_vIsoTiles[i]->center.x + _vIsoTiles[i]->width / 2 - _focus.left, _vIsoTiles[i]->center.y - _focus.top);
			LineMake(getMemDC(), _vIsoTiles[i]->center.x - _vIsoTiles[i]->width / 2 - _focus.left, _vIsoTiles[i]->center.y - _focus.top,
				_vIsoTiles[i]->center.x - _focus.left, _vIsoTiles[i]->center.y + _vIsoTiles[i]->height / 2 - _focus.top);
			LineMake(getMemDC(), _vIsoTiles[i]->center.x + _vIsoTiles[i]->width / 2 - _focus.left, _vIsoTiles[i]->center.y - _focus.top,
				_vIsoTiles[i]->center.x - _focus.left, _vIsoTiles[i]->center.y + _vIsoTiles[i]->height / 2 - _focus.top);
		}
		else
		{
			IMAGEMANAGER->findImage("�⺻Ÿ��")->frameRender(getMemDC(), _vIsoTiles[i]->rc.left - _focus.left, _vIsoTiles[i]->rc.top - _focus.top, _vIsoTiles[i]->terrainFrameX, _vIsoTiles[i]->terrainFrameY);
		}

		if (_debug)
		{
			// Rectangle(getMemDC(), _vIsoTiles[i]->rc.left, _vIsoTiles[i]->rc.top, _vIsoTiles[i]->rc.right, _vIsoTiles[i]->rc.bottom);
		}

	}

	// ������Ʈ
	for (int i = 0; i < _vIsoTiles.size(); ++i)
	{
	// 	// Ŭ���� ����� ����Ͽ� ȭ�鿡 �Ⱥ��̴� �ֵ��� ���� ����
	// 	RECT temp;
	// 
		image* objImage;
	
		if (_vIsoTiles[i]->obj == OBJ_WALL) objImage = IMAGEMANAGER->findImage("�⺻������Ʈ");
		else if (_vIsoTiles[i]->obj == OBJ_FLAG) objImage = IMAGEMANAGER->findImage("�⺻������Ʈ2");
		else if (_vIsoTiles[i]->obj == OBJ_NONE) continue;
	
	RECT objRect = RectMake(_vIsoTiles[i]->rc.left, _vIsoTiles[i]->rc.top - objImage->getFrameHeight() + IMAGEMANAGER->findImage("�⺻Ÿ��")->getFrameHeight(),
	 		objImage->getFrameWidth(), objImage->getFrameHeight());
	// 
	// 	if (!IntersectRect(&temp, &_focus, &objRect)) continue;
	// 
	// 	if (_vIsoTiles[i]->obj == OBJ_WALL)
	// 	{
	// 		objImage->frameRender(getMemDC(), objRect.left - _focus.left,
	// 			objRect.top - _focus.top,
	// 			_vIsoTiles[i]->objFrameX, _vIsoTiles[i]->objFrameY);
	// 	}
	// 	else if (_vIsoTiles[i]->obj == OBJ_FLAG)
	// 	{
	// 		objImage->frameRender(getMemDC(), _vIsoTiles[i]->rc.left - _focus.left, _vIsoTiles[i]->rc.top - _focus.top,
	// 			_vIsoTiles[i]->objFrameX, _vIsoTiles[i]->objFrameY);
	// 	}
	if (_debug)
		{
		Rectangle(getMemDC(), objRect.left - _focus.left, objRect.top - _focus.top, objRect.right - _focus.left, objRect.bottom - _focus.top);
		}
	 }
}

void mapManager::load(string mapName)
{

	HANDLE file;
	DWORD read;

	string temp = mapName + ".map";

	file = CreateFile(temp.c_str(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	while (_vIsoTiles.size())
	{
		// �ҷ����� �� �ҷ����� ������ �����µ� ������ ����??
		SAFE_DELETE(_vIsoTiles[0]);
		_vIsoTiles.erase(_vIsoTiles.begin());
	}

	ReadFile(file, &_tileX, sizeof(int), &read, NULL);
	ReadFile(file, &_tileY, sizeof(int), &read, NULL);

	for (int i = 0; i < _tileY; ++i)
	{
		for (int k = 0; k < _tileX; ++k)
		{
			tagIsometricTile* tempIso = new tagIsometricTile;

			ReadFile(file, tempIso, sizeof(tagIsometricTile), &read, NULL);
			_vIsoTiles.push_back(tempIso);

		}
	}


	// ������ Ÿ���� �ε����� �ٸ��� ������ ������ ���ش�.
	for (int i = 0; i < (int)(_tileX * _tileY) - 1; ++i)
	{
		for (int k = 1; k < (_tileX * _tileY); ++k)
		{
			// y���� �ٸ� ��
			if (_vIsoTiles[k - 1]->idY > _vIsoTiles[k]->idY)
			{
				swap(_vIsoTiles[k - 1], _vIsoTiles[k]);
			}
			// ���� ��
			else if(_vIsoTiles[k  - 1 ]->idY == _vIsoTiles[k]->idY)
			{
				if (_vIsoTiles[k - 1]->idX > _vIsoTiles[k]->idX)
				{
					swap(_vIsoTiles[k - 1], _vIsoTiles[k]);
				}
			}
		}
	}
	
	CloseHandle(file);

}

void mapManager::changeMap(MAP map)
{
	_currentMap = map;

	SOUNDMANAGER->stop(_currentBgm);

	switch (map)
	{
	case MAP_TUTORIAL01:
		_currentBgm = "�ʵ�_��";
		load("tutorialMap01");
		break;
	case MAP_TUTORIAL02:
		_currentBgm = "�ʵ�_��";
		load("tutorialMap02");
		break;
	case MAP_TOWN:
		_currentBgm = "����_��";
		load("townMap");
		break;
	case MAP_FIELD:
		_currentBgm = "����_��";
		load("fieldMap01");
		break;
	case MAP_MAX:
		break;
	default:
		break;
	}

	SOUNDMANAGER->play(_currentBgm,_bgmVolume);
}

bool mapManager::isOnceClick()
{
	// a star -> ������ ���̸� �ȹ��
	// ���ǽ� ���ʹ� üũ -> �ƴϸ� ����ŷ -> ��ŷ�� ���� �ε����� ���� �÷��̾��� �ε����� �˾ƾ� ��
	// 
	// �̰� �Ű� ������� ����� ������ �Լ� ����.
	if (isPickTile())
	{
		// ���Ǿ��� ���ʹ� Ŭ�� - > ���ǽó� ���ʹ̱� ��ŷ�Ǹ� �ڽ��� ��ǥ�� �ʿ� �����ش�.
		// �÷��̾� ��ġ�� Ÿ���� ��ġ(���콺��ŷ�̳� ���ʹ� ��ǥ)
		// ��ŷ�� ������ ���� Ÿ����ġ�� ��ŷ�� Ÿ����ġ�� �ٸ��� ���̽�Ÿ 
		// �����ؼ� Ÿ�� �߽��� �������� �̵� ������ ��ǥ �̵�
		// 
		// 
		// 
		if (_currentTileX == _targetTileX && _currentTileY == _targetTileY) return true;

		_ast->setTile(_currentTileX, _currentTileY, _targetTileX, _targetTileY);
		_vPath = _ast->pathFinder(_ast->getCurrentTile());
		
		// wall �� Ŭ�������� ���ο� end��ǥ�� ���ѵ� �װ� �ٽ� target���� ����
		
		_player->setTarget(getTile(_vPath[0])->center.x, getTile(_vPath[0])->center.y);

		// ���Ͱ� �Ųٷ� ��� �����Ƿ� �� ������ �����.

		vector<int> vTempPath;

		for (int i = 0; i < _vPath.size(); ++i)
		{
			int tempPath = _vPath[_vPath.size() - (i+1)];
			// ���⼭ �ѹ� �� ����ó���� ���ش�.
			if(_vIsoTiles[tempPath]->obj == OBJ_NONE) vTempPath.push_back(tempPath);
		}

		_vPath = vTempPath;

		_player->setPath(_vPath);


		return true;
	}

	return false;
}

bool mapManager::isPickTile(float targetX, float targetY, bool isPlayer)
{
	if (isPlayer)
	{


		// �÷��̾��� Ÿ�� �ε����� �˾Ƴ���.

		// Ÿ���� ���� ��ǥ�� �˸� ���� ���콺 ��ǥ�� �뷫���� Ÿ�� index�� �˼� �ִ�.
		int playerIndexSub = (_player->getX() - _vIsoTiles[0]->center.x) / (_width / 2); // ��
		int playerIndexSum = (_player->getY() - _vIsoTiles[0]->center.y) / (_height / 2); // ��

		int playerIndexX = (playerIndexSum + playerIndexSub) / 2;
		int playerIndexY = (playerIndexSum - playerIndexSub) / 2;

		for (int y = playerIndexY - 3; y < playerIndexY + 3; ++y)
		{
			if (y < 0) continue;
			for (int x = playerIndexX - 3; x < playerIndexX + 3; ++x)
			{
				if (x < 0) continue;

				// ���� ������ (y-b) = m(x-a);  / ����
				// _ptMouse.y - ������y = ���� * (_ptMouse.x - ������x)
				// ����, ������ �������� ���Ѵ�.

				// ���� ������ (y-b) = -m(x-a);  \(��������) ����
				// _ptMouse.y - ������y = -���� * (_ptMouse.x - ������x)
				// ��, �Ʒ� �������� ���Ѵ�.

				// ����� ����

				float isoWid = _width;
				float isoHei = _height;

				float grade = (float)(_height / 2) / (_width / 2);

				float centerX = _vIsoTiles[y * _tileX + x]->center.x;
				float centerY = _vIsoTiles[y * _tileX + x]->center.y;


				// 1. ���� ��ǥ�� ���콺 ������ + ��Ŀ�� ���� ��
				// 2. ���� ��ǥ���� ��Ŀ�� ���� �� ���콺 ������ ��
				POINT D1, D2, D3, D4;
				D1.x = centerX - isoWid / 2; D1.y = centerY;
				D2.x = centerX; D2.y = centerY - isoHei / 2;
				D3.x = centerX + isoWid / 2; D3.y = centerY;
				D4.x = centerX; D4.y = centerY + isoHei / 2;

				float d1 = _player->getY() - D1.y - (-grade * (_player->getX() - D1.x));
				float d2 = _player->getY() - D2.y - (grade * (_player->getX() - D2.x));
				float d3 = _player->getY() - D3.y - (-grade * (_player->getX() - D3.x));
				float d4 = _player->getY() - D4.y - (grade * (_player->getX() - D4.x));

				if (d1 > 0)
				{
					if (d2 > 0)
					{
						if (d3 < 0)
						{
							if (d4 < 0)
							{
								_currentTileX = x;
								_currentTileY = y;
								break;
							}
						}
					}
				}
			}
		}
	}

	// Ÿ���� Ÿ�� �ε����� �˾Ƴ���.

	// Ÿ���� ���� ��ǥ�� �˸� ���� ���콺 ��ǥ�� �뷫���� Ÿ�� index�� �˼� �ִ�.
	int targetIndexSub = (targetX - _vIsoTiles[0]->center.x) / (_width / 2); // ��
	int targetIndexSum = (targetY - _vIsoTiles[0]->center.y) / (_height / 2); // ��

	int targetIndexX = (targetIndexSum + targetIndexSub) / 2;
	int targetIndexY = (targetIndexSum - targetIndexSub) / 2;

	for (int y = targetIndexY - 3; y < targetIndexY + 3; ++y)
	{
		if (y < 0) continue;
		for (int x = targetIndexX - 3; x < targetIndexX + 3; ++x)
		{
			if (x < 0) continue;

			// ���� ������ (y-b) = m(x-a);  / ����
			// _ptMouse.y - ������y = ���� * (_ptMouse.x - ������x)
			// ����, ������ �������� ���Ѵ�.

			// ���� ������ (y-b) = -m(x-a);  \(��������) ����
			// _ptMouse.y - ������y = -���� * (_ptMouse.x - ������x)
			// ��, �Ʒ� �������� ���Ѵ�.

			// ����� ����

			float isoWid = _width;
			float isoHei = _height;

			float grade = (float)(_height / 2) / (_width / 2);

			float centerX = _vIsoTiles[y * _tileX + x]->center.x;
			float centerY = _vIsoTiles[y * _tileX + x]->center.y;


			// 1. ���� ��ǥ�� ���콺 ������ + ��Ŀ�� ���� ��
			// 2. ���� ��ǥ���� ��Ŀ�� ���� �� ���콺 ������ ��
			POINT D1, D2, D3, D4;
			D1.x = centerX - isoWid / 2; D1.y = centerY;
			D2.x = centerX; D2.y = centerY - isoHei / 2;
			D3.x = centerX + isoWid / 2; D3.y = centerY;
			D4.x = centerX; D4.y = centerY + isoHei / 2;

			float d1 = targetY - D1.y - (-grade * ( targetX - D1.x));
			float d2 = targetY - D2.y - ( grade * ( targetX - D2.x));
			float d3 = targetY - D3.y - (-grade * ( targetX - D3.x));
			float d4 = targetY - D4.y - ( grade * ( targetX - D4.x));

			if (d1 > 0)
			{
				if (d2 > 0)
				{
					if (d3 < 0)
					{
						if (d4 < 0)
						{
							_targetTileX = x;
							_targetTileY = y;
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

bool mapManager::isPickTile()
{
	// �÷��̾��� Ÿ�� �ε����� �˾Ƴ���.

	// Ÿ���� ���� ��ǥ�� �˸� ���� ���콺 ��ǥ�� �뷫���� Ÿ�� index�� �˼� �ִ�.
	int playerIndexSub = (_player->getX() - _vIsoTiles[0]->center.x) / (_width / 2); // ��
	int playerIndexSum = (_player->getY() - _vIsoTiles[0]->center.y) / (_height / 2); // ��

	int playerIndexX = (playerIndexSum + playerIndexSub) / 2;
	int playerIndexY = (playerIndexSum - playerIndexSub) / 2;

	for (int y = playerIndexY - 3; y < playerIndexY + 3; ++y)
	{
		if (y < 0) continue;
		for (int x = playerIndexX - 3; x < playerIndexX + 3; ++x)
		{
			if (x < 0) continue;

			// ���� ������ (y-b) = m(x-a);  / ����
			// _ptMouse.y - ������y = ���� * (_ptMouse.x - ������x)
			// ����, ������ �������� ���Ѵ�.

			// ���� ������ (y-b) = -m(x-a);  \(��������) ����
			// _ptMouse.y - ������y = -���� * (_ptMouse.x - ������x)
			// ��, �Ʒ� �������� ���Ѵ�.

			// ����� ����

			float isoWid = _width;
			float isoHei = _height;

			float grade = (float)(_height / 2) / (_width / 2);

			float centerX = _vIsoTiles[y * _tileX + x]->center.x;
			float centerY = _vIsoTiles[y * _tileX + x]->center.y;


			// 1. ���� ��ǥ�� ���콺 ������ + ��Ŀ�� ���� ��
			// 2. ���� ��ǥ���� ��Ŀ�� ���� �� ���콺 ������ ��
			POINT D1, D2, D3, D4;
			D1.x = centerX - isoWid / 2; D1.y = centerY;
			D2.x = centerX; D2.y = centerY - isoHei / 2;
			D3.x = centerX + isoWid / 2; D3.y = centerY;
			D4.x = centerX; D4.y = centerY + isoHei / 2;

			float d1 = _player->getY() - D1.y - (-grade * (_player->getX() - D1.x));
			float d2 = _player->getY() - D2.y - (grade * (_player->getX() - D2.x));
			float d3 = _player->getY() - D3.y - (-grade * (_player->getX() - D3.x));
			float d4 = _player->getY() - D4.y - (grade * (_player->getX() - D4.x));

			if (d1 > 0)
			{
				if (d2 > 0)
				{
					if (d3 < 0)
					{
						if (d4 < 0)
						{
							_currentTileX = x;
							_currentTileY = y;
							break;
						}
					}
				}
			}
		}
	}

	// ��ŷ�� ���� Ÿ�� �ε����� �˾Ƴ���.

	// Ÿ���� ���� ��ǥ�� �˸� ���� ���콺 ��ǥ�� �뷫���� Ÿ�� index�� �˼� �ִ�.
	int indexSub = ((_ptMouse.x + _focus.left) - _vIsoTiles[0]->center.x) / (_width / 2); // ��
	int indexSum = ((_ptMouse.y + _focus.top) - _vIsoTiles[0]->center.y) / (_height / 2); // ��

	int indexX = (indexSum + indexSub) / 2;
	int indexY = (indexSum - indexSub) / 2;

	for (int y = indexY - 3; y < indexY + 3; ++y)
	{
		if (y < 0) continue;
		for (int x = indexX - 3; x < indexX + 3; ++x)
		{
			if (x < 0) continue;

			// ���� ������ (y-b) = m(x-a);  / ����
			// _ptMouse.y - ������y = ���� * (_ptMouse.x - ������x)
			// ����, ������ �������� ���Ѵ�.

			// ���� ������ (y-b) = -m(x-a);  \(��������) ����
			// _ptMouse.y - ������y = -���� * (_ptMouse.x - ������x)
			// ��, �Ʒ� �������� ���Ѵ�.

			// ����� ����

			float isoWid = _width;
			float isoHei = _height;

			float grade = (float)(_height / 2) / (_width / 2);

			float centerX = _vIsoTiles[y * _tileX + x]->center.x - _focus.left;
			float centerY = _vIsoTiles[y * _tileX + x]->center.y - _focus.top;

			POINT D1, D2, D3, D4;
			D1.x = centerX - isoWid / 2; D1.y = centerY;
			D2.x = centerX; D2.y = centerY - isoHei / 2;
			D3.x = centerX + isoWid / 2; D3.y = centerY;
			D4.x = centerX; D4.y = centerY + isoHei / 2;

			float d1 = _ptMouse.y - D1.y - (-grade * (_ptMouse.x - D1.x));
			float d2 = _ptMouse.y - D2.y - (grade * (_ptMouse.x - D2.x));
			float d3 = _ptMouse.y - D3.y - (-grade * (_ptMouse.x - D3.x));
			float d4 = _ptMouse.y - D4.y - (grade * (_ptMouse.x - D4.x));

			if (d1 > 0)
			{
				if (d2 > 0)
				{
					if (d3 < 0)
					{
						if (d4 < 0)
						{
							_targetTileX = x;
							_targetTileY = y;
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

