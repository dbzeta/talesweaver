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

	// UI�Ŵ������� �����ϴ� Ŭ������ ��Ƴ��� ����

	vector<uiScreen*> _vUiScreen;			// ��ɵ� ��� ���� ����

	// UI�Ŵ������� ���Ǵ� ��ư ��

	tagButton _identityBtn;					// ĳ���� ����â ��ư
	tagButton _comboBtn;					// �޺���ư
	tagButton _equipBtn;					// ���â ��ư
	tagButton _skillBtn;					// ��ųâ ��ư
	tagButton _inventoryBtn;				// �κ��丮â ��ư
	tagButton _questBtn;					// ����Ʈâ ��ư
	tagButton _menuBtn;						// �޴�â ��ư
	tagButton _showBtn;						// �����ֱ� ��ư
	tagButton _hideBtn;						// ����� ��ư

	bool _isShow;							// ������ ��ưâ ��������� ��Ÿ��������

	// UI�Ŵ������� �����ϴ� Ŭ���� ��
	
	quickSlot* _quickSlot;							// �� ����;
	combo* _combo;									// �޺�â
	skillScreen* _skill;							// ��ųâ
	inventory* _inventory;							// �κ��丮â
	questScreen* _quest;							// ����Ʈâ
	menu* _menu;									// ESC������ ������ �޴���ââ
	status* _identity;								// ĳ���� ����â
	equipment* _equipment;							// ���â
	storeScreen* _storeScreen;						// ����â
	statusInfomation* _statusInfomation;			// ��������â

public:
	uiManager();
	~uiManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setUi();
	void setBtn();

	void pushButton();				// Ű���� ������ ��

	bool isDoubleClick();			// ���콺 double Ŭ������ ��
	bool isOnceClick();				// ���콺 Once Ŭ������ ��
	bool isOnceClickUp();			// ���콺 Once Ŭ������ ��
	bool isStayClick();				// ���콺 stay Ŭ������ ��


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

