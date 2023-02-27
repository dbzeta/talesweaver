#include "stdafx.h"
#include "aStarTest.h"


aStarTest::aStarTest()
{
}


aStarTest::~aStarTest()
{

}

HRESULT aStarTest::init(int tileX, int tileY)
{
	_isStart = 0;

	_tileX = tileX;
	_tileY = tileY;

	return S_OK;
}

void aStarTest::release()
{
	while (_vOpenList.size() > 0)
	{
		_vOpenList.erase(_vOpenList.begin());
	}
	while (_vCloseList.size() > 0)
	{
		_vCloseList.erase(_vCloseList.begin());
	}
	for (int i = 0; i < _vTotalList.size(); i++)
	{
		_vTotalList[i]->setIsOpen(true);
	}
}

void aStarTest::update()
{
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_currentTile = _startTile;
		pathFinder(_currentTile);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vTotalList.size(); i++)
		{
			if (PtInRect(&_vTotalList[i]->getRect(), _ptMouse))
			{
				if (_vTotalList[i]->getAttribute() == "start") continue;
				if (_vTotalList[i]->getAttribute() == "end") continue;

				_vTotalList[i]->setIsOpen(false);
				_vTotalList[i]->setAttribute("wall");
				_vTotalList[i]->setColor(RGB(230, 140, 200));
				break;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		this->release();
	}

}

void aStarTest::render()
{
	for (int i = 0; i < _vTotalList.size(); i++)
	{
		_vTotalList[i]->render();
	}
}


void aStarTest::setTile(int wallX, int wallY, bool isWall)
{
	// //Ÿ�� �����Լ�
	// _startTile = new tile;
	// _startTile->init(4, 12);
	// _startTile->setAttribute("start");
	// 
	// _endTile = new tile;
	// _endTile->init(20, 12);
	// _endTile->setAttribute("end");
	// 
	// _currentTile = _startTile;
	// 
	// for (int i = 0; i < TILENUMY; i++)
	// {
	// 	for (int j = 0; j < TILENUMX; j++)
	// 	{
	// 		if (j == _startTile->getIdX() && i == _startTile->getIdY())
	// 		{
	// 			_startTile->setColor(RGB(0, 255, 255));
	// 			_vTotalList.push_back(_startTile);
	// 			continue;
	// 		}
	// 		if (j == _endTile->getIdX() && i == _endTile->getIdY())
	// 		{
	// 			_endTile->setColor(RGB(10, 120, 55));
	// 			_vTotalList.push_back(_endTile);
	// 			continue;
	// 		}
	// 		//Ÿ���� �ϴ� ����ش�
	// 		tile* node = new tile;
	// 		node->init(j, i);
	// 		_vTotalList.push_back(node);
	// 
	// 
	// 		// totalList���� start, end, �� ���� ������ ��� Ÿ��!! �� ����ִ�
	// 		// start�� end�� ��� �������� ������ ���־�� �ϹǷ� continue �� �Ѱ��ش�.
	// 	}
	// }


	tile* node = new tile;
	node->init(wallX, wallY);

	if (isWall)
	{
		node->setAttribute("wall");
		node->setIsOpen(false);
	}
	else
	{
		node->setAttribute("");
	}

	_vTotalList.push_back(node);


}

void aStarTest::setTile(int startX, int startY, int endX, int endY)
{
	_vOpenList.clear();
	_vCloseList.clear();
	_vPath.clear();

	for (int i = 0; i < _tileX * _tileY; ++i)
	{
		tile* node = _vTotalList[i];
		if (node->getAttribute() != "wall")
		{
			node->setAttribute("");
			node->setIsOpen(true);
			node->setCostFromStart(0);
			node->setCostToGoal(0);
			node->setTotalCost(0);
			node->setParentNode(NULL);
		}
	}
	_startTile = _vTotalList[startY * _tileX + startX];
	_startTile->setAttribute("start");

	// ����ó�� �������� wall�ϰ��
	_endTile = _vTotalList[endY * _tileX + endX];
	
	if (_endTile->getAttribute() != "")
	{

		int tempDistance = 9999;
		int tempTileIndex = 0;

		for (int i = 0; i < addOpenList(_endTile).size(); ++i)
		{
			int distance = getDistance(_vOpenList[i]->getCenter().x, _vOpenList[i]->getCenter().y, _startTile->getCenter().x, _startTile->getCenter().y);
			
			if (tempDistance > distance)
			{
				tempDistance = distance;
				tempTileIndex = _vOpenList[i]->getIdX() + _vOpenList[i]->getIdY() * _tileX;
			}
		}

		_endTile = _vTotalList[tempTileIndex];
		_endTile->setAttribute("end");

	}
	else
	{
		_endTile->setAttribute("end");
	}
	
	_currentTile = _startTile;

	_vOpenList.clear();
	_vCloseList.clear();
	_vPath.clear();

}

vector<tile*> aStarTest::addOpenList(tile* currentTile)
{
	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	//Ÿ�� �ֺ� 9���� ���鼭
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// ���� Ÿ�� �������� �ֺ� 9��

			// -1 ����ó��
			if (startX + j < 0 || startY + i < 0) continue;
			if (startX + j > _tileX - 1 || startY + i > _tileX - 1) continue;

			int index = (startY * _tileX) + startX + j + (i * _tileX);
			tile* node = _vTotalList[(startY * _tileX) + startX + j + (i * _tileX)];
			//Ŭ����Ÿ��, ����Ÿ��, �������� �Ѿ��
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;
			if (i == 1 && j == 1) continue;

			//�������� ����Ÿ�Ϸ� ��� �������ش�
			// ��������� �����ʴ밢���� �����
			node->setParentNode(_currentTile);

			// �տ��� �̹� open�� ������� �κ��� �Ѿ�� ���ؼ� ���.

			//üũ �س��� ������ �Ұ�
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{

				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));

			if (!addObj) continue;
			_vOpenList.push_back(node);
		}
	}

	return _vOpenList;
}

//��ã��
vector<int> aStarTest::pathFinder(tile* currentTile)
{
	if (_startTile == _endTile) return _vPath;
	//���� ������ ��
	float tempTotalCost = 5000;
	tile* tempTile = NULL;


	for (int i = 0; i < addOpenList(currentTile).size(); i++)
	{
		//���� ���κ��� ������������ ��κ��
		_vOpenList[i]->setCostToGoal((abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) +
			abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);


		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();

		//���������κ��� ��������� ��κ��
		// currentTile �ֺ� Ÿ���� �ڽ�Ʈ�� �����ǹǷ� �����ؾ���

		_vOpenList[i]->setCostFromStart(((getDistance(center1.x, center1.y, center2.x, center2.y) > TILEWIDTH) ? 14 : 10) +
			_vOpenList[i]->getParentNode()->getCostFromStart());

		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() +
			_vOpenList[i]->getCostFromStart());

		//���� ����� ������ �ָ� ����
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}


		_vOpenList[i]->setIsOpen(false);

		// tempTile�� addObj�� FALSE���̴�.
	}


	if (tempTile == NULL)
		return _vPath;

	//����������~
	if (tempTile->getAttribute() == "end")
	{
		//�̶����� �� ��ο� ��ĥ�ض�
		while (tempTile->getParentNode() != NULL)
		{
			int x = tempTile->getIdX();
			int y = tempTile->getIdY();

			int tileIdx = y * _tileX + x;
			_vPath.push_back(tileIdx);

			tempTile = tempTile->getParentNode();
		}

		return _vPath;
	}

	//������ ���� Ŭ���� ����Ʈ��~
	_vCloseList.push_back(tempTile);

	//���� ���� ������ Ÿ���� ����
	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;

	//��ͷ� ��!
	_vPath = pathFinder(_currentTile);

	return _vPath;
}


