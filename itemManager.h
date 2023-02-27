#pragma once
#include "gameNode.h"
#include "item.h"

class itemManager : public gameNode
{
private:
	vector<item*> _vItemList;
	
public:
	itemManager();
	~itemManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setItem();

	void load();
	void save();

	vector<item*>& getVItemList() { return _vItemList; }
	item* getItem(int itemNum);
	item* makeItem(int itemNum);

};

