#pragma once
#include "gameNode.h"
#include "intro.h"

class introScene : public gameNode
{
private:
	intro* _intro;

public:
	introScene();
	~introScene();

	HRESULT init();
	void release();
	void update();
	void render();

};

