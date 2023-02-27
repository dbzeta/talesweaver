#pragma once
#include "npc.h"

class uiManager;

class wanderingCat : public npc
{
private:
	vector<int> _vOwnedItemNum;
	uiManager* _um;

public:
	wanderingCat();
	~wanderingCat();

	HRESULT init();
	void release();
	void update();
	void render();

	virtual void changeDirection(RECT playerRC);		// NPC의 경우 말을 걸경우 모습을 바꿔준다.

	virtual void setNpc(int cx, int by);
	virtual bool isOnceClick();

	void setItem();
	void showItemList();

	vector<int> getSellingItemList() { return _vOwnedItemNum; }

	void setUmAddressLink(uiManager* um) { _um = um; }

	virtual int getX() { return _cx; }
	virtual int getY() { return _by; }

};

class kanakeu : public npc
{
private:
	vector<int> _vOwnedItemNum;
	uiManager* _um;

public:
	kanakeu();
	~kanakeu();

	HRESULT init();
	void release();
	void update();
	void render();

	virtual void changeDirection(RECT playerRC);		// NPC의 경우 말을 걸경우 모습을 바꿔준다.

	virtual void setNpc(int cx, int by);
	virtual bool isOnceClick();

	void setItem();
	void showItemList();

	vector<int> getSellingItemList() { return _vOwnedItemNum; }

	void setUmAddressLink(uiManager* um) { _um = um; }

	virtual int getX() { return _cx; }
	virtual int getY() { return _by; }
};

