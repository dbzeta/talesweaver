#pragma once
#include "gameNode.h"
#include "aStarTest.h"

class aStarTestScene : public gameNode
{
private:
	aStarTest* _ast;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	aStarTestScene();
	~aStarTestScene();
};

