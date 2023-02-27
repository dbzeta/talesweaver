#pragma once
#include "uiScreen.h"

#define MAXEQUIPMENTITEM 13


struct tagEquipmentScreenItem
{
	RECT boxRc;							// 아이템 칸 렉트
	int boxNum;							// 아이템 칸 번호
	int itemNum = 0;					// 아이템 넘버
	bool isUseBox = false;				// 칸이 사용 중인가
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

