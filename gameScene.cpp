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
	//_image = IMAGEMANAGER->addPngFrameImage("�̵�������", "�̵�������.png", 15416, 201, 82, 1, false, false);
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



	// ���Ӿ����� ���� ������
	// ���� Ŭ�� �Ǻ��� ���
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
			// ����Ŭ��
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


	// ���� Ŭ�� �ʱ�ȭ
	if(_doubleClickCount > 25)
	{
		_startDoubleCount = false;
		_doubleClickCount = 0;
	}

	EFFECTMANAGER->update();

}

void gameScene::render()
{
	// �����۸Ŵ����� ����Ʈ�Ŵ����� ��� ������ ���ְ� ������ �����ش�.
	_im->render();
	_qm->render();

	// ��
	_mm->render();
	
	// ����� ��Ʈ
	_player->render();
	_em->render();
	_nm->render();

	// z ����
	DRAWMANAGER->render(getMemDC());

	// ����Ʈ
	EFFECTMANAGER->render();

	// UI�Ŵ����� ��� ������ �������� ������ ���־�� �Ѵ�.
	_um->render();

}
