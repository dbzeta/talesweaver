#pragma once
#include "image.h"
#include <atlcomcli.h>
#include <wincodec.h>
#include <wincodecsdk.h>

#define IfFailedThrowHR(expr) {HRESULT hr = (expr); if (FAILED(hr)) throw hr;}
#define DIB_WIDTHBYTES(bits) ((((bits) + 31)>>5)<<2)

class cPng : public image
{
public:
	typedef struct tagPngInfo
	{
		DWORD resID;
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float x;
		float y;
		int width;
		int height;

		int currentFrameX;
		int currentFrameY;
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		RECT boundingBox;

		tagPngInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0.f;
			y = 0.f;
			width = 0;
			height = 0;

			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			boundingBox = RectMake(0,0,0,0);
		}
	}PNG_INFO, *LPPNG_INFO;

private:
	//생성과 동시에 멤버이니셜라이즈로 초기화 해주는 변수들
	LPPNG_INFO		_pngInfo;		//이미지 정보
	TCHAR*			_fileName;		//이미지 경로 이름

	BLENDFUNCTION	_blendFunc;

	CComPtr<IWICBitmapDecoder> _pDecoder;
	CComPtr<IWICBitmapFrameDecode> _pFrame;
	CComPtr<IWICFormatConverter> _pConvertedFrame;

public:
	cPng();
	~cPng();
	HRESULT init(const char* fileName, int width, int height,BOOL trans,COLORREF transColor);
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY,BOOL trans,COLORREF transColor);
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor);

	//삭제
	void release();

	//그냥 렌더
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int width, int height);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY,int width, int height);

	void rotateRender(HDC hdc, float angle);
	void rotateRender(HDC hdc, int destX, int destY, float angle);
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);
	void alphaLoopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);
	void rotateFrameRender(HDC hdc, int destX, int destY, float angle);
	void rotateFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float angle);
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	void rotateAlphaRender(HDC hdc, BYTE alpha, float angle);
	void rotateAlphaRender(HDC hdc, int destX, int destY, BYTE alpha, float angle);

	void alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void rotateAlphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha, float angle);
	void rotateAlphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha, float angle);

	//프레임 렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//DC 얻어오기
	inline HDC getMemDC() { return _pngInfo->hMemDC; }

	virtual void setAlphaBlend(BOOL alpha);
	virtual void setRotate(BOOL rotate);

	//좌표 X
	inline void setX(float x) { _pngInfo->x = x; }
	inline float setX() { return _pngInfo->x; }

	//좌표 Y
	inline void setY(float y) { _pngInfo->y = y; }
	inline float getY() { return _pngInfo->y; }

	//좌표 센터
	inline void setCenter(float x, float y)
	{
		_pngInfo->x = x - (_pngInfo->width / 2);
		_pngInfo->y = y - (_pngInfo->height / 2);
	}

	//중점 X
	inline float getCenterX()
	{
		return _pngInfo->maxFrameX <= 0 ? _pngInfo->x + (_pngInfo->width / 2) :
			_pngInfo->x + (_pngInfo->frameWidth / 2);
	}

	//중점 Y
	inline float getCenterY()
	{
		return _pngInfo->maxFrameY <= 0 ? _pngInfo->y + (_pngInfo->height / 2) :
			_pngInfo->y + (_pngInfo->frameHeight / 2);
	}

	//가로 해상도
	inline int getWidth() { return _pngInfo->width; }

	//세로 해상도
	inline int getHeight() { return _pngInfo->height; }

	//바운딩 박스
	inline RECT BoundingBox()
	{
		RECT rc = {
			(int)_pngInfo->x,
			(int)_pngInfo->y,
			(int)_pngInfo->x + _pngInfo->frameWidth,
			(int)_pngInfo->y + _pngInfo->frameHeight };

		return rc;
	}

	//프레임
	inline void setFrameX(int frameX)
	{
		_pngInfo->currentFrameX = frameX;
	}

	inline void setFrameY(int frameY)
	{
		_pngInfo->currentFrameY = frameY;
		if (frameY > _pngInfo->maxFrameY)
			_pngInfo->currentFrameY = _pngInfo->maxFrameY;
	}

	inline int getMaxFrameX() { return _pngInfo->maxFrameX; }
	inline int getMaxFrameY() { return _pngInfo->maxFrameY; }

	inline int getFrameX() { return _pngInfo->currentFrameX; }
	inline int getFrameY() { return _pngInfo->currentFrameY; }

	inline int getFrameWidth() { return _pngInfo->frameWidth; }
	inline int getFrameHeight() { return _pngInfo->frameHeight; }
};