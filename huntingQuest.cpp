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


// �÷��̾ ���ʹ� ���� -> ���ʹ̿� �������� �� -> ���ʹ��� ����ü���� 0�� �Ǹ� ���ʹ� ����

// (isLive�� ���ʹ̰� �׾����� �Ǻ� ( �޸� Ǯ�� �����ؼ� �޸𸮴� ��� ���ܵΰ� ������ ���Ǹ� �ٲ㼭 ��ȯ���ش�.)

// �¶��� ���ӿ��� �� ���Ͱ� �������� �׾����� ��� �Ǻ��� �ϴ���?

// 