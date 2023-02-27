#pragma once
#include "item.h"
class etcItem : public item
{
public:
	etcItem();
	~etcItem();

	HRESULT init();
	void release();
	void update();
	void render();
};

