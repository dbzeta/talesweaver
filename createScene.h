#pragma once
#include "gameNode.h"
#include "create.h"

class createScene : public gameNode
{
private:
	create* _create;

public:
	createScene();
	~createScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

