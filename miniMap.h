#pragma once
#include "uiScreen.h"
class miniMap : public uiScreen
{
public:
	miniMap();
	~miniMap();

	HRESULT init();
	void release();
	void update();
	void render();

};

