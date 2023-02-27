#pragma once
#include "item.h"

class eventItem : public item
{
public:
	eventItem();
	~eventItem();

	HRESULT init();
	void release();
	void update();
	void render();
};

