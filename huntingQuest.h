#pragma once
#include "quest.h"

class enemyManager;

class huntingQuest : public quest
{
private:
	int _enemyNum;								// ���ʹ� �ѹ�
	int _requireHuntingEnemyNumber;				// �ʿ��� ���ʹ� ��
	int _currentHuntingEnemyNumber;				// ���� ���� ���ʹ� ��


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

