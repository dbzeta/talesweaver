#pragma once
#include "image.h"

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

struct tagButton
{
	RECT rc;
	image* btnImage;
	int frameX, frameY;
};

struct tagTabButton
{
	RECT rc;
	image* btnImage;
	bool isClick;
	int frameX, frameY;
};

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;


	bool _isWrite;

	int _len;

protected:
	char _str[256];


public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);


	image* getBackBuffer(void) { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }
	
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	void setIsWrite(bool write) { _isWrite = write; }


	gameNode();
	virtual ~gameNode();
};

