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

	tagTabButton* _purchaseBtn;										// 구입버튼
	tagTabButton* _saleBtn;											// 판매버튼
	tagButton _closeBtn;											// 나가기버튼
	tagButton _buyBtn;												// 결제 버튼


	vector<tagTabButton*> _vTabButton;						

	vector<int> _vSellingItemList;									// 판매하는 아이템의 num
	
	vector<tagStoreItem> _vStoreItem;								// 판매하는 아이템들 담아놓을 벡터

	vector<int> _vBuyingItemList;									// 구매하려는 아이템의 num

	int _paymentMoney;												// 결제 금액 ( 플레이어가 사려는 아이템의 총 금액 )

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

