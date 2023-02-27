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
	
	int _frameX, _frameY;									// ĳ���� ����â frameX,y;

	tagTabButton _statBtn;									// ĳ���� ���� ��ư
	tagTabButton _battleBtn;								// ĳ���� ��Ʋ ��ư

	tagButton _exitBtn;										// â ���� ��ư

	tagButton _levelUpBtn;									// ������ ��ư

	bool _isClick;											// Ŭ�����Դϴ�.

	tagStatusUpButton _upBtn[7];							// ����Ʈ�� �÷��� up��ư

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

