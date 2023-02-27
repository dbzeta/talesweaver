#pragma once
#include "gameNode.h"

struct tagHintingQuest
{
	int enemyNum;							// ���ʹ� �ѹ�
	int requireHuntingEnemyNum;				// �ʿ��� ���ʹ� ��
};

class enemyManager;

class quest : public gameNode
{
protected:
	char _questContent[1024];				// ����Ʈ ����

	int _questNum;							// ����Ʈ �ѹ�
	int _requireLevel;						// �䱸 ����

	int _npcNum;							// ����Ʈ�� �ִ� npc

	int _rewardItemNum;						// ���� ������ �ѹ�
	int _rewardExp;							// ���� ����ġ

	bool _isRepeatQuest;					// �ݺ� ����Ʈ�ΰ�?
	bool _isStart;							// 
	bool _isClear;							// 

	enemyManager* _em;						

public:
	quest();
	~quest();

	virtual HRESULT init(int questNum, int requireLevel, int rewardItemNum, int rewardExp, bool isRepeat);
	virtual void release();
	virtual void update();
	virtual void render();

	// void setQuest(int enemyNum, int requireEnemy) { _huntingQuest.enemyNum = enemyNum; _huntingQuest.requireHuntingEnemyNum = requireEnemy; }

	virtual void countHuntingEnemy() {};

	void setEmAddressLink(enemyManager* em) { _em = em; }

	bool getIsClear() { return _isClear; }

};

