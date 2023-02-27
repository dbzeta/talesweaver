#pragma once
#include "gameNode.h"

struct tagHintingQuest
{
	int enemyNum;							// 에너미 넘버
	int requireHuntingEnemyNum;				// 필요한 에너미 수
};

class enemyManager;

class quest : public gameNode
{
protected:
	char _questContent[1024];				// 퀘스트 내용

	int _questNum;							// 퀘스트 넘버
	int _requireLevel;						// 요구 레벨

	int _npcNum;							// 퀘스트를 주는 npc

	int _rewardItemNum;						// 보상 아이템 넘버
	int _rewardExp;							// 보상 경험치

	bool _isRepeatQuest;					// 반복 퀘스트인가?
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

