#pragma once
#include "uiScreen.h"

#define MAXINVENTORYBOX 64

struct tagInventoryButton
{
	RECT rc;
	image* btnImage;
	int frameX, frameY;
	bool isPicking = false;
};

struct tagInventoryItem
{
	RECT boxRc;							// ������ ĭ ��Ʈ
	int boxNum;							// ������ ĭ �ѹ� ( �������� ���° ĭ�� ����ִ��� )
	int itemNum = 0;					// ������ �ѹ�
	int itemEA	=	0;					// ������ �� ��
	bool isUseBox = false;				// ĭ�� ��� ���ΰ�
};

class player;
class itemManager;

class inventory : public uiScreen
{
private:

	player* _player;
	itemManager* _im;

	vector<tagInventoryButton*> _vTotalInventoryList;

	// ��� ���� ����
	tagInventoryButton* _totalBtn;
	tagInventoryButton* _equipBtn;
	tagInventoryButton* _consumBtn;
	tagInventoryButton* _etcBtn;
	tagInventoryButton* _eventBtn;


	// ��Ÿ ��ư
	tagButton _upBtn;								// �κ��丮 â �巡�� up
	tagButton _downBtn;								// �κ��丮 â �巡�� down
	tagButton _exitBtn;								// �κ��丮 â ����

	tagInventoryButton _dragBar;					// �κ��丮 â �巡�׹�

	RECT _tempDragBarRc;
	int _differentY;								// ��ȭ�� �巡�׹� ��ġ

	tagInventoryItem _arrInventoryItemList[MAXINVENTORYBOX];	// �������� ������ �� �ִ� ĭ �̸� ����

	int _currentBoxNum;								// ��ŷ�� �ڽ� �ѹ�
	bool _isPickingItem;							// �������� ��ŷ �Ǿ��°�?
public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();


	void setBtn();

	bool isDoubleClick();							// Double
	bool isOnceClick();								// Once
	bool isStayClick();								// Stay
	bool isOnceClickUp();

	void checkPicking();

	void setIsPicking(tagInventoryButton* pickingBtn);

	void setPlayerAddressLink(player* player) { _player = player; }
	void setImAddressLink(itemManager* im) { _im = im; }

	void addInventoryItem(int itemNum);

};

