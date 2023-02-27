#pragma once
//======================================================
// 2017. 03. 07 ## image Class ##
//======================================================
#include "animation.h"

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		//리소스 파일
		LOAD_FILE,			//파일
		LOAD_EMPTY,
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD		resID;
		HDC			hMemDC;
		HBITMAP		hBit;
		HBITMAP		hOBit;
		float		x;
		float		y;
		int			width;
		int			height;
		int			currentFrameX;
		int			currentFrameY;
		int			maxFrameX;
		int			maxFrameY;
		int			frameWidth;
		int			frameHeight;
		BYTE		loadType;

		tagImageInfo()
		{
			resID			= 0;
			hMemDC			= NULL;
			hBit			= NULL;
			hOBit			= NULL;
			x				= 0;
			y				= 0;
			width			= 0;
			height			= 0;
			currentFrameX	= 0;
			currentFrameY	= 0;
			maxFrameX		= 0;
			maxFrameY		= 0;
			frameWidth		= 0;
			frameHeight		= 0;
			loadType		= LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

protected:
	LPIMAGE_INFO	_imageInfo;			//이미지 정보 구조체
	CHAR*			_fileName;			//파일이름
	BOOL			_trans;				//특정칼라 날릴껀지 여부
	COLORREF		_transColor;		//특정칼라 레퍼런스
	BOOL			_alpha;
	BOOL			_rotate;


	BLENDFUNCTION	_blendFunc;			//알파블렌드를 사용키위한 정보
	LPIMAGE_INFO	_blendImage;		//알파블렌드를 사용하기 위한 이미지 정보

	LPIMAGE_INFO _rotateImage; 
	
public:
	image();
	virtual ~image();


	virtual HRESULT init(int width, int height);

	virtual HRESULT init(const DWORD resID, int width, int height,
		BOOL trans, COLORREF transColor);

	virtual HRESULT init(const char* fileName, int width, int height,
		BOOL trans, COLORREF transColor);

	virtual HRESULT init(const char* fileName, float x, float y, int width, int height,
		BOOL trans, COLORREF transColor);

	virtual HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor);
	virtual HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor);

	virtual void release(void);

	virtual void setTransColor(BOOL trans, COLORREF transColor);
	virtual void setAlphaBlend(BOOL alpha);
	virtual void setRotate(BOOL rotate);

	//렌더링 함수        뿌릴 곳X좌표, 뿌릴 곳 Y좌표
	virtual void render(HDC hdc);
	virtual void render(HDC hdc, int destX, int destY);

	virtual void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	virtual void rotateRender(HDC hdc,float angle);
	virtual void rotateRender(HDC hdc, int destX, int destY,float angle);

	virtual void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	virtual void alphaLoopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);

	virtual void frameRender(HDC hdc, int destX, int destY);
	virtual void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	virtual void rotateFrameRender(HDC hdc, int destX, int destY,float angle);
	virtual void rotateFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY,float angle);

	virtual void alphaRender(HDC hdc, BYTE alpha);
	virtual void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	virtual void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	virtual void rotateAlphaRender(HDC hdc, BYTE alpha,float angle);
	virtual void rotateAlphaRender(HDC hdc, int destX, int destY, BYTE alpha,float angle);

	virtual void alphaFrameRender(HDC hdc, int destX, int destY,BYTE alpha);
	virtual void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	virtual void rotateAlphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha,float angle);
	virtual void rotateAlphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha,float angle);

	virtual void aniRender(HDC hdc, int destX, int destY, animation* ani);

	virtual void alphaAniRender(HDC hdc, int destX, int destY, animation* ani, BYTE alpha);

	virtual void rotateAniRender(HDC hdc, int destX, int destY, animation* ani, float angle);

	virtual void rotateAlphaAniRender(HDC hdc, int destX, int destY, animation* ani, BYTE alpha,float angle);

	virtual inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//======================================================
	// 여러분들이 이미지를 편하게 조작키 위한 게타,세타
	//======================================================

	virtual inline void setX(float x) { _imageInfo->x = x; }
	virtual inline float getX() { return _imageInfo->x; }

	virtual inline void setY(float y) { _imageInfo->y = y; }
	virtual inline float getY() { return _imageInfo->y; }

	virtual inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	virtual inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ?
			_imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	virtual inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ?
			_imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	
	}

	virtual inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	virtual inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	virtual inline int getWidth(void) { return _imageInfo->width; }
	virtual inline int getHeight(void) { return _imageInfo->height; }

	virtual inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	virtual inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	virtual inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	virtual inline int getFrameY(void) { return _imageInfo->currentFrameY; }

	virtual inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	virtual inline int getFrameHeight(void) { return _imageInfo->frameHeight; }
};

