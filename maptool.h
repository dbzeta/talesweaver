#pragma once
#include "gameNode.h"
#include "mapNode.h"


struct tagScreen
{
	RECT rc;
	image* screenImage;
};

// ���� �� Ÿ�� �� ������Ʈ
struct tagSampleTile
{
	RECT rc;
	image* sampleImage;
	int frameX, frameY;
};


class maptool : public gameNode
{
private:

	vector<tagIsometricTile*> _vIsoTiles;			// isoŸ�� ��� �� ����

	int _tileX, _tileY;								// Ÿ�� ����
	int _isoWidth, _isoHeight;						// ���̼�Ÿ�� ũ��
	int _tileWidth, _tileHeight;					// Ÿ�� ũ��

	tagScreen _rightUIScreen;						// Ÿ�� �� ������Ʈ �� ��ư ���� �� ����̹���
	tagScreen _leftUIScreen;						// Ÿ�� �� ������Ʈ �� ��ư ���� �� ����̹���

	vector<tagSampleTile*> _vSampleTile;			// ǥ�õǴ� Ÿ�� ��Ƶ� ����
	vector<tagSampleTile*> _vSampleObject;			// ǥ�õǴ� ������Ʈ ��Ƶ� ����
	vector<tagSampleTile*> _vSampleObject2;			// ǥ�õǴ� ������Ʈ ��Ƶ� ����2

	tagSampleTile* _currentPicking;					// ���� Ŭ�� �� Ÿ�� �� ������Ʈ;

	tagButton _addTileBtn, _removeTileBtn;			// Ÿ�� �߰�, ���� ��ư
	tagButton _saveBtn, _loadBtn, _eraseBtn;		// ����, �ҷ�����, ����� ��ư

	tagTabButton _terrainBtn, _objectBtn[2];		// Terrain Object ���� ��ư
	tagButton _returnBtn;							// �������� ���ư��� ��ư
	
	// RECT _focus;									// �������� ���� �ּ�ó���� ��Ŀ�� ( Ŭ���� ����� ī�޶� ��Ʈ )

	bool _isPickingSample;							// ���콺�� ���� Ÿ�� �� ������Ʈ ������ �� true�� ���ش�.
	bool _isEraseObject;							// ����� ��ư Ŭ���� true�� ���ϸ� ������Ʈ�� �������ش�.

public:
	maptool();
	~maptool();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setSampleTileAndObject(void);
	void renderSampleTileAndObject(void);

	void setTile(void);
	void addTile(void);
	void removeTile(void);

	void checkMousePoint(void);
	void checkPushButton(void);

	void selectTerrain(void);
	void selectObject(int objectNum);

	void pickingTile(int pickingIndex);
	bool isPicking(float cx, float cy);

	void save(void);
	void load(void);

};

