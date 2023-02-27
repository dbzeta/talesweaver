#pragma once
#include "uiScreen.h"

class questScreen : public uiScreen
{
private:
	image* _subQuestScreen;
	RECT _subQuestScreenRc;

	tagButton _giveUpBtn;		// �����ư
	tagButton _closeBtn;		// �ݱ��ư
	tagButton _exitBtn;			// �����ư



public:
	questScreen();
	~questScreen();

	HRESULT init();
	void release();
	void update();
	void render();

	void setBtn();

	bool isOnceClick();									// Once
	bool isOnceClickUp();
	bool isStayClick() { return false; }				// Stay
};

