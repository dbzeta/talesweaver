#pragma once
#include "uiScreen.h"

class questScreen : public uiScreen
{
private:
	image* _subQuestScreen;
	RECT _subQuestScreenRc;

	tagButton _giveUpBtn;		// 포기버튼
	tagButton _closeBtn;		// 닫기버튼
	tagButton _exitBtn;			// 종료버튼



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

