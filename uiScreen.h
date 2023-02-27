#pragma once
#include "gameNode.h"

class uiScreen : public gameNode
{ 
protected:
	image* _background;				// 창 이미지
	RECT _rc;						// 창 RECT 값

	int _divisionX, _divisionY;		// 마우스 클릭 시 현재 마우스 좌표를 알기위해 사용 ( 한번 클릭했을 때 한번만 사용 )
	RECT _tempRc;					// 마우스 클릭 시 현재 RC값을 알기위해 사용

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

