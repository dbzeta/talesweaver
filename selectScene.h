#pragma once
#include "gameNode.h"
#include "select.h"

class selectScene : public gameNode
{
private:
	select* _select;

public:
	selectScene();
	~selectScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

