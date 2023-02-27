#pragma once
#include "gameNode.h"
#include <vector>
#include "tile.h"

#define GHOSTMAX 4

enum GHOSTDIRECTION
{
	GHOSTDIRECTION_LEFT,
	GHOSTDIRECTION_RIGHT,
	GHOSTDIRECTION_UP,
	GHOSTDIRECTION_DOWN,
};


struct tagGhost
{
	image* image;
	GHOSTDIRECTION dir;
	RECT rc;
	float cx, cy;
	float speed;
	int currentFrameX, currentFrameY;
	int count;
	int startTileIdx, endTileIdx, currentTileIdx;
	int tileX, tileY;

	int costToGoal, costFromStart;

	vector<int> vOpenList;




};

class packmanMap;
class packman;

class ghost : public gameNode
{
private:
	tagGhost _ghost[GHOSTMAX];
	
	packmanMap* _packmanMap;
	packman* _packman;


public:
	virtual HRESULT init();
	virtual void relese();
	virtual void update();
	virtual void render();

	virtual void move();

	virtual void setGhostPosition(int pos, int ghostNum);

	virtual vector<int> addOpenList(int currentTileIdx);
	virtual void pathFinder(int currentTileIdx);


	inline virtual void setPackmanMapAddressLink(packmanMap* packmanMap) { _packmanMap = packmanMap; }
	inline virtual void setPackmanAddressLink(packman* packman) { _packman = packman; }

	ghost();
	~ghost();
};

