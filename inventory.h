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
	RECT boxRc;							// 아이템 칸 렉트
	int boxNum;							// 아이템 칸 넘버 ( 아이템이 몇번째 칸에 들어있는지 )
	int itemNum = 0;					// 아이템 넘버
	int itemEA	=	0;					// 아이템 갯 수
	bool isUseBox = false;				// 칸이 사용 중인가
};

class player;
class itemManager;

class inventory : public uiScreen
{
private:

	player* _player;
	itemManager* _im;

	vector<tagInventoryButton*> _vTotalInventoryList;

	// 장비 종류 선택
	tagInventoryButton* _totalBtn;
	tagInventoryButton* _equipBtn;
	tagInventoryButton* _consumBtn;
	tagInventoryButton* _etcBtn;
	tagInventoryButton* _eventBtn;


	// 기타 버튼
	tagButton _upBtn;								// 인벤토리 창 드래그 up
	tagButton _downBtn;								// 인벤토리 창 드래그 down
	tagButton _exitBtn;								// 인벤토리 창 종료

	tagInventoryButton _dragBar;					// 인벤토리 창 드래그바

	RECT _tempDragBarRc;
	int _differentY;								// 변화된 드래그바 위치

	tagInventoryItem _arrInventoryItemList[MAXINVENTORYBOX];	// 아이템을 저장할 수 있는 칸 미리 생성

	int _currentBoxNum;								// 피킹된 박스 넘버
	bool _isPickingItem;							// 아이템이 피킹 되었는가?
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

