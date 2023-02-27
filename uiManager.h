#pragma once
#include "gameNode.h"
#include <vector>
#include "quickSlot.h"
#include "skillScreen.h"
#include "inventory.h"
#include "questScreen.h"
#include "status.h"
#include "menu.h"
#include "equipment.h"
#include "storeScreen.h"
#include "statusInfomation.h"
#include "combo.h"

class player;
class enemyManager;
class itemManager;


class uiManager : public gameNode
{
private:
	player* _player; 
	enemyManager* _em;
	itemManager* _im;

	// UI매니저에서 관리하는 클래스를 담아놓을 벡터

	vector<uiScreen*> _vUiScreen;			// 기능들 담아 놓을 벡터

	// UI매니저에서 사용되는 버튼 들

	tagButton _identityBtn;					// 캐릭터 정보창 버튼
	tagButton _comboBtn;					// 콤보버튼
	tagButton _equipBtn;					// 장비창 버튼
	tagButton _skillBtn;					// 스킬창 버튼
	tagButton _inventoryBtn;				// 인벤토리창 버튼
	tagButton _questBtn;					// 퀘스트창 버튼
	tagButton _menuBtn;						// 메뉴창 버튼
	tagButton _showBtn;						// 보여주기 버튼
	tagButton _hideBtn;						// 숨기기 버튼

	bool _isShow;							// 오른쪽 버튼창 숨길것인지 나타낼것인지

	// UI매니저에서 관리하는 클래스 들
	
	quickSlot* _quickSlot;							// 퀵 슬롯;
	combo* _combo;									// 콤보창
	skillScreen* _skill;							// 스킬창
	inventory* _inventory;							// 인벤토리창
	questScreen* _quest;							// 퀘스트창
	menu* _menu;									// ESC누르면 나오는 메뉴차창창
	status* _identity;								// 캐릭터 정보창
	equipment* _equipment;							// 장비창
	storeScreen* _storeScreen;						// 상점창
	statusInfomation* _statusInfomation;			// 상태정보창

public:
	uiManager();
	~uiManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setUi();
	void setBtn();

	void pushButton();				// 키보드 눌렀을 때

	bool isDoubleClick();			// 마우스 double 클릭했을 때
	bool isOnceClick();				// 마우스 Once 클릭했을 때
	bool isOnceClickUp();			// 마우스 Once 클릭했을 때
	bool isStayClick();				// 마우스 stay 클릭했을 때


	void zOrder(uiScreen* uiScreen);

	vector<uiScreen*> getVUiScreen() { return _vUiScreen; }
	storeScreen* getStoreScreen() { return _storeScreen; }
	inventory* getInventoryScreen() { return _inventory; }
	equipment* getEquipmentScreen() { return _equipment; }
	statusInfomation* getStatusInfoScreen() { return _statusInfomation; }

	void setPlayerAddressLink(player* player) { _player = player; }
	void setImAddressLink(itemManager* im) { _im = im; }
	void setEmAddressLink(enemyManager* em) { _em = em; }


};

