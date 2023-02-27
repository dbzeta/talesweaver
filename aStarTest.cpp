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
	// //타일 셋팅함수
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
	// 		//타일을 싹다 담아준다
	// 		tile* node = new tile;
	// 		node->init(j, i);
	// 		_vTotalList.push_back(node);
	// 
	// 
	// 		// totalList에는 start, end, 그 외의 나머지 모든 타일!! 이 담겨있다
	// 		// start와 end의 경우 나머지와 구분을 해주어야 하므로 continue 로 넘겨준다.
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

	// 예외처리 목적지가 wall일경우
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

	//타일 주변 9개를 돌면서
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// 현재 타일 기준으로 주변 9개

			// -1 예외처리
			if (startX + j < 0 || startY + i < 0) continue;
			if (startX + j > _tileX - 1 || startY + i > _tileX - 1) continue;

			int index = (startY * _tileX) + startX + j + (i * _tileX);
			tile* node = _vTotalList[(startY * _tileX) + startX + j + (i * _tileX)];
			//클로즈타일, 시작타일, 끝나일은 넘어가라
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;
			if (i == 1 && j == 1) continue;

			//상위노드는 현재타일로 계속 갱신해준다
			// 결과적으론 오른쪽대각선이 여기들어감
			node->setParentNode(_currentTile);

			// 앞에서 이미 open에 집어넣은 부분은 넘어가기 위해서 사용.

			//체크 해놓을 임의의 불값
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

//길찾기
vector<int> aStarTest::pathFinder(tile* currentTile)
{
	if (_startTile == _endTile) return _vPath;
	//비교할 임의의 값
	float tempTotalCost = 5000;
	tile* tempTile = NULL;


	for (int i = 0; i < addOpenList(currentTile).size(); i++)
	{
		//현재 노드로부터 도착지점까지 경로비용
		_vOpenList[i]->setCostToGoal((abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) +
			abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);


		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();

		//시작점으로부터 현재노드까지 경로비용
		// currentTile 주변 타일은 코스트가 누적되므로 수정해야함

		_vOpenList[i]->setCostFromStart(((getDistance(center1.x, center1.y, center2.x, center2.y) > TILEWIDTH) ? 14 : 10) +
			_vOpenList[i]->getParentNode()->getCostFromStart());

		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() +
			_vOpenList[i]->getCostFromStart());

		//가장 비용이 저렴한 애를 뽑자
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}


		_vOpenList[i]->setIsOpen(false);

		// tempTile은 addObj가 FALSE값이다.
	}


	if (tempTile == NULL)
		return _vPath;

	//도착했으면~
	if (tempTile->getAttribute() == "end")
	{
		//이때까지 온 경로에 색칠해라
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

	//지나온 길은 클로즈 리스트로~
	_vCloseList.push_back(tempTile);

	//다음 노드로 설정된 타일을 제거
	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;

	//재귀로 뙇!
	_vPath = pathFinder(_currentTile);

	return _vPath;
}


