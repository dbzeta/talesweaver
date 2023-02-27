#pragma once
#include "gameNode.h"

class packmanMap : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
	DWORD _attribute[TILEX * TILEY];

public:

	virtual HRESULT init();
	virtual void relese();
	virtual void update();
	virtual void render();

	virtual void load();

	inline virtual DWORD* getAttribute() { return _attribute; }
	inline virtual tagTile* getTiles() { return _tiles; }
	inline virtual void setTilesIsOpen(int tileNum, bool isOpen) { _tiles[tileNum].isOpen = isOpen; }



	packmanMap();
	~packmanMap();
};

