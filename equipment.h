#pragma once
#include "uiScreen.h"

#define MAXEQUIPMENTITEM 13


struct tagEquipmentScreenItem
{
	RECT boxRc;							// ������ ĭ ��Ʈ
	int boxNum;							// ������ ĭ ��ȣ
	int itemNum = 0;					// ������ �ѹ�
	bool isUseBox = false;				// ĭ�� ��� ���ΰ�
};

class player;
class itemManager;

class equipment : public uiScreen
{
private:
	player* _player;
	itemManager* _im;

	tagEquipmentScreenItem _arrEquipmentItemList[MAXEQUIPMENTITEM];

public:
	equipment();
	~equipment();

	HRESULT init();
	void release();
	void update();
	void render();

	void updateEquipmentItem();

	bool isDoubleClick();								// Double
	bool isOnceClick();									// Once Down
	bool isStayClick() { return false; }				// Stay 
	bool isOnceClickUp() { return false; }				// Once Up

	void setPlayerAddressLink(player* player) { _player = player; }
	void setImAddressLink(itemManager* im) { _im = im; }


};	

