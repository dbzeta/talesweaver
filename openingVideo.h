#pragma once
#include "gameNode.h"
#include <Vfw.h>

#pragma comment(lib, "vfw32.lib")

class openingVideo : public gameNode
{
private:
	HWND _hWndVideo;

	int _playcount;

public:
	openingVideo();
	~openingVideo();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


};

