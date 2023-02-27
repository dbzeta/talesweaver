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

	vector<tagIsometricTile*> _vIsoTiles;			// ���̼� Ÿ���� ��� ����

	int _tileX, _tileY;
	int _width, _height;

	int _currentX, _currentY;						// �÷��̾��� ��ġ ��ǥ
	int _targetX, _targetY;							// Ÿ�� ( ���ʹ�, ���Ǿ�, Ÿ�� �� ��ġ��ǥ )

	int _currentTileX, _currentTileY;				// �÷��̾��� Ÿ�� �ε���
	int _targetTileX, _targetTileY;					// Ÿ���� Ÿ�� �ε���

	MAP _currentMap;								// ������ map

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
	bool isPickTile(float targetX, float targetY, bool isPlayer);	// �÷��̾�� Ÿ��(���Ǿ� ���ʹ�)���� ��ŷ
	bool isPickTile();								// �÷��̾�� ���콺 �����Ͱ��� ��ŷ

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

