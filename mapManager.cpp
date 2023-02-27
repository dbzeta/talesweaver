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
	
	_currentBgm = "필드_낮";
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

		if (_vIsoTiles[i]->obj == OBJ_WALL) objImage = IMAGEMANAGER->findImage("기본오브젝트");
		else if (_vIsoTiles[i]->obj == OBJ_FLAG) objImage = IMAGEMANAGER->findImage("기본오브젝트2");
		else if (_vIsoTiles[i]->obj == OBJ_NONE) continue;
		RECT objRect = RectMake(_vIsoTiles[i]->rc.left, _vIsoTiles[i]->rc.top - objImage->getFrameHeight() + IMAGEMANAGER->findImage("기본타일")->getFrameHeight(),
			objImage->getFrameWidth(), objImage->getFrameHeight());

		DRAWMANAGER->addDrawList(DRAW_FRAMERENDER, "OBJECT", objImage, _vIsoTiles[i]->objFrameX, _vIsoTiles[i]->objFrameY, objRect, 0);
	}
}

void mapManager::render()				
{
	for (int i = 0; i < _vIsoTiles.size(); ++i)
	{
		// 클리핑 기법을 사용하여 화면에 안보이는 애들은 랜더를 안해준다
		RECT temp;
		// 포커스의 rect와 타일의 rect를 비교하여 교차하는 부분이 없을경우 continue로 넘겨주어 랜더를 안해준다.
		if (!IntersectRect(&temp, &_focus, &_vIsoTiles[i]->rc)) continue;

		// 화면에 보여지는 타일의 실제 좌표는 고정이고 추가된 포커스 좌표에 따라 보여진다.
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
			IMAGEMANAGER->findImage("기본타일")->frameRender(getMemDC(), _vIsoTiles[i]->rc.left - _focus.left, _vIsoTiles[i]->rc.top - _focus.top, _vIsoTiles[i]->terrainFrameX, _vIsoTiles[i]->terrainFrameY);
		}

		if (_debug)
		{
			// Rectangle(getMemDC(), _vIsoTiles[i]->rc.left, _vIsoTiles[i]->rc.top, _vIsoTiles[i]->rc.right, _vIsoTiles[i]->rc.bottom);
		}

	}

	// 오브젝트
	for (int i = 0; i < _vIsoTiles.size(); ++i)
	{
	// 	// 클리핑 기법을 사용하여 화면에 안보이는 애들은 랜더 안해
	// 	RECT temp;
	// 
		image* objImage;
	
		if (_vIsoTiles[i]->obj == OBJ_WALL) objImage = IMAGEMANAGER->findImage("기본오브젝트");
		else if (_vIsoTiles[i]->obj == OBJ_FLAG) objImage = IMAGEMANAGER->findImage("기본오브젝트2");
		else if (_vIsoTiles[i]->obj == OBJ_NONE) continue;
	
	RECT objRect = RectMake(_vIsoTiles[i]->rc.left, _vIsoTiles[i]->rc.top - objImage->getFrameHeight() + IMAGEMANAGER->findImage("기본타일")->getFrameHeight(),
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
		// 불러오기 후 불러오기 누르면 터지는데 이유가 뭐지??
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


	// 가져온 타일의 인덱스가 다르기 때문에 재정렬 해준다.
	for (int i = 0; i < (int)(_tileX * _tileY) - 1; ++i)
	{
		for (int k = 1; k < (_tileX * _tileY); ++k)
		{
			// y값이 다를 떄
			if (_vIsoTiles[k - 1]->idY > _vIsoTiles[k]->idY)
			{
				swap(_vIsoTiles[k - 1], _vIsoTiles[k]);
			}
			// 같을 때
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
		_currentBgm = "필드_낮";
		load("tutorialMap01");
		break;
	case MAP_TUTORIAL02:
		_currentBgm = "필드_밤";
		load("tutorialMap02");
		break;
	case MAP_TOWN:
		_currentBgm = "마을_낮";
		load("townMap");
		break;
	case MAP_FIELD:
		_currentBgm = "마을_밤";
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
	// a star -> 못가는 곳이면 안뱉어
	// 엔피시 에너미 체크 -> 아니면 맵피킹 -> 피킹된 맵의 인덱스와 현재 플레이어의 인덱스를 알아야 함
	// 
	// 이거 매개 변수없어도 상관이 없으니 함수 수정.
	if (isPickTile())
	{
		// 엔피씨나 에너미 클릭 - > 엔피시나 에너미기 피킹되면 자신의 좌표를 맵에 보내준다.
		// 플레이어 위치와 타겟의 위치(마우스피킹이나 에너미 좌표)
		// 피킹을 했을때 현재 타일위치와 피킹된 타일위치가 다르면 에이스타 
		// 적용해서 타일 중심점 기준으로 이동 같으면 좌표 이동
		// 
		// 
		// 
		if (_currentTileX == _targetTileX && _currentTileY == _targetTileY) return true;

		_ast->setTile(_currentTileX, _currentTileY, _targetTileX, _targetTileY);
		_vPath = _ast->pathFinder(_ast->getCurrentTile());
		
		// wall 을 클릭했을때 새로운 end좌표를 구한뒤 그걸 다시 target으로 지정
		
		_player->setTarget(getTile(_vPath[0])->center.x, getTile(_vPath[0])->center.y);

		// 벡터가 거꾸로 담겨 있으므로 재 정렬을 해줘요.

		vector<int> vTempPath;

		for (int i = 0; i < _vPath.size(); ++i)
		{
			int tempPath = _vPath[_vPath.size() - (i+1)];
			// 여기서 한번 더 예외처리를 해준다.
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


		// 플레이어의 타일 인덱스를 알아낸다.

		// 타일의 시작 좌표를 알면 현재 마우스 좌표의 대략적인 타일 index를 알수 있다.
		int playerIndexSub = (_player->getX() - _vIsoTiles[0]->center.x) / (_width / 2); // 차
		int playerIndexSum = (_player->getY() - _vIsoTiles[0]->center.y) / (_height / 2); // 합

		int playerIndexX = (playerIndexSum + playerIndexSub) / 2;
		int playerIndexY = (playerIndexSum - playerIndexSub) / 2;

		for (int y = playerIndexY - 3; y < playerIndexY + 3; ++y)
		{
			if (y < 0) continue;
			for (int x = playerIndexX - 3; x < playerIndexX + 3; ++x)
			{
				if (x < 0) continue;

				// 선형 방정식 (y-b) = m(x-a);  / 기울기
				// _ptMouse.y - 꼭지점y = 기울기 * (_ptMouse.x - 꼭지점x)
				// 왼쪽, 오른쪽 꼭지점을 구한다.

				// 선형 방정식 (y-b) = -m(x-a);  \(역슬래시) 기울기
				// _ptMouse.y - 꼭지점y = -기울기 * (_ptMouse.x - 꼭지점x)
				// 위, 아래 꼭지점을 구한다.

				// 기울기는 공통

				float isoWid = _width;
				float isoHei = _height;

				float grade = (float)(_height / 2) / (_width / 2);

				float centerX = _vIsoTiles[y * _tileX + x]->center.x;
				float centerY = _vIsoTiles[y * _tileX + x]->center.y;


				// 1. 실제 좌표와 마우스 포인터 + 포커스 보정 비교
				// 2. 실제 좌표에서 포커스 보정 후 마우스 포인터 비교
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

	// 타겟의 타일 인덱스를 알아낸다.

	// 타일의 시작 좌표를 알면 현재 마우스 좌표의 대략적인 타일 index를 알수 있다.
	int targetIndexSub = (targetX - _vIsoTiles[0]->center.x) / (_width / 2); // 차
	int targetIndexSum = (targetY - _vIsoTiles[0]->center.y) / (_height / 2); // 합

	int targetIndexX = (targetIndexSum + targetIndexSub) / 2;
	int targetIndexY = (targetIndexSum - targetIndexSub) / 2;

	for (int y = targetIndexY - 3; y < targetIndexY + 3; ++y)
	{
		if (y < 0) continue;
		for (int x = targetIndexX - 3; x < targetIndexX + 3; ++x)
		{
			if (x < 0) continue;

			// 선형 방정식 (y-b) = m(x-a);  / 기울기
			// _ptMouse.y - 꼭지점y = 기울기 * (_ptMouse.x - 꼭지점x)
			// 왼쪽, 오른쪽 꼭지점을 구한다.

			// 선형 방정식 (y-b) = -m(x-a);  \(역슬래시) 기울기
			// _ptMouse.y - 꼭지점y = -기울기 * (_ptMouse.x - 꼭지점x)
			// 위, 아래 꼭지점을 구한다.

			// 기울기는 공통

			float isoWid = _width;
			float isoHei = _height;

			float grade = (float)(_height / 2) / (_width / 2);

			float centerX = _vIsoTiles[y * _tileX + x]->center.x;
			float centerY = _vIsoTiles[y * _tileX + x]->center.y;


			// 1. 실제 좌표와 마우스 포인터 + 포커스 보정 비교
			// 2. 실제 좌표에서 포커스 보정 후 마우스 포인터 비교
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
	// 플레이어의 타일 인덱스를 알아낸다.

	// 타일의 시작 좌표를 알면 현재 마우스 좌표의 대략적인 타일 index를 알수 있다.
	int playerIndexSub = (_player->getX() - _vIsoTiles[0]->center.x) / (_width / 2); // 차
	int playerIndexSum = (_player->getY() - _vIsoTiles[0]->center.y) / (_height / 2); // 합

	int playerIndexX = (playerIndexSum + playerIndexSub) / 2;
	int playerIndexY = (playerIndexSum - playerIndexSub) / 2;

	for (int y = playerIndexY - 3; y < playerIndexY + 3; ++y)
	{
		if (y < 0) continue;
		for (int x = playerIndexX - 3; x < playerIndexX + 3; ++x)
		{
			if (x < 0) continue;

			// 선형 방정식 (y-b) = m(x-a);  / 기울기
			// _ptMouse.y - 꼭지점y = 기울기 * (_ptMouse.x - 꼭지점x)
			// 왼쪽, 오른쪽 꼭지점을 구한다.

			// 선형 방정식 (y-b) = -m(x-a);  \(역슬래시) 기울기
			// _ptMouse.y - 꼭지점y = -기울기 * (_ptMouse.x - 꼭지점x)
			// 위, 아래 꼭지점을 구한다.

			// 기울기는 공통

			float isoWid = _width;
			float isoHei = _height;

			float grade = (float)(_height / 2) / (_width / 2);

			float centerX = _vIsoTiles[y * _tileX + x]->center.x;
			float centerY = _vIsoTiles[y * _tileX + x]->center.y;


			// 1. 실제 좌표와 마우스 포인터 + 포커스 보정 비교
			// 2. 실제 좌표에서 포커스 보정 후 마우스 포인터 비교
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

	// 피킹한 곳의 타일 인덱스를 알아낸다.

	// 타일의 시작 좌표를 알면 현재 마우스 좌표의 대략적인 타일 index를 알수 있다.
	int indexSub = ((_ptMouse.x + _focus.left) - _vIsoTiles[0]->center.x) / (_width / 2); // 차
	int indexSum = ((_ptMouse.y + _focus.top) - _vIsoTiles[0]->center.y) / (_height / 2); // 합

	int indexX = (indexSum + indexSub) / 2;
	int indexY = (indexSum - indexSub) / 2;

	for (int y = indexY - 3; y < indexY + 3; ++y)
	{
		if (y < 0) continue;
		for (int x = indexX - 3; x < indexX + 3; ++x)
		{
			if (x < 0) continue;

			// 선형 방정식 (y-b) = m(x-a);  / 기울기
			// _ptMouse.y - 꼭지점y = 기울기 * (_ptMouse.x - 꼭지점x)
			// 왼쪽, 오른쪽 꼭지점을 구한다.

			// 선형 방정식 (y-b) = -m(x-a);  \(역슬래시) 기울기
			// _ptMouse.y - 꼭지점y = -기울기 * (_ptMouse.x - 꼭지점x)
			// 위, 아래 꼭지점을 구한다.

			// 기울기는 공통

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

