#pragma once
#include "uiScreen.h"

class player;

class combo : public uiScreen
{
private:
	player* _player;

	tagButton _comboBtn[3];

	image* _selectComboImage;
	RECT _stabRc;
	RECT _verticalHackRc;
	RECT _horizonHackRc;

	bool _isClickCombo1;
	bool _isClickCombo2;
	bool _isClickCombo3;
	bool _isSelectAttackType;


public:
	combo();
	~combo();

	HRESULT init();
	void release();
	void update();
	void render();

	bool isOnceClick();														// Once
	bool isOnceClickUp() { return false; };
	bool isStayClick() { return false; };									// Stay

	void setBtn();

	void setPlayerAddressLink(player* player) { _player = player; }
};

