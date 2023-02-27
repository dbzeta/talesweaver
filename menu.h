#pragma once
#include "uiScreen.h"

class player;

class menu : public uiScreen
{
private:
	
	player* _player;
	
	tagButton _exitGameBtn;
	tagButton _returnGameBtn;
	tagButton _settingOptionBtn;
	tagButton _goSelectCharacterBtn;
	tagButton _showUtilizationClassBtn;


public:
	menu();
	~menu();

	HRESULT init();
	void release();
	void update();
	void render();

	bool isOnceClick();									// Once
	bool isOnceClickUp();
	bool isStayClick() { return false; }				// Stay

	void setBtn();

	void setPlayerAddressLink(player* player) { _player = player; }

};

