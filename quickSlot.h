#pragma once
#include "uiScreen.h"

class quickSlot : public uiScreen
{
private:
	bool _isQuickSlot1;
	bool _isQuickSlot2;
		
public:
	quickSlot();
	~quickSlot();

	HRESULT init();
	void release();
	void update();
	void render();

	void addSkill();
	void changeQuickSlot() { _isQuickSlot1 = !_isQuickSlot1; }
	
	bool isOnceClick() { return false; }				// Once
	bool isStayClick() { return false; }				// Stay
	bool isOnceClickUp() { return false; }
};

