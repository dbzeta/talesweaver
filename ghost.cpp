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

	//타일 주변 9개를 돌면서
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// 현재 타일 기준으로 주변 9개

			// -1 예외처리
			if (startX + j < 0 || startY + i < 0) continue;
			if (startX + j > TILEX - 1 || startY + i > TILEY - 1) continue;

			int tileIdx = (startY * TILEX) + startX + j + (i * TILEX);
			//클로즈타일, 시작타일, 끝나일은 넘어가라
			if (!_packmanMap->getTiles()[tileIdx].isOpen) continue;
			if (_packmanMap->getAttribute()[tileIdx] & ATTR_UNMOVE) continue;
			if (tileIdx == _ghost[0].startTileIdx) continue;

			//상위노드는 현재타일로 계속 갱신해준다
			// 결과적으론 오른쪽대각선이 여기들어감
			//node->setParentNode(_currentTile);

			// 앞에서 이미 open에 집어넣은 부분은 넘어가기 위해서 사용.

			//체크 해놓을 임의의 불값
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
	//비교할 임의의 값
	float tempTotalCost = 5000;

	for (int i = 0; i < addOpenList(currentTileIdx).size(); i++)
	{
		//현재 노드로부터 도착지점까지 경로비용
		_ghost[0].costToGoal = ((abs(_packman->getTileX() - _packmanMap->getTiles()[_ghost[0].currentTileIdx].terrainFrameX) +
			abs(_packman->getTileY() - _packmanMap->getTiles()[_ghost[0].currentTileIdx].terrainFrameY)) * 10);


		//	POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		//	POINT center2 = _vOpenList[i]->getCenter();

		//	//시작점으로부터 현재노드까지 경로비용
		//	// currentTile 주변 타일은 코스트가 누적되므로 수정해야함

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

		//	//가장 비용이 저렴한 애를 뽑자
		//	if (tempTotalCost > _vOpenList[i]->getTotalCost())
		//	{
		//		tempTotalCost = _vOpenList[i]->getTotalCost();
		//		tempTile = _vOpenList[i];
		//	}

		//	// 가장 비용이 저렴한 타일 검출 ( 가장 저렴한 타일은 계속해서 변할수 있으므로 전체를 다 검사 해 준다 )
		//	// 그 외의 타일은 close 타일에 넣기위해 isOpen을 false해준다.
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

		//	// tempTile은 addObj가 FALSE값이다.

		//	if (!addObj) continue;
		//	_vOpenList.push_back(tempTile);
		//}

		////도착했으면~
		//if (tempTile->getAttribute() == "end")
		//{
		//	//이때까지 온 경로에 색칠해라
		//	while (_currentTile->getParentNode() != NULL)
		//	{
		//		_currentTile->setColor(RGB(22, 14, 128));
		//		_currentTile = _currentTile->getParentNode();
		//	}

		//	return;
		//}

		////지나온 길은 클로즈 리스트로~
		//_vCloseList.push_back(tempTile);

		////다음 노드로 설정된 타일을 제거
		//for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		//{

		//	if (*_viOpenList == tempTile)
		//	{
		//		_viOpenList = _vOpenList.erase(_viOpenList);
		//		break;
		//	}
		//}

		//_currentTile = tempTile;

		//재귀로 뙇!
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
