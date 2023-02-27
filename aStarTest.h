#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>

#define TILEWIDTH 32
#define TILEHEIGHT 32

#define TILENUMX ((int)(WINSIZEX / TILEWIDTH))
#define TILENUMY ((int)(WINSIZEY / TILEHEIGHT))

class aStarTest : public gameNode
{
private:
	//타일 전부 담을 거
	vector<tile*> _vTotalList;
	vector<tile*>::iterator _viTotalList;

	//갈수 있는 타일 담을 거
	vector<tile*> _vOpenList;
	vector<tile*>::iterator _viOpenList;

	//지나온 거 담을 거
	vector<tile*> _vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile;		// 시작 타일
	tile* _endTile;			// 끝 타일
	tile* _currentTile;		// 현재 타일

	bool _isStart;

	vector<int> _vPath;		// 경로의 인덱스를 저장해 줄 벡터

	int _tileX, _tileY;
public:
	HRESULT init(int tileX, int tileY);
	void release();
	void update();
	void render();

	void setTile(int wallX, int wallY, bool isWall);
	void setTile(int startX, int startY, int endX, int endY);

	vector<int> pathFinder(tile* currentTile);

	vector<tile*> addOpenList(tile* currentTile);

	tile* getCurrentTile() { return _currentTile; }
	tile* getStartTile() { return _startTile; }
	tile* getEndTile() { return _endTile; }

	aStarTest();
	~aStarTest();
};

