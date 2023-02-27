#include "stdafx.h"
#include "huntingQuest.h"
#include "enemyManager.h"

huntingQuest::huntingQuest()
{
}


huntingQuest::~huntingQuest()
{
}

HRESULT huntingQuest::init(int questNum, int requireLevel, int rewardItemNum, int rewardExp, bool isRepeat)
{
	_questNum = questNum;
	_requireLevel = requireLevel;
	_rewardItemNum = rewardItemNum;
	_rewardExp = rewardExp;
	_isRepeatQuest = isRepeat;

	_isStart = _isClear = false;

	return S_OK;
}

void huntingQuest::release()
{

}

void huntingQuest::update()
{
	if (_isStart)
	{
		countHuntingEnemy();

		if (_currentHuntingEnemyNumber >= _requireHuntingEnemyNumber)
		{
			_currentHuntingEnemyNumber = _requireHuntingEnemyNumber;
			_isClear = true;
		}
	}
}

void huntingQuest::render()
{

}

void huntingQuest::countHuntingEnemy()
{
	for (int i = 0; i < _em->getVEnemyList().size(); ++i)
	{
		if (!_em->getVEnemyList()[i]->getIsLive() && _em->getVEnemyList()[i]->getReSpawnCount() <= 1)
		{
			if (_enemyNum == _em->getVEnemyList()[i]->getEnemyNum())
			{
				_currentHuntingEnemyNumber++;
			}
		}
	}

}


// 플레이어가 에너미 공격 -> 에너미에 데미지를 줌 -> 에너미의 현재체력이 0이 되면 에너미 죽음

// (isLive로 에너미가 죽었는지 판별 ( 메모리 풀을 응용해서 메모리는 계속 남겨두고 삭제는 조건만 바꿔서 소환해준다.)

// 온라인 게임에서 이 몬스터가 누구한테 죽었는지 어떻게 판별을 하느가?

// 