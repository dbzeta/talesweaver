#include "stdafx.h"
#include "loading.h"


HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	_kind = LOAD_KIND_IMAGE_0;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, int width, int height,
	BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_1;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.fileName = fileName;
	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForPngImage(string keyName, const char* fileName,	int width, int height,
	BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_2;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.fileName = fileName;
	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.fileName = fileName;
	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForPngFrameImage(string keyName, const char* fileName, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.fileName = fileName;
	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForEffectImage(string keyName, const char* fileName, int width, int height,
	int frameWidth, int frameHeight, int fps, float elaspedTime, int buffer)
{
	_kind = LOAD_KIND_EFFECTIMAGE_0;

	memset(&_effectResource, 0, sizeof(tagEffectResource));

	_effectResource.fileName = fileName;
	_effectResource.keyName = keyName;
	_effectResource.width = width;
	_effectResource.height = height;
	_effectResource.frameWidth = frameWidth;
	_effectResource.frameHeight= frameHeight;
	_effectResource.fps = fps;
	_effectResource.elapsedTime = elaspedTime;
	_effectResource.buffer = buffer;

	return S_OK;
}

HRESULT loadItem::initForSound(string keyName, const char* fileName, bool bgm, bool loop)
{
	_kind = LOAD_KIND_SOUND;

	memset(&_soundResource, 0, sizeof(tagSoundResource));

	_soundResource.fileName = fileName;
	_soundResource.keyName = keyName;
	_soundResource.bgm = bgm;
	_soundResource.loop = loop;

	return S_OK;
}





loading::loading()
{
}


loading::~loading()
{
}

HRESULT loading::init()
{
	_background = IMAGEMANAGER->addPngImage("로딩백그라운드", "image\\로딩씬\\로딩화면.png", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_loadingBar = new progressBar;
	_loadingBar->init("loadingBarTop", "loadingBarBottom", (float)WINSIZEX / 2, (float)WINSIZEY - 76, WINSIZEX, 7);
	_loadingBar->setGauge(0, 0);

	_currentGauge = 0;


	return S_OK;
}

void loading::release()
{
	SAFE_DELETE(_loadingBar);
}

void loading::update()
{
	_loadingBar->update();
}

void loading::render()
{
	_background->render(getMemDC());
	_loadingBar->render();

}


void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);

	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadPngImage(string keyName, const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForPngImage(keyName, fileName, width, height, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, frameX, frameY, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadPngFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForPngFrameImage(keyName, fileName, width, height, frameX, frameY, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadEffectImage(string keyName, const char* fileName, int width, int height, int frameWidth, int frameHeight, int fps, float elapedTime, int buffer)
{
	loadItem* item = new loadItem;
	item->initForEffectImage(keyName, fileName, width, height, frameWidth, frameHeight, fps, elapedTime, buffer);

	_vLoadItem.push_back(item);
}

void loading::loadSound(string keyName, const char* fileName, bool bgm, bool loop)
{
	loadItem* item = new loadItem;
	item->initForSound(keyName, fileName, bgm, loop);

	_vLoadItem.push_back(item);
}

//로딩하는 곳
BOOL loading::loadingDone()
{
	//로딩 하나당 게이지가 올라갈텐디 벡터사이즈보다 크다면
	//즉 로딩이 끝났다면 트루값 반환
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
	}
	break;

	case LOAD_KIND_IMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_IMAGE_2:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addPngImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addPngFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_EFFECTIMAGE_0:
	{
		tagEffectResource img = item->getEffectResource();
		EFFECTMANAGER->addEffect(img.keyName, img.fileName, img.width, img.height, img.frameWidth, img.frameHeight, img.fps, img.elapsedTime, img.buffer);
	}
	break;

	//요부분 숙제
	case LOAD_KIND_SOUND:
	{
		tagSoundResource snd = item->getSoundResource();
		SOUNDMANAGER->addSound(snd.keyName, snd.fileName, snd.bgm, snd.loop);
	}
	break;
	}

	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());

	_currentGauge++;

	return FALSE;
}
