#pragma once
#include "gameNode.h"
#include "maptool.h"

struct tagIsoTile
{
	POINT center;
	RECT rc;

	int idX, idY;

	tagIsoTile* parentNode = NULL;

	float totalCost;		//F
	float costFromStart;	//G
	float costToGoal;		//H
				
	bool isOpen;			// ������ ������ �Ǵ�.

	DWORD attribute;
};

class maptoolScene : public gameNode
{
private:
	maptool* _maptool;


public:
	maptoolScene();
	~maptoolScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

