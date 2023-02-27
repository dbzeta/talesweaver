#pragma once
#include "item.h"

class consumptionItem :	public item
{
private:

public:
	consumptionItem();
	~consumptionItem();

	HRESULT init();
	void release();
	void update();
	void render();
};

