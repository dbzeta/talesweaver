#pragma once
#include "gameNode.h"
#include "isometricTile.h"

struct tagScreen
{
	RECT rc;
	image* screenImage;
};

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


// 선택 할 타일 및 오브젝트
struct tagSampleTile
{
	RECT rc;
	image* sampleImage;
	int frameX, frameY;
};

class maptool : public gameNode
{
private:

	vector<isometricTile*> _vIsoTile;				// iso타일을 담아 둘 벡터

	int _tileX, _tileY;								// 타일 갯수
	int _isoWidth, _isoHeight;						// 아이소타일 크기
	int _tileWidth, _tileHeight;					// 타일 크기

	tagScreen _rightUIScreen;						// 타일 및 오브젝트 등 버튼 선택 용 배경이미지
	tagScreen _leftUIScreen;						// 타일 및 오브젝트 등 버튼 선택 용 배경이미지

	vector<tagSampleTile*> _vSampleTile;			// 표시되는 타일 담아둘 벡터
	vector<tagSampleTile*> _vSampleObject;			// 표시되는 오브젝트 담아둘 벡터

	tagSampleTile* _currentPicking;					// 현재 클릭 된 타일 및 오브젝트;

	tagButton _addTileBtn, _removeTileBtn;			// 타일 추가, 감소 버튼
	tagButton _saveBtn, _loadBtn, _eraseBtn;		// 저장, 불러오기, 지우기 버튼

	tagTabButton _terrainBtn, _objectBtn;			// Terrain Object 선택 버튼
	tagButton _returnBtn;							// 메인으로 돌아가는 버튼
	

	RECT _focus;									// 포커스 ( 클리핑 검출용 카메라 렉트 )

	bool _isPickingSample;							// 마우스로 샘플 타일 및 오브젝트 눌렀을 때 true로 해준다.
	bool _isEraseObject;							// 지우기 버튼 클릭시 true로 변하며 오브젝트를 제거해준다.

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
	void selectObject(void);

	void pickingTile(int pickingIndex);
	bool isPicking(float cx, float cy);

	void save(void);
	void load(void);

};

