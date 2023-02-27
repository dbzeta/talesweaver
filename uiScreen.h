#pragma once
#include "gameNode.h"

class uiScreen : public gameNode
{ 
protected:
	image* _background;				// â �̹���
	RECT _rc;						// â RECT ��

	int _divisionX, _divisionY;		// ���콺 Ŭ�� �� ���� ���콺 ��ǥ�� �˱����� ��� ( �ѹ� Ŭ������ �� �ѹ��� ��� )
	RECT _tempRc;					// ���콺 Ŭ�� �� ���� RC���� �˱����� ���

	bool _isUse;

public:
	uiScreen();
	~uiScreen();

	HRESULT init();
	void release();
	void update();
	void render();

	void changeIsUse() { _isUse = !_isUse; }
	bool getIsUse() { return _isUse; }

	virtual bool isDoubleClick() { return false; }				// Double
	
	virtual bool isOnceClick() { return false; };				// Once 
	virtual bool isOnceClickUp() { return false; };
	
	virtual bool isStayClick()  { return false; };				// Stay

	virtual void setBtn() {};

};

