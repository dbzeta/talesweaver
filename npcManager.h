#pragma once
#include "gameNode.h"
#include "merchantNpc.h"
#include "normalNpc.h"

class uiManager;
class player;
class mapManager;

class npcManager : public gameNode
{
private:
	player* _player;
	uiManager* _um;
	mapManager*_mm;

	vector<npc*> _vTotalNpcList;

	wanderingCat* _wanderingCat;			// �Ҹ�ǰ ���� 
	kanakeu* _kanakeu;						// ��� ����
	maria* _maria;							// ����Ʈ 

public:
	npcManager();
	~npcManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setPlayerAddressLink(player* player) { _player = player; }
	void setUmAddressLink(uiManager* um) { _um = um; }
	void setMmAddressLink(mapManager* mm) { _mm = mm; }

	bool isOnceClick();

	void setNpc();

	vector<npc*> getVTotalNpcList() { return _vTotalNpcList; }

};

