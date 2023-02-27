#pragma once
#include "gameNode.h"
#include "huntingQuest.h"

class enemyManager;

class questManager : public gameNode
{
private:
	vector<quest*> _vTotalQuestList;

	enemyManager* _em;

public:
	questManager();
	~questManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setEmAddressLink(enemyManager* em) { _em = em; }

};

