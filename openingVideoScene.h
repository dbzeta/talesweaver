#pragma once
#include "gameNode.h"
#include "openingVideo.h"

class openingVideoScene : public gameNode
{
private:
	openingVideo* _openingVideo;

public:
	openingVideoScene();
	~openingVideoScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

