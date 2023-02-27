#include "stdafx.h"
#include "ghost.h"
#include "packmanMap.h"
#include "packman.h"

ghost::ghost()
{
}


ghost::~ghost()
{
}


HRESULT ghost::init()
{
	
	IMAGEMANAGER->addFrameImage("weakGhost", "image\\ghost_weak.bmp", 32 * 2, 16 * 2, 2, 1, true, RGB(255, 0, 255));

	_ghost[0].image = IMAGEMANAGER->addFrameImage("ghost1", "image\\ghost1.bmp", 32 * 2, 64 * 2, 2, 4, true, RGB(255, 0, 255));
	_ghost[1].image = IMAGEMANAGER->addFrameImage("ghost2", "image\\ghost2.bmp", 32 * 2, 64 * 2, 2, 4, true, RGB(255, 0, 255));
	_ghost[2].image = IMAGEMANAGER->addFrameImage("ghost3", "image\\ghost3.bmp", 32 * 2, 64 * 2, 2, 4, true, RGB(255, 0, 255));
	_ghost[3].image = IMAGEMANAGER->addFrameImage("ghost4", "image\\ghost4.bmp", 32 * 2, 64 * 2, 2, 4, true, RGB(255, 0, 255));

	for (int i = 0; i < GHOSTMAX; i++)
	{
		_ghost[i].currentFrameX = _ghost[i].currentFrameY = 0;
		_ghost[i].count = 0;
		_ghost[i].dir = GHOSTDIRECTION_UP;
		_ghost[i].speed = 90.0f;
	}


	return S_OK;
}

void ghost::relese()
{

}

void ghost::update()
{
	move();
}

void ghost::render()
{
	
	for (int i = 0; i < GHOSTMAX; i++)
	{
		_ghost[i].image->frameRender(getMemDC(), _ghost[i].rc.left, _ghost[i].rc.top, 
			_ghost[i].currentFrameX, _ghost[i].currentFrameY);
	}

}

void ghost::move()
{
	for (int i = 0; i < GHOSTMAX; i++)
	{
		_ghost[i].count++;

		switch (_ghost[i].dir)
		{
			case GHOSTDIRECTION_LEFT:
			{
				_ghost[i].currentFrameY = 0;
				if (_ghost[i].count % 8 == 0) _ghost[i].currentFrameX++;
				if (_ghost[i].currentFrameX > _ghost[i].image->getMaxFrameX()) _ghost[i].currentFrameX = 0;
			}break;
			case GHOSTDIRECTION_RIGHT:
			{
				_ghost[i].currentFrameY = 2;
				if (_ghost[i].count % 8 == 0) _ghost[i].currentFrameX++;
				if (_ghost[i].currentFrameX > _ghost[i].image->getMaxFrameX()) _ghost[i].currentFrameX = 0;
			}break;
			case GHOSTDIRECTION_UP:
			{
				_ghost[i].currentFrameY = 1;
				if (_ghost[i].count % 8 == 0) _ghost[i].currentFrameX++;
				if (_ghost[i].currentFrameX > _ghost[i].image->getMaxFrameX()) _ghost[i].currentFrameX = 0;
			}break;
			case GHOSTDIRECTION_DOWN:
			{
				_ghost[i].currentFrameY = 3;
				if (_ghost[i].count % 8 == 0) _ghost[i].currentFrameX++;
				if (_ghost[i].currentFrameX > _ghost[i].image->getMaxFrameX()) _ghost[i].currentFrameX = 0;
			}break;
			default:
				break;
		}

	}


}

vector<int> ghost::addOpenList(int currentTileIdx)
{
	int startX = _packmanMap->getTiles()[currentTileIdx].terrainFrameX - 1;
	int startY = _packmanMap->getTiles()[currentTileIdx].terrainFrameY - 1;

	//Ÿ�� �ֺ� 9���� ���鼭
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// ���� Ÿ�� �������� �ֺ� 9��

			// -1 ����ó��
			if (startX + j < 0 || startY + i < 0) continue;
			if (startX + j > TILEX - 1 || startY + i > TILEY - 1) continue;

			int tileIdx = (startY * TILEX) + startX + j + (i * TILEX);
			//Ŭ����Ÿ��, ����Ÿ��, �������� �Ѿ��
			if (!_packmanMap->getTiles()[tileIdx].isOpen) continue;
			if (_packmanMap->getAttribute()[tileIdx] & ATTR_UNMOVE) continue;
			if (tileIdx == _ghost[0].startTileIdx) continue;

			//�������� ����Ÿ�Ϸ� ��� �������ش�
			// ��������� �����ʴ밢���� �����
			//node->setParentNode(_currentTile);

			// �տ��� �̹� open�� ������� �κ��� �Ѿ�� ���ؼ� ���.

			//üũ �س��� ������ �Ұ�
			bool addObj = true;

			for (int i = 0 ; _ghost[0].vOpenList.size(); i++)
			{
			
				if (_ghost[0].vOpenList[i] == tileIdx)
				{
					addObj = false;
					break;
				}
			}

			if (!addObj) continue;
			_ghost[0].vOpenList.push_back(tileIdx);
		}
	}

	return _ghost[0].vOpenList;
}

void ghost::pathFinder(int currentTileIdx)
{
	//���� ������ ��
	float tempTotalCost = 5000;

	for (int i = 0; i < addOpenList(currentTileIdx).size(); i++)
	{
		//���� ���κ��� ������������ ��κ��
		_ghost[0].costToGoal = ((abs(_packman->getTileX() - _packmanMap->getTiles()[_ghost[0].currentTileIdx].terrainFrameX) +
			abs(_packman->getTileY() - _packmanMap->getTiles()[_ghost[0].currentTileIdx].terrainFrameY)) * 10);


		//	POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		//	POINT center2 = _vOpenList[i]->getCenter();

		//	//���������κ��� ��������� ��κ��
		//	// currentTile �ֺ� Ÿ���� �ڽ�Ʈ�� �����ǹǷ� �����ؾ���

		//	if (_currentTile->getCostFromStart() > 0)
		//	{
		//		float currentCost = _currentTile->getCostFromStart();
		//		_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > TILEWIDTH) ? 14 + currentCost : 10 + currentCost);
		//	}
		//	else
		//	{
		//		_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > TILEWIDTH) ? 14 : 10);
		//	}

		//	_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() +
		//		_vOpenList[i]->getCostFromStart());

		//	//���� ����� ������ �ָ� ����
		//	if (tempTotalCost > _vOpenList[i]->getTotalCost())
		//	{
		//		tempTotalCost = _vOpenList[i]->getTotalCost();
		//		tempTile = _vOpenList[i];
		//	}

		//	// ���� ����� ������ Ÿ�� ���� ( ���� ������ Ÿ���� ����ؼ� ���Ҽ� �����Ƿ� ��ü�� �� �˻� �� �ش� )
		//	// �� ���� Ÿ���� close Ÿ�Ͽ� �ֱ����� isOpen�� false���ش�.
		//	bool addObj = true;
		//	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		//	{
		//		if (*_viOpenList == tempTile)
		//		{
		//			addObj = false;
		//			break;
		//		}
		//	}

		//	_vOpenList[i]->setIsOpen(false);

		//	// tempTile�� addObj�� FALSE���̴�.

		//	if (!addObj) continue;
		//	_vOpenList.push_back(tempTile);
		//}

		////����������~
		//if (tempTile->getAttribute() == "end")
		//{
		//	//�̶����� �� ��ο� ��ĥ�ض�
		//	while (_currentTile->getParentNode() != NULL)
		//	{
		//		_currentTile->setColor(RGB(22, 14, 128));
		//		_currentTile = _currentTile->getParentNode();
		//	}

		//	return;
		//}

		////������ ���� Ŭ���� ����Ʈ��~
		//_vCloseList.push_back(tempTile);

		////���� ���� ������ Ÿ���� ����
		//for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		//{

		//	if (*_viOpenList == tempTile)
		//	{
		//		_viOpenList = _vOpenList.erase(_viOpenList);
		//		break;
		//	}
		//}

		//_currentTile = tempTile;

		//��ͷ� ��!
		//pathFinder(_currentTile);
	}
}

void ghost::setGhostPosition(int pos, int ghostNum)
{
	_ghost[ghostNum].rc = _packmanMap->getTiles()[pos].rc;

	_ghost[ghostNum].cx = _ghost[ghostNum].rc.left + (_ghost[ghostNum].rc.right - _ghost[ghostNum].rc.left) / 2;
	_ghost[ghostNum].cy = _ghost[ghostNum].rc.top + (_ghost[ghostNum].rc.bottom - _ghost[ghostNum].rc.top) / 2;

	_ghost[ghostNum].startTileIdx = _ghost[ghostNum].currentTileIdx = pos;

}
