#include "stdafx.h"
#include "png.h"
#include "cWICImagingFactory.h"
#include <assert.h>

#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "WindowsCodecs.lib")

cPng::cPng()
	: _pngInfo(NULL)
	, _fileName(NULL)
	, _pDecoder(NULL)
	, _pFrame(NULL)
	, _pConvertedFrame(NULL)
{
}

cPng::~cPng()
{
}

HRESULT cPng::init(const char * fileName, int width, int height,BOOL trans,COLORREF transColor)
{
	//초기화가 다시 되는 것을 방지
	if (_pngInfo != NULL) release();

	IWICImagingFactory* pFactory = cWICImagingFactory::GetInstance().GetFactory();
	assert(pFactory);
	if (!pFactory)
		throw WINCODEC_ERR_NOTINITIALIZED;

	wchar_t wFileName[256];
	MultiByteToWideChar(CP_ACP, 0, fileName, -1, wFileName, sizeof(wFileName));
	IfFailedThrowHR(pFactory->CreateDecoderFromFilename(
		wFileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &_pDecoder));

	UINT nCount = 0;
	UINT nFrame = 0;
	if (SUCCEEDED(_pDecoder->GetFrameCount(&nCount)))
	{
		if (nFrame >= nCount)
			nFrame = nCount - 1;
	}
	IfFailedThrowHR(_pDecoder->GetFrame(nFrame, &_pFrame));

	IfFailedThrowHR(pFactory->CreateFormatConverter(&_pConvertedFrame));
	IfFailedThrowHR(_pConvertedFrame->Initialize(
		_pFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeCustom
	));

	if (_pConvertedFrame == nullptr)
		throw WINCODEC_ERR_WRONGSTATE;

	if (!pFactory)
		throw WINCODEC_ERR_NOTINITIALIZED;

	CComPtr<IWICBitmapScaler> pScaler = nullptr;
	IfFailedThrowHR(pFactory->CreateBitmapScaler(&pScaler));
	IfFailedThrowHR(pScaler->Initialize(_pConvertedFrame, width, height, WICBitmapInterpolationModeFant));

	BITMAPINFO bminfo;
	ZeroMemory(&bminfo, sizeof(bminfo));
	bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bminfo.bmiHeader.biWidth = width;
	bminfo.bmiHeader.biHeight = -(LONG)height;
	bminfo.bmiHeader.biPlanes = 1;
	bminfo.bmiHeader.biBitCount = 32;
	bminfo.bmiHeader.biCompression = BI_RGB;

	void* pvImageBits = nullptr;

	//DC 얻어 오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 생성
	_pngInfo = new PNG_INFO;
	_pngInfo->resID = 0;
	_pngInfo->hMemDC = CreateCompatibleDC(hdc);
	_pngInfo->hBit = CreateDIBSection(hdc, &bminfo, DIB_PAL_COLORS, &pvImageBits, NULL, 0);
	_pngInfo->hOBit = (HBITMAP)SelectObject(_pngInfo->hMemDC, _pngInfo->hBit);
	_pngInfo->width = width;
	_pngInfo->height = height;
	_pngInfo->x = 0.f;
	_pngInfo->y = 0.f;

	_pngInfo->currentFrameX = 0;
	_pngInfo->currentFrameY = 0;
	_pngInfo->frameWidth = width;
	_pngInfo->frameHeight = height;
	_pngInfo->maxFrameX = 0;
	_pngInfo->maxFrameY = 0;
	_pngInfo->boundingBox = BoundingBox();

	UINT nStride = DIB_WIDTHBYTES(width * 32);
	UINT nImage = nStride * height;
	IfFailedThrowHR(pScaler->CopyPixels(nullptr, nStride, nImage, reinterpret_cast<BYTE*>(pvImageBits)));

	int len = _tcslen(fileName);
	_fileName = new TCHAR[len + 1];
	lstrcpyn(_fileName, fileName, len + 1);

	_blendFunc.BlendOp = AC_SRC_OVER;
	_blendFunc.BlendFlags = 0;
	_blendFunc.SourceConstantAlpha = 0xff;
	_blendFunc.AlphaFormat = AC_SRC_ALPHA;

	_imageInfo = NULL;
	_blendImage = NULL;
	_rotateImage = NULL;

	_rotate = false;
	_alpha = false;

	ReleaseDC(_hWnd, hdc);

	if (_pngInfo->hBit == 0)
	{
		release();

		return E_FAIL;
	}
	return S_OK;
}

HRESULT cPng::init(const char* fileName, int width, int height, int frameX, int frameY,BOOL trans,COLORREF transColor)
{
	//초기화가 다시 되는 것을 방지
	if (_pngInfo != NULL) release();

	IWICImagingFactory* pFactory = cWICImagingFactory::GetInstance().GetFactory();
	assert(pFactory);
	if (!pFactory)
		throw WINCODEC_ERR_NOTINITIALIZED;

	wchar_t wFileName[256];
	MultiByteToWideChar(CP_ACP, 0, fileName, -1, wFileName, sizeof(wFileName));
	IfFailedThrowHR(pFactory->CreateDecoderFromFilename(
		wFileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &_pDecoder));

	UINT nCount = 0;
	UINT nFrame = 0;
	if (SUCCEEDED(_pDecoder->GetFrameCount(&nCount)))
	{
		if (nFrame >= nCount)
			nFrame = nCount - 1;
	}
	IfFailedThrowHR(_pDecoder->GetFrame(nFrame, &_pFrame));

	IfFailedThrowHR(pFactory->CreateFormatConverter(&_pConvertedFrame));
	IfFailedThrowHR(_pConvertedFrame->Initialize(
		_pFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeCustom
	));

	if (_pConvertedFrame == nullptr)
		throw WINCODEC_ERR_WRONGSTATE;

	if (!pFactory)
		throw WINCODEC_ERR_NOTINITIALIZED;

	CComPtr<IWICBitmapScaler> pScaler = nullptr;
	IfFailedThrowHR(pFactory->CreateBitmapScaler(&pScaler));
	IfFailedThrowHR(pScaler->Initialize(_pConvertedFrame, width, height, WICBitmapInterpolationModeFant));

	BITMAPINFO bminfo;
	ZeroMemory(&bminfo, sizeof(bminfo));
	bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bminfo.bmiHeader.biWidth = width;
	bminfo.bmiHeader.biHeight = -(LONG)height;
	bminfo.bmiHeader.biPlanes = 1;
	bminfo.bmiHeader.biBitCount = 32;
	bminfo.bmiHeader.biCompression = BI_RGB;

	void* pvImageBits = nullptr;

	//DC 얻어 오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 생성
	_pngInfo = new PNG_INFO;
	_pngInfo->resID = 0;
	_pngInfo->hMemDC = CreateCompatibleDC(hdc);
	_pngInfo->hBit = CreateDIBSection(hdc, &bminfo, DIB_PAL_COLORS, &pvImageBits, NULL, 0);
	_pngInfo->hOBit = (HBITMAP)SelectObject(_pngInfo->hMemDC, _pngInfo->hBit);
	_pngInfo->width = width;
	_pngInfo->height = height;
	_pngInfo->x = 0.f;
	_pngInfo->y = 0.f;

	_pngInfo->currentFrameX = 0;
	_pngInfo->currentFrameY = 0;
	_pngInfo->frameWidth = width / frameX;
	_pngInfo->frameHeight = height / frameY;
	_pngInfo->maxFrameX = frameX - 1;
	_pngInfo->maxFrameY = frameY - 1;
	_pngInfo->boundingBox = BoundingBox();
	
	UINT nStride = DIB_WIDTHBYTES(width * 32);
	UINT nImage = nStride * height;
	IfFailedThrowHR(pScaler->CopyPixels(nullptr, nStride, nImage, reinterpret_cast<BYTE*>(pvImageBits)));

	int len = _tcslen(fileName);
	_fileName = new TCHAR[len + 1];
	lstrcpyn(_fileName, fileName, len + 1);

	_blendFunc.BlendOp = AC_SRC_OVER;
	_blendFunc.BlendFlags = 0;
	_blendFunc.SourceConstantAlpha = 0xff;
	_blendFunc.AlphaFormat = AC_SRC_ALPHA;

	_imageInfo = NULL;
	_blendImage = NULL;
	_rotateImage = NULL;

	_rotate = false;
	_alpha = false;

	ReleaseDC(_hWnd, hdc);

	if (_pngInfo->hBit == 0)
	{
		release();

		return E_FAIL;
	}
	return S_OK;
}

HRESULT cPng::init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//초기화가 다시 되는 것을 방지
	if (_pngInfo != NULL) release();

	IWICImagingFactory* pFactory = cWICImagingFactory::GetInstance().GetFactory();
	assert(pFactory);
	if (!pFactory)
		throw WINCODEC_ERR_NOTINITIALIZED;

	wchar_t wFileName[256];
	MultiByteToWideChar(CP_ACP, 0, fileName, -1, wFileName, sizeof(wFileName));
	IfFailedThrowHR(pFactory->CreateDecoderFromFilename(
		wFileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &_pDecoder));

	UINT nCount = 0;
	UINT nFrame = 0;
	if (SUCCEEDED(_pDecoder->GetFrameCount(&nCount)))
	{
		if (nFrame >= nCount)
			nFrame = nCount - 1;
	}
	IfFailedThrowHR(_pDecoder->GetFrame(nFrame, &_pFrame));

	IfFailedThrowHR(pFactory->CreateFormatConverter(&_pConvertedFrame));
	IfFailedThrowHR(_pConvertedFrame->Initialize(
		_pFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeCustom
	));

	if (_pConvertedFrame == nullptr)
		throw WINCODEC_ERR_WRONGSTATE;

	if (!pFactory)
		throw WINCODEC_ERR_NOTINITIALIZED;

	CComPtr<IWICBitmapScaler> pScaler = nullptr;
	IfFailedThrowHR(pFactory->CreateBitmapScaler(&pScaler));
	IfFailedThrowHR(pScaler->Initialize(_pConvertedFrame, width, height, WICBitmapInterpolationModeFant));

	BITMAPINFO bminfo;
	ZeroMemory(&bminfo, sizeof(bminfo));
	bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bminfo.bmiHeader.biWidth = width;
	bminfo.bmiHeader.biHeight = -(LONG)height;
	bminfo.bmiHeader.biPlanes = 1;
	bminfo.bmiHeader.biBitCount = 32;
	bminfo.bmiHeader.biCompression = BI_RGB;

	void* pvImageBits = nullptr;

	//DC 얻어 오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 생성
	_pngInfo = new PNG_INFO;
	_pngInfo->resID = 0;
	_pngInfo->hMemDC = CreateCompatibleDC(hdc);
	_pngInfo->hBit = CreateDIBSection(hdc, &bminfo, DIB_PAL_COLORS, &pvImageBits, NULL, 0);
	_pngInfo->hOBit = (HBITMAP)SelectObject(_pngInfo->hMemDC, _pngInfo->hBit);
	_pngInfo->width = width;
	_pngInfo->height = height;
	_pngInfo->x = x;
	_pngInfo->y = y;

	_pngInfo->currentFrameX = 0;
	_pngInfo->currentFrameY = 0;
	_pngInfo->frameWidth = width / frameX;
	_pngInfo->frameHeight = height / frameY;
	_pngInfo->maxFrameX = frameX - 1;
	_pngInfo->maxFrameY = frameY - 1;
	_pngInfo->boundingBox = BoundingBox();

	UINT nStride = DIB_WIDTHBYTES(width * 32);
	UINT nImage = nStride * height;
	IfFailedThrowHR(pScaler->CopyPixels(nullptr, nStride, nImage, reinterpret_cast<BYTE*>(pvImageBits)));

	int len = _tcslen(fileName);
	_fileName = new TCHAR[len + 1];
	lstrcpyn(_fileName, fileName, len + 1);

	_blendFunc.BlendOp = AC_SRC_OVER;
	_blendFunc.BlendFlags = 0;
	_blendFunc.SourceConstantAlpha = 0xff;
	_blendFunc.AlphaFormat = AC_SRC_ALPHA;

	_imageInfo = NULL;
	_blendImage = NULL;
	_rotateImage = NULL;

	_rotate = false;
	_alpha = false;

	ReleaseDC(_hWnd, hdc);

	if (_pngInfo->hBit == 0)
	{
		release();

		return E_FAIL;
	}
	return S_OK;
}

//삭제
void cPng::release()
{
	if (_pngInfo)
	{
		//이미지 삭제
		SelectObject(_pngInfo->hMemDC, _pngInfo->hOBit);
		DeleteObject(_pngInfo->hBit);
		DeleteDC(_pngInfo->hMemDC);

		//포인터도 삭제
		SAFE_DELETE(_pngInfo);
		SAFE_DELETE(_fileName);
	}
	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);
		SAFE_DELETE(_blendImage);
		_alpha = false;
	}

	if (_rotateImage)
	{
		SelectObject(_rotateImage->hMemDC, _rotateImage->hOBit);
		DeleteObject(_rotateImage->hBit);
		DeleteDC(_rotateImage->hMemDC);
		SAFE_DELETE(_rotateImage);
		_rotate = false;
	}
	if (_pConvertedFrame)
	{
		_pConvertedFrame.Release();
		_pConvertedFrame = nullptr;
	}
	if (_pFrame)
	{
		_pFrame.Release();
		_pFrame = nullptr;
	}
	if (_pDecoder)
	{
		_pDecoder.Release();
		_pDecoder = nullptr;
	}
}

void cPng::render(HDC hdc)
{
	::AlphaBlend(hdc, (int)_pngInfo->x, (int)_pngInfo->y, _pngInfo->width, _pngInfo->height, _pngInfo->hMemDC, 0, 0, _pngInfo->width, _pngInfo->height, _blendFunc);
}

void cPng::render(HDC hdc, int destX, int destY)
{
	::AlphaBlend(hdc, destX, destY, _pngInfo->width, _pngInfo->height, _pngInfo->hMemDC, 0, 0, _pngInfo->width, _pngInfo->height, _blendFunc);
}

void cPng::render(HDC hdc, int destX, int destY, int sourWidth, int sourHeight)
{
	::AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _pngInfo->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
}

void cPng::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	::AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _pngInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
}

void cPng::rotateRender(HDC hdc, float angle)
{
	if (!_rotate) setRotate(TRUE);
	float centerX = _pngInfo->x + _pngInfo->width / 2;
	float centerY = _pngInfo->y + _pngInfo->height / 2;

	POINT rPoint[3];
	int dist = sqrt((_pngInfo->width / 2)*(_pngInfo->width / 2) + (_pngInfo->height / 2)*(_pngInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));
	baseAngle[1] = atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));


	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle)*dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)*dist);
	}

	::PlgBlt(_rotateImage->hMemDC, rPoint, _pngInfo->hMemDC, 0, 0, _pngInfo->width, _pngInfo->height, NULL, 0, 0);
	::AlphaBlend(hdc, centerX - _rotateImage->width/2, centerY - _rotateImage->height / 2, _rotateImage->width, _rotateImage->height, _rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, _blendFunc);
	
}

void cPng::rotateRender(HDC hdc, int destX, int destY, float angle)
{
	if (!_rotate) setRotate(TRUE);
	float centerX = destX + _pngInfo->width / 2;
	float centerY = destY + _pngInfo->height / 2;

	POINT rPoint[3];
	int dist = sqrt((_pngInfo->width / 2)*(_pngInfo->width / 2) + (_pngInfo->height / 2)*(_pngInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));
	baseAngle[1] = atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));


	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle)*dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)*dist);
	}

	::PlgBlt(_rotateImage->hMemDC, rPoint, _pngInfo->hMemDC, 0, 0, _pngInfo->width, _pngInfo->height, NULL, 0, 0);
	::AlphaBlend(hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2, _rotateImage->width, _rotateImage->height, _rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, _blendFunc);
}

void cPng::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	if (offSetX < 0) offSetX = _pngInfo->width + (offSetX % _pngInfo->width);
	if (offSetY < 0) offSetY = _pngInfo->height + (offSetY % _pngInfo->height);

	//이미지에서 그려지는 영역
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려주는 영역
	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//Y Axis
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//그려지는 이미지의 높이를 가져온다
		rcSour.top = (y + offSetY) % _pngInfo->height;
		rcSour.bottom = _pngInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		//소스의 영역이 그려주는 영역 밖으로 나가면 보정
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//나간만큼 다시 그려올려준다
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _pngInfo->width;
			rcSour.right = _pngInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left, rcSour.bottom - rcSour.top);
		}
	}
}

void cPng::alphaLoopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha)
{
	if (offSetX < 0) offSetX = _pngInfo->width + (offSetX % _pngInfo->width);
	if (offSetY < 0) offSetY = _pngInfo->height + (offSetY % _pngInfo->height);

	//이미지에서 그려지는 영역
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려주는 영역
	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//Y Axis
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//그려지는 이미지의 높이를 가져온다
		rcSour.top = (y + offSetY) % _pngInfo->height;
		rcSour.bottom = _pngInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		//소스의 영역이 그려주는 영역 밖으로 나가면 보정
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//나간만큼 다시 그려올려준다
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _pngInfo->width;
			rcSour.right = _pngInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			alphaRender(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left, rcSour.bottom - rcSour.top, alpha);
		}
	}
}

void cPng::rotateFrameRender(HDC hdc, int destX, int destY, float angle)
{
	if (!_rotate) setRotate(TRUE);
	float centerX = destX + _pngInfo->frameWidth / 2;
	float centerY = destY + _pngInfo->frameHeight / 2;

	POINT rPoint[3];
	int dist = sqrt((_pngInfo->frameWidth / 2)*(_pngInfo->frameWidth / 2) + (_pngInfo->frameHeight / 2)*(_pngInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_pngInfo->frameHeight / 2) / ((float)_pngInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_pngInfo->frameHeight / 2) / ((float)_pngInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_pngInfo->frameHeight / 2) / ((float)_pngInfo->frameWidth / 2));


	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle)*dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)*dist);
	}
	::PlgBlt(_rotateImage->hMemDC, rPoint, _pngInfo->hMemDC, _pngInfo->currentFrameX * _pngInfo->frameWidth, _pngInfo->currentFrameX * _pngInfo->frameHeight, _pngInfo->frameWidth, _pngInfo->frameHeight, NULL, 0, 0);
	::AlphaBlend(hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2, _rotateImage->width, _rotateImage->height, _rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, _blendFunc);


}

void cPng::rotateFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float angle)
{
	if (!_rotate) setRotate(TRUE);
	_pngInfo->currentFrameX = currentFrameX;
	_pngInfo->currentFrameY = currentFrameY;

	float centerX = destX + _pngInfo->frameWidth / 2;
	float centerY = destY + _pngInfo->frameHeight / 2;

	POINT rPoint[3];
	int dist = sqrt((_pngInfo->frameWidth / 2)*(_pngInfo->frameWidth / 2) + (_pngInfo->frameHeight / 2)*(_pngInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_pngInfo->frameHeight / 2) / ((float)_pngInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_pngInfo->frameHeight / 2) / ((float)_pngInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_pngInfo->frameHeight / 2) / ((float)_pngInfo->frameWidth / 2));


	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle)*dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)*dist);
	}
	
	::PlgBlt(_rotateImage->hMemDC, rPoint, _pngInfo->hMemDC, _pngInfo->currentFrameX * _pngInfo->frameWidth, _pngInfo->currentFrameX * _pngInfo->frameHeight, _pngInfo->frameWidth, _pngInfo->frameHeight, NULL, 0, 0);
	::AlphaBlend(hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2, _rotateImage->width, _rotateImage->height, _rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, _blendFunc);

}

void cPng::alphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;
	AlphaBlend(hdc, (int)_pngInfo->x, (int)_pngInfo->y, _pngInfo->width, _pngInfo->height,
		_pngInfo->hMemDC, 0, 0, _pngInfo->width, _pngInfo->height, _blendFunc);
}

void cPng::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;
	AlphaBlend(hdc, destX, destY, _pngInfo->width, _pngInfo->height,
		_pngInfo->hMemDC, 0, 0, _pngInfo->width, _pngInfo->height, _blendFunc);
}

void cPng::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;
	AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
		_pngInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
}

void cPng::rotateAlphaRender(HDC hdc, BYTE alpha, float angle)
{
	_blendFunc.SourceConstantAlpha = alpha;
	if (!_rotate) setRotate(TRUE);
	float centerX = _pngInfo->x + _pngInfo->width / 2;
	float centerY = _pngInfo->y + _pngInfo->height / 2;

	POINT rPoint[3];
	int dist = sqrt((_pngInfo->width / 2)*(_pngInfo->width / 2) + (_pngInfo->height / 2)*(_pngInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));
	baseAngle[1] = atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));


	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle)*dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)*dist);
	}

	::PlgBlt(_rotateImage->hMemDC, rPoint, _pngInfo->hMemDC, 0, 0, _pngInfo->width, _pngInfo->height, NULL, 0, 0);
	::AlphaBlend(hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2, _rotateImage->width, _rotateImage->height, _rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, _blendFunc);

}

void cPng::rotateAlphaRender(HDC hdc, int destX, int destY, BYTE alpha, float angle)
{
	_blendFunc.SourceConstantAlpha = alpha;
	if (!_rotate) setRotate(TRUE);
	float centerX = destX + _pngInfo->width / 2;
	float centerY = destY + _pngInfo->height / 2;

	POINT rPoint[3];
	int dist = sqrt((_pngInfo->width / 2)*(_pngInfo->width / 2) + (_pngInfo->height / 2)*(_pngInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));
	baseAngle[1] = atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));


	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle)*dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)*dist);
	}

	::PlgBlt(_rotateImage->hMemDC, rPoint, _pngInfo->hMemDC, 0, 0, _pngInfo->width, _pngInfo->height, NULL, 0, 0);
	::AlphaBlend(hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2, _rotateImage->width, _rotateImage->height, _rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, _blendFunc);

}

void cPng::alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;
	AlphaBlend(hdc, destX, destY, _pngInfo->frameWidth, _pngInfo->frameHeight,
		_pngInfo->hMemDC, _pngInfo->currentFrameX * _pngInfo->frameWidth, 
		_pngInfo->currentFrameY * _pngInfo->frameHeight, _pngInfo->frameWidth, _pngInfo->frameHeight, _blendFunc);
}

void cPng::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;
	_pngInfo->currentFrameX = currentFrameX;
	_pngInfo->currentFrameY = currentFrameY;
	AlphaBlend(hdc, destX, destY, _pngInfo->frameWidth, _pngInfo->frameHeight,
		_pngInfo->hMemDC, _pngInfo->currentFrameX * _pngInfo->frameWidth,
		_pngInfo->currentFrameY * _pngInfo->frameHeight, _pngInfo->frameWidth, _pngInfo->frameHeight, _blendFunc);
}

void cPng::rotateAlphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha, float angle)
{
	_blendFunc.SourceConstantAlpha = alpha;
	if (!_rotate) setRotate(TRUE);
	float centerX = destX + _pngInfo->frameWidth / 2;
	float centerY = destY + _pngInfo->frameHeight / 2;

	POINT rPoint[3];
	int dist = sqrt((_pngInfo->width / 2)*(_pngInfo->width / 2) + (_pngInfo->height / 2)*(_pngInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));
	baseAngle[1] = atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));


	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle)*dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)*dist);
	}

	::PlgBlt(_rotateImage->hMemDC, rPoint, _pngInfo->hMemDC, _pngInfo->currentFrameX*_pngInfo->frameWidth, _pngInfo->currentFrameY*_pngInfo->frameHeight, _pngInfo->frameWidth, _pngInfo->frameHeight, NULL, 0, 0);
	::AlphaBlend(hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2, _rotateImage->width, _rotateImage->height, _rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, _blendFunc);

}

void cPng::rotateAlphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha, float angle)
{
	_blendFunc.SourceConstantAlpha = alpha;
	if (!_rotate) setRotate(TRUE);
	float centerX = destX + _pngInfo->frameWidth / 2;
	float centerY = destY + _pngInfo->frameHeight / 2;

	_pngInfo->currentFrameX = currentFrameX;
	_pngInfo->currentFrameY = currentFrameY;

	POINT rPoint[3];
	int dist = sqrt((_pngInfo->width / 2)*(_pngInfo->width / 2) + (_pngInfo->height / 2)*(_pngInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));
	baseAngle[1] = atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_pngInfo->height / 2) / ((float)_pngInfo->width / 2));


	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle)*dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)*dist);
	}

	::PlgBlt(_rotateImage->hMemDC, rPoint, _pngInfo->hMemDC, _pngInfo->currentFrameX*_pngInfo->frameWidth, _pngInfo->currentFrameY*_pngInfo->frameHeight, _pngInfo->frameWidth, _pngInfo->frameHeight, NULL, 0, 0);
	::AlphaBlend(hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2, _rotateImage->width, _rotateImage->height, _rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, _blendFunc);

}

void cPng::frameRender(HDC hdc, int destX, int destY)
{
	::AlphaBlend(hdc, destX, destY, _pngInfo->frameWidth, _pngInfo->frameHeight, _pngInfo->hMemDC, _pngInfo->currentFrameX * _pngInfo->frameWidth, _pngInfo->currentFrameY * _pngInfo->frameHeight, _pngInfo->frameWidth, _pngInfo->frameHeight, _blendFunc);
}

void cPng::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_pngInfo->currentFrameX = currentFrameX;
	_pngInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _pngInfo->maxFrameX) _pngInfo->currentFrameX = _pngInfo->maxFrameX;
	if (currentFrameY > _pngInfo->maxFrameY) _pngInfo->currentFrameY = _pngInfo->maxFrameY;
	
	::AlphaBlend(hdc, destX, destY, _pngInfo->frameWidth, _pngInfo->frameHeight, _pngInfo->hMemDC, _pngInfo->currentFrameX * _pngInfo->frameWidth, _pngInfo->currentFrameY * _pngInfo->frameHeight, _pngInfo->frameWidth, _pngInfo->frameHeight, _blendFunc);
}

void cPng::setAlphaBlend(BOOL alpha)
{
	_alpha = alpha;
	if (_alpha)
	{
		if (_blendImage != NULL)
		{
			SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
			DeleteObject(_blendImage->hBit);
			DeleteDC(_blendImage->hMemDC);
			SAFE_DELETE(_blendImage);
		}

		{
			HDC hdc = GetDC(_hWnd);

			_blendImage = new IMAGE_INFO;
			
			_blendImage->loadType = LOAD_EMPTY;

			if (_rotate)
			{
				int size;
				int width = _pngInfo->frameWidth;
				int height = _pngInfo->frameHeight;

				size = sqrt(width*width + height*height) + 1;


				_blendImage->resID = 0;
				_blendImage->hMemDC = CreateCompatibleDC(hdc);
				_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
				_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
				_blendImage->width = size;
				_blendImage->height = size;
			}
			else
			{
				_blendImage->resID = 0;
				_blendImage->hMemDC = CreateCompatibleDC(hdc);
				_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _pngInfo->frameWidth, _pngInfo->frameHeight);
				_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
				_blendImage->width = _pngInfo->frameWidth;
				_blendImage->height = _pngInfo->frameHeight;
			}
		}
	}
	else
	{
		if (_blendImage != NULL)
		{
			SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
			DeleteObject(_blendImage->hBit);
			DeleteDC(_blendImage->hMemDC);
			SAFE_DELETE(_blendImage);
		}
		_blendFunc.SourceConstantAlpha = 255;
	}
}

void cPng::setRotate(BOOL rotate)
{
	if (rotate)
	{
		_rotate = rotate;
		int size;
		int width = _pngInfo->frameWidth;
		int height = _pngInfo->frameHeight;

		size = sqrt(width*width + height*height) + 1;

		HDC hdc = GetDC(_hWnd);
		_rotateImage = new IMAGE_INFO;
		_rotateImage->loadType = LOAD_EMPTY;
		_rotateImage->resID = 0;
		_rotateImage->hMemDC = CreateCompatibleDC(hdc);
		_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
		_rotateImage->width = size;
		_rotateImage->height = size;
	}
	else
	{
		if (_rotateImage != NULL)
		{
			SelectObject(_rotateImage->hMemDC, _rotateImage->hOBit);
			DeleteObject(_rotateImage->hBit);
			DeleteDC(_rotateImage->hMemDC);

			SAFE_DELETE(_rotateImage);
		}
		_rotate = rotate;
	}
}
