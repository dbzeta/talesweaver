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
	//Ÿ�� ���� ���� ��
	vector<tile*> _vTotalList;
	vector<tile*>::iterator _viTotalList;

	//���� �ִ� Ÿ�� ���� ��
	vector<tile*> _vOpenList;
	vector<tile*>::iterator _viOpenList;

	//������ �� ���� ��
	vector<tile*> _vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile;		// ���� Ÿ��
	tile* _endTile;			// �� Ÿ��
	tile* _currentTile;		// ���� Ÿ��

	bool _isStart;

	vector<int> _vPath;		// ����� �ε����� ������ �� ����

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

