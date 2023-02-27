#pragma once
#include "item.h"

class equipmentItem : public item
{
private:

public:
	equipmentItem();
	~equipmentItem();

	HRESULT init();
	void release();
	void update();
	void render();

};

