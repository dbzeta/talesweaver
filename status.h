#pragma once
#include "uiScreen.h"

class player;

struct tagStatusUpButton
{
	bool isUse;
	image* image;
	int frameX, frameY;
	RECT rc;

};

class status :	public uiScreen
{
private:
	
	player* _player;																		
	
	int _frameX, _frameY;									// 캐릭터 정보창 frameX,y;

	tagTabButton _statBtn;									// 캐릭터 스탯 버튼
	tagTabButton _battleBtn;								// 캐릭터 배틀 버튼

	tagButton _exitBtn;										// 창 종료 버튼

	tagButton _levelUpBtn;									// 레벨업 버튼

	bool _isClick;											// 클릭중입니다.

	tagStatusUpButton _upBtn[7];							// 포인트를 올려줄 up버튼

public:
	status();
	~status();

	HRESULT init();
	void release();
	void update();
	void render();

	bool isOnceClick();									// Once
	bool isOnceClickUp();
	bool isStayClick();									// Stay

	void setBtn();

	void setPlayerAddressLink(player* player) { _player = player; }

};

