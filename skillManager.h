#pragma once
#include "gameNode.h"
#include "skills.h"

class skillManager : public gameNode
{
private:
	vector<skills*> _vTotalSkillList;


public:
	skillManager();
	~skillManager();

	HRESULT init();
	void release();
	void update();
	void render();

};

