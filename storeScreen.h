#pragma once
#include "uiScreen.h"

class itemManager;
class player;

struct tagStoreItem
{
	image* itemIconImage;
	RECT imageRc;
	RECT pickingRc;
	char itemName[128];
	int cost;
};

class storeScreen : public uiScreen
{
private:
	itemManager* _im;
	player* _player;

	tagTabButton* _purchaseBtn;										// ���Թ�ư
	tagTabButton* _saleBtn;											// �ǸŹ�ư
	tagButton _closeBtn;											// �������ư
	tagButton _buyBtn;												// ���� ��ư


	vector<tagTabButton*> _vTabButton;						

	vector<int> _vSellingItemList;									// �Ǹ��ϴ� �������� num
	
	vector<tagStoreItem> _vStoreItem;								// �Ǹ��ϴ� �����۵� ��Ƴ��� ����

	vector<int> _vBuyingItemList;									// �����Ϸ��� �������� num

	int _paymentMoney;												// ���� �ݾ� ( �÷��̾ ����� �������� �� �ݾ� )

	bool _isSetItem;

public:
	storeScreen();
	~storeScreen();

	HRESULT init();
	void release();
	void update();
	void render();

	void setBtn();
	void setItem();

	virtual bool isDoubleClick();								// Double
	virtual bool isOnceClick();									// Once 
	virtual bool isOnceClickUp();

	virtual bool isStayClick() { return false; };				// Stay

	void setSelliingItemList(vector<int> vSellingItem) { _vSellingItemList = vSellingItem; }
	void setIsUse(bool isUse) { _isUse = isUse; }

	void setImAddressLink(itemManager* im) { _im = im; }
	void setPlayerAddressLink(player* player) { _player = player; }

	bool getIsUse() { return _isUse; }

};

