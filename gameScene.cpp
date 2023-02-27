#include "stdafx.h"
#include "gameScene.h"
#include "player.h"
#include "enemyManager.h"
#include "mapManager.h"

gameScene::gameScene()
{
}


gameScene::~gameScene()
{
}


HRESULT gameScene::init()
{
	//_image = IMAGEMANAGER->addPngFrameImage("이동마법진", "이동마법진.png", 15416, 201, 82, 1, false, false);
	//_frameX = _count = 0;

	_um = new uiManager;
	_um->init();

	_player = new player;
	_player->init();

	_em = new enemyManager;
	_em->init();

	_mm = new mapManager;
	_mm->init();

	_im = new itemManager;
	_im->init();

	_nm = new npcManager;
	_nm->init();

	_qm = new questManager;
	_qm->init();

	_player->setEmAddressLink(_em);
	_player->setNmAddressLink(_nm);
	_player->setMmAddressLink(_mm);
	_player->setUmAddressLink(_um);
	_player->setEmAddressLink(_im);

	_em->setPlayerAddressLink(_player);
	_em->setMmAddressLink(_mm);
	_em->setUmAddressLink(_um);

	_nm->setPlayerAddressLink(_player);
	_nm->setUmAddressLink(_um);

	_qm->setEmAddressLink(_em);

	_um->setPlayerAddressLink(_player);
	_um->setImAddressLink(_im);
	_um->setEmAddressLink(_em);

	_mm->setPlayerAddressLink(_player);


	_um->setUi();
	_player->initStatus();
	_em->setMinion();
	_nm->setNpc();



	// 게임씬에서 사용될 변수들
	// 더블 클릭 판별에 사용
	_isDoubleClick = _startDoubleCount = false;
	_doubleClickCount = 0; 



	return S_OK;
}

void gameScene::release()
{
	_player->release();
	_em->release();
	_mm->release();
	_um->release();
	_im->release();
	_nm->release();
	_qm->release();
}

void gameScene::update()
{

	if (_startDoubleCount) _doubleClickCount++;

	_mm->update();
	_um->update();
	_player->update();
	_em->update(); 
	_im->update();
	_nm->update();
	_qm->update();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_startDoubleCount)
		{
			// 더블클릭
			if (_doubleClickCount < 25)
			{
				_isDoubleClick = true;
				_startDoubleCount = false;
				_doubleClickCount = 0;

				if(_um->isDoubleClick()) return;
			}
		}
		else _startDoubleCount = true;

		if (_um->isOnceClick()) return;
		if (_player->isOnceClick()) return;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (_um->isOnceClickUp()) return;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (_um->isStayClick()) return;
	}


	// 더블 클릭 초기화
	if(_doubleClickCount > 25)
	{
		_startDoubleCount = false;
		_doubleClickCount = 0;
	}

	EFFECTMANAGER->update();

}

void gameScene::render()
{
	// 아이템매니저와 퀘스트매니저의 경우 관리만 해주고 랜더는 안해준다.
	_im->render();
	_qm->render();

	// 맵
	_mm->render();
	
	// 디버그 렉트
	_player->render();
	_em->render();
	_nm->render();

	// z 오더
	DRAWMANAGER->render(getMemDC());

	// 이펙트
	EFFECTMANAGER->render();

	// UI매니저의 경우 무조건 마지막에 랜더를 해주어야 한다.
	_um->render();

}
