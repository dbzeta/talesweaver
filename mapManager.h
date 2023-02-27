#pragma once
#include "gameNode.h"
#include "mapNode.h"
#include "aStarTest.h"


class player;

enum MAP
{
	MAP_TUTORIAL01 = 1,
	MAP_TUTORIAL02 = 2,
	MAP_TOWN = 3,
	MAP_FIELD = 4,
	MAP_MAX,
};



class mapManager : public gameNode
{
private:
	player* _player;

	aStarTest* _ast;

	vector<int> _vPath;

	vector<tagIsometricTile*> _vIsoTiles;			// 아이소 타일이 담긴 벡터

	int _tileX, _tileY;
	int _width, _height;

	int _currentX, _currentY;						// 플레이어의 위치 좌표
	int _targetX, _targetY;							// 타겟 ( 에너미, 엔피씨, 타일 의 위치좌표 )

	int _currentTileX, _currentTileY;				// 플레이어의 타일 인덱스
	int _targetTileX, _targetTileY;					// 타겟의 타일 인덱스

	MAP _currentMap;								// 현재의 map

public:
	mapManager();
	~mapManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void load(string mapName);
	
	void changeMap(MAP map);

	bool isOnceClick();
	bool isPickTile(float targetX, float targetY, bool isPlayer);	// 플레이어와 타겟(엔피씨 에너미)간의 피킹
	bool isPickTile();								// 플레이어와 마우스 포인터간의 피킹

	void setCurrentXY(int currentX, int currentY)	{ _currentX = currentX; _currentY	= currentY; }
	void setTargetXY(int targetX, int targetY)		{ _targetX	= targetX;	_targetY	= targetY;	}

	void setPlayerAddressLink(player* player) { _player = player; }

	int getCurrentTileX() { return _currentTileX; }
	int getCurrentTileY() { return _currentTileY; }

	int getTargetTileX() { return _targetTileX; }
	int getTargetTileY() { return _targetTileY; }

	int getTileX() { return _tileX; }
	int getTileY() { return _tileY; }

	tagIsometricTile* getTile(int tileIndex) {  return _vIsoTiles[tileIndex]; }
	vector<tagIsometricTile*> getVTile() {  return _vIsoTiles; }

	aStarTest* getAstar() { return _ast; }

	MAP getCurrentMap() { return _currentMap; }

};

