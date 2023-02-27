#pragma once
#include "gameNode.h"
#include "progressBar.h"

//====================================
// ## 17. 05. 11 ## Loa(r)d of Moon ##
//====================================

enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,
	LOAD_KIND_IMAGE_1,
	LOAD_KIND_IMAGE_2,		// png
	LOAD_KIND_FRAMEIMAGE_0,
	LOAD_KIND_FRAMEIMAGE_1, // png
	LOAD_KIND_EFFECTIMAGE_0, // png
	LOAD_KIND_SOUND,
	LOAD_KIND_END
};

struct tagImageResource
{
	string keyName;			//이미지 키 값
	const char* fileName;	//파일이름
	float x, y;				//좌표
	int width, height;		//크기
	int frameX, frameY;
	bool trans;
	COLORREF transColor;
};

struct tagEffectResource
{
	string keyName;					//이미지 키 값
	const char* fileName;			//파일이름
	float x, y;						//좌표
	int width, height;				//크기
	int frameWidth, frameHeight;
	int fps;
	float elapsedTime;
	int buffer;
};

struct tagSoundResource
{
	string keyName;			//이미지 키 값
	const char* fileName;	//파일이름
	bool bgm;
	bool loop;
};

class loadItem
{
private:
	LOAD_KIND _kind;
	tagImageResource _imageResource;
	tagSoundResource _soundResource;
	tagEffectResource _effectResource;

public:
	HRESULT initForImage(string keyName, int width, int height);
	HRESULT initForImage(string keyName, const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT initForPngImage(string keyName, const char* fileName, int width, int height, 
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT initForFrameImage(string keyName, const char* fileName, int width, int height,
		int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT initForPngFrameImage(string keyName, const char* fileName, int width, int height,
		int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT initForEffectImage(string keyName, const char* fileName, int width, int height,
		int frameWidth, int frameHeight, int fps, float elapsedTime, int buffer);

	HRESULT initForSound(string keyName, const char* fileName, bool bgm, bool loop);

	LOAD_KIND getLoadingKind(void) { return _kind; }

	tagImageResource getImageResource(void) { return _imageResource; }
	tagSoundResource getSoundResource(void) { return _soundResource; }
	tagEffectResource getEffectResource(void) { return _effectResource; }

	loadItem() {}
	~loadItem() {}
};

class loading : public gameNode
{
private:
	typedef vector<loadItem*> arrLoadItem;
	typedef vector<loadItem*>::iterator arrLoadItemIter;

private:
	arrLoadItem		_vLoadItem;

	image*			_background;
	progressBar*	_loadingBar;

	int _currentGauge;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void loadImage(string keyName, int width, int height);
	void loadImage(string keyName, const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE);
	void loadPngImage(string keyName, const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE);
	void loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);
	void loadPngFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);
	void loadEffectImage(string keyName, const char* fileName, int width, int height, int frameWidth, int frameHeight, int fps, float elapsedTime, int buffer);
	void loadSound(string keyName, const char* fileName, bool bgm, bool loop);

	BOOL loadingDone();

	vector<loadItem*> getLoadItem() { return _vLoadItem; }
	int getCurrentGauge() { return _currentGauge; }

	loading();
	~loading();
};

