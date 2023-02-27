#pragma once
#include "quest.h"

class enemyManager;

class huntingQuest : public quest
{
private:
	int _enemyNum;								// 에너미 넘버
	int _requireHuntingEnemyNumber;				// 필요한 에너미 수
	int _currentHuntingEnemyNumber;				// 현재 잡은 에너미 수


public:
	huntingQuest();
	~huntingQuest();

	virtual HRESULT init(int questNum, int requireLevel, int rewardItemNum, int rewardExp, bool isRepeat);
	virtual void release();
	virtual void update();
	virtual void render();
	
	virtual void countHuntingEnemy();

	inline void setQuest(int enemyNum, int requireEnemyNum) { _enemyNum = enemyNum; _requireHuntingEnemyNumber = requireEnemyNum; }

};

