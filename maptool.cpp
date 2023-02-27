#include "stdafx.h"
#include "maptool.h"


maptool::maptool()
	:_tileX(3), _tileY(3), _tileWidth(96), _tileHeight(96)
{
	_isoWidth = _tileWidth * 2;
	_isoHeight = _tileHeight;
	
}


maptool::~maptool()
{
}

HRESULT maptool::init(void)
{
	
	_currentPicking = NULL;

	_returnBtn.btnImage = IMAGEMANAGER->findImage("돌아가기버튼");
	_returnBtn.frameX = _returnBtn.frameY = 0;
	_returnBtn.rc = RectMake(50, WINSIZEY - 10 - _returnBtn.btnImage->getFrameHeight(), _returnBtn.btnImage->getFrameWidth(), _returnBtn.btnImage->getFrameHeight());

	_saveBtn.btnImage = IMAGEMANAGER->findImage("저장하기버튼");
	_saveBtn.frameX = _saveBtn.frameY = 0;
	_saveBtn.rc = RectMake(50, 320, _saveBtn.btnImage->getFrameWidth(), _saveBtn.btnImage->getFrameHeight());
	_loadBtn.btnImage = IMAGEMANAGER->findImage("불러오기버튼");
	_loadBtn.frameX = _loadBtn.frameY = 0;
	_loadBtn.rc = RectMake(50, _saveBtn.rc.bottom + 20, _loadBtn.btnImage->getFrameWidth(), _loadBtn.btnImage->getFrameHeight());
	_eraseBtn.btnImage = IMAGEMANAGER->findImage("지우기버튼");
	_eraseBtn.frameX = _eraseBtn.frameY = 0;
	_eraseBtn.rc = RectMake(50, _loadBtn.rc.bottom + 20, _loadBtn.btnImage->getFrameWidth(), _loadBtn.btnImage->getFrameHeight());

	_rightUIScreen.screenImage = IMAGEMANAGER->findImage("맵툴UI");
	_rightUIScreen.rc = RectMake(WINSIZEX - _rightUIScreen.screenImage->getWidth(), WINSIZEY - _rightUIScreen.screenImage->getHeight(), _rightUIScreen.screenImage->getFrameWidth(), _rightUIScreen.screenImage->getFrameHeight());
	_leftUIScreen.screenImage = IMAGEMANAGER->findImage("맵툴UI");
	_leftUIScreen.rc = RectMake(WINSIZEX - _rightUIScreen.screenImage->getWidth(), WINSIZEY - _rightUIScreen.screenImage->getHeight(), _rightUIScreen.screenImage->getFrameWidth(), _rightUIScreen.screenImage->getFrameHeight());

	_addTileBtn.btnImage = IMAGEMANAGER->findImage("추가버튼");
	_addTileBtn.frameX = _addTileBtn.frameY = 0;
	_addTileBtn.rc = RectMake(50, 200, _addTileBtn.btnImage->getFrameWidth(), _addTileBtn.btnImage->getFrameHeight());
	_removeTileBtn.btnImage = IMAGEMANAGER->findImage("삭제버튼");
	_removeTileBtn.frameX = _removeTileBtn.frameY = 0; 
	_removeTileBtn.rc = RectMake(50, 270, _removeTileBtn.btnImage->getFrameWidth(), _removeTileBtn.btnImage->getFrameHeight());

	_terrainBtn.btnImage = IMAGEMANAGER->findImage("타일버튼");
	_terrainBtn.frameX = _terrainBtn.frameY = 0;
	_terrainBtn.rc = RectMake(WINSIZEX - 244, 276, _terrainBtn.btnImage->getFrameWidth(), _terrainBtn.btnImage->getFrameHeight());
	_terrainBtn.isClick = true;
	
	for (int i = 0; i < 2; ++i)
	{
		_objectBtn[i].btnImage = IMAGEMANAGER->findImage("오브젝트버튼");
		_objectBtn[i].frameX = 1;
		_objectBtn[i].frameY = 0;
		_objectBtn[i].rc = RectMake(WINSIZEX - 244 + _terrainBtn.btnImage->getFrameWidth() * (i+1), 276, _objectBtn[i].btnImage->getFrameWidth(), _objectBtn[i].btnImage->getFrameHeight());
		_objectBtn[i].isClick = false;
	}

	_focus = RectMake(0, 0, WINSIZEX, WINSIZEY);
	_isPickingSample = _isEraseObject = false;

	setTile();
	setSampleTileAndObject();

	return S_OK;

}

void maptool::release(void)
{
}

void maptool::update(void)
{
	checkMousePoint();
	checkPushButton();


}

void maptool::render(void)
{
	if (_debug)	Rectangle(getMemDC(), _focus.left, _focus.top, _focus.right, _focus.bottom);

	for (int i = 0; i < _vIsoTiles.size(); ++i)
	{
		// 클리핑 기법을 사용하여 화면에 안보이는 애들은 랜더를 안해준다
		RECT temp;
		// 포커스의 rect와 타일의 rect를 비교하여 교차하는 부분이 없을경우 continue로 넘겨주어 랜더를 안해준다.
		if (!IntersectRect(&temp, &_focus, &_vIsoTiles[i]->rc)) continue;

		// 화면에 보여지는 타일의 실제 좌표는 고정이고 추가된 포커스 좌표에 따라 보여진다.
		if (_vIsoTiles[i]->terrain == TR_NONE)
		{
			LineMake(getMemDC(), _vIsoTiles[i]->center.x - _focus.left, _vIsoTiles[i]->center.y - _focus.top - _vIsoTiles[i]->height / 2,
				_vIsoTiles[i]->center.x - _vIsoTiles[i]->width / 2 - _focus.left, _vIsoTiles[i]->center.y - _focus.top);
			LineMake(getMemDC(), _vIsoTiles[i]->center.x - _focus.left, _vIsoTiles[i]->center.y - _focus.top - _vIsoTiles[i]->height / 2,
				_vIsoTiles[i]->center.x + _vIsoTiles[i]->width / 2 - _focus.left, _vIsoTiles[i]->center.y - _focus.top);
			LineMake(getMemDC(), _vIsoTiles[i]->center.x - _vIsoTiles[i]->width / 2 - _focus.left, _vIsoTiles[i]->center.y - _focus.top,
				_vIsoTiles[i]->center.x - _focus.left, _vIsoTiles[i]->center.y + _vIsoTiles[i]->height / 2 - _focus.top);
			LineMake(getMemDC(), _vIsoTiles[i]->center.x + _vIsoTiles[i]->width / 2 - _focus.left, _vIsoTiles[i]->center.y - _focus.top,
				_vIsoTiles[i]->center.x - _focus.left, _vIsoTiles[i]->center.y + _vIsoTiles[i]->height / 2 - _focus.top);
		}
		else
		{
			IMAGEMANAGER->findImage("기본타일")->frameRender(getMemDC(), _vIsoTiles[i]->rc.left - _focus.left, _vIsoTiles[i]->rc.top - _focus.top, _vIsoTiles[i]->terrainFrameX, _vIsoTiles[i]->terrainFrameY);
		}

		if (_debug)
		{
			Rectangle(getMemDC(), _vIsoTiles[i]->rc.left, _vIsoTiles[i]->rc.top, _vIsoTiles[i]->rc.right, _vIsoTiles[i]->rc.bottom);
		}

	}

	for (int i = 0; i < _vIsoTiles.size(); ++i)
	{
		// 클리핑 기법을 사용하여 화면에 안보이는 애들은 랜더 안해
		RECT temp;

		image* objImage;

		if (_vIsoTiles[i]->obj == OBJ_WALL) objImage = IMAGEMANAGER->findImage("기본오브젝트");
		else if (_vIsoTiles[i]->obj == OBJ_FLAG) objImage = IMAGEMANAGER->findImage("기본오브젝트2");
		else if (_vIsoTiles[i]->obj == OBJ_NONE) continue;

		RECT objRect = RectMake(_vIsoTiles[i]->rc.left, _vIsoTiles[i]->rc.top - objImage->getFrameHeight() + IMAGEMANAGER->findImage("기본타일")->getFrameHeight(),
			objImage->getFrameWidth(), objImage->getFrameHeight());

		if (!IntersectRect(&temp, &_focus, &objRect)) continue;

		if (_vIsoTiles[i]->obj == OBJ_WALL)
		{
			objImage->frameRender(getMemDC(), _vIsoTiles[i]->rc.left - _focus.left,
				_vIsoTiles[i]->rc.top - objImage->getFrameHeight() + IMAGEMANAGER->findImage("기본타일")->getFrameHeight() - _focus.top,
				_vIsoTiles[i]->objFrameX, _vIsoTiles[i]->objFrameY);
		}
		else if (_vIsoTiles[i]->obj == OBJ_FLAG)
		{
			objImage->frameRender(getMemDC(), _vIsoTiles[i]->rc.left - _focus.left, _vIsoTiles[i]->rc.top - _focus.top,
				_vIsoTiles[i]->objFrameX, _vIsoTiles[i]->objFrameY);
		}
		if (_debug)
		{
			Rectangle(getMemDC(), objRect.left, objRect.top, objRect.right, objRect.bottom);
		}
	}

	// 버튼
	_addTileBtn.btnImage->frameRender(getMemDC(), _addTileBtn.rc.left, _addTileBtn.rc.top, _addTileBtn.frameX, _addTileBtn.frameY);
	_removeTileBtn.btnImage->frameRender(getMemDC(), _removeTileBtn.rc.left, _removeTileBtn.rc.top, _removeTileBtn.frameX, _removeTileBtn.frameY);

	_saveBtn.btnImage->frameRender(getMemDC(), _saveBtn.rc.left, _saveBtn.rc.top, _saveBtn.frameX, _saveBtn.frameY);
	_loadBtn.btnImage->frameRender(getMemDC(), _loadBtn.rc.left, _loadBtn.rc.top, _loadBtn.frameX, _loadBtn.frameY);
	_eraseBtn.btnImage->frameRender(getMemDC(), _eraseBtn.rc.left, _eraseBtn.rc.top, _eraseBtn.frameX, _eraseBtn.frameY);
	_returnBtn.btnImage->frameRender(getMemDC(), _returnBtn.rc.left, _returnBtn.rc.top, _returnBtn.frameX, _returnBtn.frameY);

	// 샘플 타일 및 오브젝트 클릭시 마우스 포인터에 랜더되는 이미지
	if (_isPickingSample) _currentPicking->sampleImage->frameRender(getMemDC(), 
		_ptMouse.x - _currentPicking->sampleImage->getFrameWidth() / 2, 
		_ptMouse.y - _currentPicking->sampleImage->getFrameHeight() / 2, 
		_currentPicking->frameX, _currentPicking->frameY);
	else if (_isEraseObject) IMAGEMANAGER->findImage("지우개")->render(getMemDC(),
		_ptMouse.x - IMAGEMANAGER->findImage("지우개")->getWidth() / 2,
		_ptMouse.y - IMAGEMANAGER->findImage("지우개")->getHeight() / 2);

	// 타일 창
	_rightUIScreen.screenImage->render(getMemDC(), _rightUIScreen.rc.left, _rightUIScreen.rc.top);

	// 타일 & 오브젝트 탭 버튼
	_terrainBtn.btnImage->frameRender(getMemDC(), _terrainBtn.rc.left, _terrainBtn.rc.top, _terrainBtn.frameX, _terrainBtn.frameY);
	_objectBtn[0].btnImage->frameRender(getMemDC(), _objectBtn[0].rc.left, _objectBtn[0].rc.top, _objectBtn[0].frameX, _objectBtn[0].frameY);
	_objectBtn[1].btnImage->frameRender(getMemDC(), _objectBtn[1].rc.left, _objectBtn[1].rc.top, _objectBtn[1].frameX, _objectBtn[1].frameY);

	// 타일 & 오브젝트 이미지
	renderSampleTileAndObject();

}

void maptool::setSampleTileAndObject(void)
{
	image* sampleImage = IMAGEMANAGER->findImage("샘플타일");
	int sampleTileX = sampleImage->getMaxFrameX() + 1;
	int sampleTileY = sampleImage->getMaxFrameY() + 1;

	int sampleX, sampleY = 0;
	for (int y = 0; y < sampleTileY; ++y)
	{
		sampleX = 0;
		
		for (int x = 0; x < sampleTileX; ++x)
		{
			SetRect(&_vSampleTile[y * sampleTileX + x]->rc,
				(sampleX * sampleImage->getFrameWidth()) + _terrainBtn.rc.left + 15,
				(sampleY * sampleImage->getFrameHeight()) + _terrainBtn.rc.bottom + 50,
				(sampleX * sampleImage->getFrameWidth()) + _terrainBtn.rc.left + 15 + sampleImage->getFrameWidth(),
				(sampleY * sampleImage->getFrameHeight()) + _terrainBtn.rc.bottom + 50 + sampleImage->getFrameHeight());

			_vSampleTile[y * sampleTileX + x]->frameX = x;
			_vSampleTile[y * sampleTileX + x]->frameY = y;

			sampleX++;
		}

		sampleY++;
	}

	sampleImage = IMAGEMANAGER->findImage("샘플오브젝트");
	sampleTileX = sampleImage->getMaxFrameX() + 1;
	sampleTileY = sampleImage->getMaxFrameY() + 1;

	sampleX, sampleY = 0;
	for (int y = 0; y < sampleTileY; ++y)
	{
		sampleX = 0;

		for (int x = 0; x < sampleTileX; ++x)
		{
			SetRect(&_vSampleObject[y * sampleTileX + x]->rc,
				(sampleX * sampleImage->getFrameWidth()) + _terrainBtn.rc.left + 15,
				(sampleY * sampleImage->getFrameHeight()) + _terrainBtn.rc.bottom + 50,
				(sampleX * sampleImage->getFrameWidth()) + _terrainBtn.rc.left + 15 + sampleImage->getFrameWidth(),
				(sampleY * sampleImage->getFrameHeight()) + _terrainBtn.rc.bottom + 50 + sampleImage->getFrameHeight());

			_vSampleObject[y * sampleTileX + x]->frameX = x;
			_vSampleObject[y * sampleTileX + x]->frameY = y;

			sampleX++;
		}

		sampleY++;
	}

	sampleImage = IMAGEMANAGER->findImage("샘플오브젝트2");
	sampleTileX = sampleImage->getMaxFrameX() + 1;
	sampleTileY = sampleImage->getMaxFrameY() + 1;

	sampleX, sampleY = 0;
	for (int y = 0; y < sampleTileY; ++y)
	{
		sampleX = 0;

		for (int x = 0; x < sampleTileX; ++x)
		{
			SetRect(&_vSampleObject2[y * sampleTileX + x]->rc,
				(sampleX * sampleImage->getFrameWidth()) + _terrainBtn.rc.left + 15,
				(sampleY * sampleImage->getFrameHeight()) + _terrainBtn.rc.bottom + 50,
				(sampleX * sampleImage->getFrameWidth()) + _terrainBtn.rc.left + 15 + sampleImage->getFrameWidth(),
				(sampleY * sampleImage->getFrameHeight()) + _terrainBtn.rc.bottom + 50 + sampleImage->getFrameHeight());

			_vSampleObject2[y * sampleTileX + x]->frameX = x;
			_vSampleObject2[y * sampleTileX + x]->frameY = y;

			sampleX++;
		}

		sampleY++;
	}
}

void maptool::renderSampleTileAndObject(void)
{
	if (_terrainBtn.isClick)
	{
		for (int i = 0; i < _vSampleTile.size(); ++i)
		{
			IMAGEMANAGER->findImage("샘플타일")->frameRender(getMemDC(),
				_vSampleTile[i]->rc.left, _vSampleTile[i]->rc.top,
				_vSampleTile[i]->frameX, _vSampleTile[i]->frameY);
		}
	}
	else if(_objectBtn[0].isClick)
	{
		for (int i = 0; i < _vSampleObject.size(); ++i)
		{
			IMAGEMANAGER->findImage("샘플오브젝트")->frameRender(getMemDC(),
				_vSampleObject[i]->rc.left, _vSampleObject[i]->rc.top,
				_vSampleObject[i]->frameX, _vSampleObject[i]->frameY);
		}
	}
	else if (_objectBtn[1].isClick)
	{
		for (int i = 0; i < _vSampleObject2.size(); ++i)
		{
			IMAGEMANAGER->findImage("샘플오브젝트2")->frameRender(getMemDC(),
				_vSampleObject2[i]->rc.left, _vSampleObject2[i]->rc.top,
				_vSampleObject2[i]->frameX, _vSampleObject2[i]->frameY);
		}
	}
}

void maptool::setTile()
{
	// 타일 추가 기본  3 * 3 추가되어있다.
	for (int i = 0; i < _tileY; ++i)
	{
		for (int k = 0; k < _tileX; ++k)
		{
			tagIsometricTile* iso = new tagIsometricTile;
			iso->idX = k;
			iso->idY = i;
			iso->width = _tileWidth * 2;
			iso->height = _tileHeight;
			iso->center = PointMake((k - i) * _tileWidth + WINSIZEX / 2, (k + i) * _tileHeight / 2 + _tileHeight);
			iso->rc = RectMakeCenter(iso->center.x, iso->center.y, iso->width, iso->height);
			iso->terrain = TR_CEMENT;
			iso->obj = OBJ_NONE;
			iso->terrainFrameX = iso->terrainFrameY = 0;
			iso->objFrameX = iso->objFrameY = 0;

			_vIsoTiles.push_back(iso);
		}
	}

	// 샘플 타일 벡터에 추가
	image* sampleImage = IMAGEMANAGER->findImage("샘플타일");
	int sampleTileX = sampleImage->getMaxFrameX() + 1;
	int sampleTileY = sampleImage->getMaxFrameY() + 1;
	
	for (int y = 0; y < sampleTileY; ++y)
	{
		for (int x = 0; x < sampleTileX; ++x)
		{
			tagSampleTile* sampleTile = new tagSampleTile;
			sampleTile->sampleImage = sampleImage;
			_vSampleTile.push_back(sampleTile);
		}
	}

	// 샘플 오브젝트 벡터에 추가
	sampleImage = IMAGEMANAGER->findImage("샘플오브젝트");
	sampleTileX = sampleImage->getMaxFrameX() + 1;
	sampleTileY = sampleImage->getMaxFrameY() + 1;

	for (int y = 0; y < sampleTileY; ++y)
	{
		for (int x = 0; x < sampleTileX; ++x)
		{
			tagSampleTile* sampleObject = new tagSampleTile;
			sampleObject->sampleImage = sampleImage;
			_vSampleObject.push_back(sampleObject);
		}
	}

	// 샘플 오브젝트 벡터에 추가
	sampleImage = IMAGEMANAGER->findImage("샘플오브젝트2");
	sampleTileX = sampleImage->getMaxFrameX() + 1;
	sampleTileY = sampleImage->getMaxFrameY() + 1;

	for (int y = 0; y < sampleTileY; ++y)
	{
		for (int x = 0; x < sampleTileX; ++x)
		{
			tagSampleTile* sampleObject2 = new tagSampleTile;
			sampleObject2->sampleImage = sampleImage;
			_vSampleObject2.push_back(sampleObject2);
		}
	}
}

void maptool::addTile()
{

	_addTileBtn.frameX = 1;

	for (int i = 0; i < _tileY + 1; ++i)
	{
		for (int k = 0; k < _tileX + 1; ++k)
		{
			if (i < _tileY && k < _tileX) continue;

			tagIsometricTile* iso = new tagIsometricTile;
			iso->idX = k;
			iso->idY = i;
			iso->width = _tileWidth * 2;
			iso->height = _tileHeight;
			iso->center = PointMake((k - i) * _tileWidth + WINSIZEX / 2, (k + i) * _tileHeight / 2 + _tileHeight);
			iso->rc = RectMakeCenter(iso->center.x, iso->center.y, iso->width, iso->height);
			iso->terrain = TR_CEMENT;
			iso->obj = OBJ_NONE;
			iso->terrainFrameX = iso->terrainFrameY = 0;
			iso->objFrameX = iso->objFrameY = 0;

			_vIsoTiles.push_back(iso);
		}
	}

	// 타일 갯수 증가
	_tileX++;
	_tileY++;


}

void maptool::removeTile()
{
	_removeTileBtn.frameX = 1;

	for (int i = _tileY - 1; i >= 0; --i)
	{
		for (int k = _tileX - 1; k >= 0; --k)
		{
			if (_vIsoTiles[i * _tileX + k]->idY < _tileY - 1 && _vIsoTiles[i * _tileX + k]->idX < _tileX - 1) continue;
			
			// 클래스에서 구조체로 바꾸자 안터지고있다..
			SAFE_DELETE(_vIsoTiles[i * _tileX + k]);
			_vIsoTiles.erase(_vIsoTiles.begin() + i * _tileX + k);
		}
	}

	// 타일 갯수 감소
	if (_tileX > 0 && _tileY > 0)
	{
		_tileX--; 
		_tileY--;
	}

}

void maptool::checkMousePoint()
{
	// 마우스를 사용한 포커스 변화

	if (_ptMouse.x <= 10) { _focus.left -= 5; _focus.right -= 5; }
	else if (_ptMouse.x >= WINSIZEX - 10) { _focus.left += 5; _focus.right += 5; }
	if (_ptMouse.y <= 10) { _focus.top -= 5; _focus.bottom -= 5; }
	else if (_ptMouse.y >= WINSIZEY - 10) { _focus.top += 5; _focus.bottom += 5; }

}

void maptool::checkPushButton()
{
	// 마우스 왼쪽 버튼 클릭 시
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		// 타일 추가
		if (PtInRect(&_addTileBtn.rc, _ptMouse))
		{
			addTile();
			return;			// 피킹이랑 같이 되는것을 막기위해 리턴
		}

		// 타일 감소
		else if (PtInRect(&_removeTileBtn.rc, _ptMouse))
		{
			removeTile();		
			return;
		}

		// 저장
		else if (PtInRect(&_saveBtn.rc, _ptMouse))
		{
			_saveBtn.frameX = 1;
			return;
		}

		// 불러오기
		else if(PtInRect(&_loadBtn.rc, _ptMouse))
		{
			_loadBtn.frameX = 1;

			return;
		}

		// 지우기
		else if (PtInRect(&_eraseBtn.rc, _ptMouse))
		{
			_isEraseObject = true;
			_isPickingSample = false;
			_eraseBtn.frameX = 1;
			return;
		}
		// 돌아가기
		else if(PtInRect(&_returnBtn.rc, _ptMouse))
		{
			_returnBtn.frameX = 1;
			
			return;
		}

		// Terrain Tab 선택
		else if (PtInRect(&_terrainBtn.rc, _ptMouse))
		{
			selectTerrain();
			return;
		}

		// 오브젝트 0 Tab 선택
		else if (PtInRect(&_objectBtn[0].rc, _ptMouse))
		{
			selectObject(0);
			return;
		}

		// 오브젝트 1 Tab 선택
		else if (PtInRect(&_objectBtn[1].rc, _ptMouse))
		{
			selectObject(1);
			return;
		}

		// 샘플 타일 선택
		for (int i = 0; i < _vSampleTile.size(); ++i)
		{
			if (PtInRect(&_vSampleTile[i]->rc, _ptMouse) &&
				_terrainBtn.isClick)
			{
				_isPickingSample = true;
				_isEraseObject = false;
				_currentPicking = _vSampleTile[i];
				return;
			}
		}

		// 샘플 오브젝트1 선택
		for (int i = 0; i < _vSampleObject.size(); ++i)
		{
			if (PtInRect(&_vSampleObject[i]->rc, _ptMouse) &&
				_objectBtn[0].isClick)
			{
				_isPickingSample = true; 
				_isEraseObject = false;
				_currentPicking = _vSampleObject[i];
				return;
			}
		}
		// 샘플 오브젝트2 선택
		for (int i = 0; i < _vSampleObject2.size(); ++i)
		{

			if (PtInRect(&_vSampleObject2[i]->rc, _ptMouse) &&
				_objectBtn[1].isClick)
			{
				_isPickingSample = true;
				_isEraseObject = false;
				_currentPicking = _vSampleObject2[i];
				return;
			}
		}
		// 피킹 확인
		for (int i = 0; i < _tileX * _tileY; ++i)
		{
			if (isPicking(_vIsoTiles[i]->center.x, _vIsoTiles[i]->center.y))
			{
				pickingTile(i);
			}
		}

	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (_addTileBtn.frameX != 0) _addTileBtn.frameX = 0;
		if (_removeTileBtn.frameX != 0) _removeTileBtn.frameX = 0;
		if (_eraseBtn.frameX != 0) _eraseBtn.frameX = 0;
		if (_saveBtn.frameX != 0)
		{
			_saveBtn.frameX = 0;
			if (PtInRect(&_saveBtn.rc, _ptMouse))
			{
				ShowCursor(true);
				save();
				ShowCursor(false);
			}
		}
		if (_loadBtn.frameX != 0)
		{
			_loadBtn.frameX = 0;
			if (PtInRect(&_loadBtn.rc, _ptMouse))
			{
				ShowCursor(true);
				load();
				ShowCursor(false);
			}
		}
		if (_returnBtn.frameX != 0)
		{
			_returnBtn.frameX = 0; 
			if (PtInRect(&_returnBtn.rc, _ptMouse))
			{
				SCENEMANAGER->changeScene("인트로씬");
			}
		}
	}

	// 샘플 타일 및 오브젝트 선택 취소
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		_isPickingSample = false;
		_isEraseObject = false;
	}


	// 화살표로 포커스 변화
	if (KEYMANAGER->isStayKeyDown(VK_UP)) { _focus.top -= 5; _focus.bottom -= 5; }
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) { _focus.top += 5; _focus.bottom += 5; }
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) { _focus.left -= 5; _focus.right -= 5; }
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) { _focus.left += 5; _focus.right += 5; }



}

void maptool::selectTerrain()
{
	_terrainBtn.frameX = 0;	
	_terrainBtn.isClick = true;
	_objectBtn[0].frameX = 1;
	_objectBtn[0].isClick = false;
	_objectBtn[1].frameX = 1;
	_objectBtn[1].isClick = false;

	_isPickingSample = false;
	_isEraseObject = false;

}

void maptool::selectObject(int objectNum)
{
	if (objectNum == 0)
	{
		_objectBtn[0].frameX = 0;
		_objectBtn[0].isClick = true;
		_objectBtn[1].frameX = 1;
		_objectBtn[1].isClick = false;
	}
	else
	{
		_objectBtn[0].frameX = 1;
		_objectBtn[0].isClick = false;
		_objectBtn[1].frameX = 0;
		_objectBtn[1].isClick = true;
	}

	_terrainBtn.frameX = 1;
	_terrainBtn.isClick = false;

	_isPickingSample = false;
	_isEraseObject = false;

}



void maptool::pickingTile(int pickingIndex)
{
	if (_currentPicking == NULL) return;

	if (_isEraseObject)
	{
		_vIsoTiles[pickingIndex]->obj = OBJ_NONE;
		_vIsoTiles[pickingIndex]->objFrameX = _vIsoTiles[pickingIndex]->objFrameY = 0;
	}
	else if (_terrainBtn.isClick)
	{
		if (_currentPicking->frameY == 0)
		{
			_vIsoTiles[pickingIndex]->terrain = TR_CEMENT;
			_vIsoTiles[pickingIndex]->terrainFrameX = _currentPicking->frameX;
			_vIsoTiles[pickingIndex]->terrainFrameY = _currentPicking->frameY;
		}
		if (_currentPicking->frameY == 1)
		{
			_vIsoTiles[pickingIndex]->terrain = TR_GRASS;
			_vIsoTiles[pickingIndex]->terrainFrameX = _currentPicking->frameX;
			_vIsoTiles[pickingIndex]->terrainFrameY = _currentPicking->frameY;
		}
		if (_currentPicking->frameY == 2)
		{
			_vIsoTiles[pickingIndex]->terrain = TR_DESERT;
			_vIsoTiles[pickingIndex]->terrainFrameX = _currentPicking->frameX;
			_vIsoTiles[pickingIndex]->terrainFrameY = _currentPicking->frameY;
		}
	}
	else if (_objectBtn[0].isClick)
	{
		_vIsoTiles[pickingIndex]->obj = OBJ_WALL;
		_vIsoTiles[pickingIndex]->objFrameX = _currentPicking->frameX;
		_vIsoTiles[pickingIndex]->objFrameY = _currentPicking->frameY;
	}
	else if (_objectBtn[1].isClick)
	{
		_vIsoTiles[pickingIndex]->obj = OBJ_FLAG;
		_vIsoTiles[pickingIndex]->objFrameX = _currentPicking->frameX;
		_vIsoTiles[pickingIndex]->objFrameY = _currentPicking->frameY;
	}
}

bool maptool::isPicking(float cx, float cy)
{
	
	for (int i = 0; i < _tileX * _tileY; ++i)
	{

		// 선형 방정식 (y-b) = m(x-a);  / 기울기
		// _ptMouse.y - 꼭지점y = 기울기 * (_ptMouse.x - 꼭지점x)
		// 왼쪽, 오른쪽 꼭지점을 구한다.

		// 선형 방정식 (y-b) = -m(x-a);  \(역슬래시) 기울기
		// _ptMouse.y - 꼭지점y = -기울기 * (_ptMouse.x - 꼭지점x)
		// 위, 아래 꼭지점을 구한다.

		// 기울기는 공통


		float grade = (float)(_isoHeight / 2) / (_isoWidth / 2);

		float centerX = cx - _focus.left;
		float centerY = cy - _focus.top;

		POINT D1, D2, D3, D4;
		D1.x = centerX - _isoWidth / 2; D1.y = centerY;
		D2.x = centerX; D2.y = centerY - _isoHeight / 2;
		D3.x = centerX + _isoWidth / 2; D3.y = centerY;
		D4.x = centerX; D4.y = centerY + _isoHeight / 2;

		float d1 = _ptMouse.y - D1.y - (-grade * (_ptMouse.x - D1.x));
		float d2 = _ptMouse.y - D2.y - (grade * (_ptMouse.x - D2.x));
		float d3 = _ptMouse.y - D3.y - (-grade * (_ptMouse.x - D3.x));
		float d4 = _ptMouse.y - D4.y - (grade * (_ptMouse.x - D4.x));

		if (d1 > 0)
		{
			if (d2 > 0)
			{
				if (d3 < 0)
				{
					if (d4 < 0)
					{
						return true;
					}
				}
			}
		}

	}

	return false;
}

void maptool::save(void)
{
	HANDLE file;
	DWORD write;

	OPENFILENAME sfn;
	char filePathSize[1028] = "";
	ZeroMemory(&sfn, sizeof(OPENFILENAME));
	sfn.lStructSize = sizeof(OPENFILENAME);
	sfn.hwndOwner = NULL;
	sfn.lpstrFile = filePathSize;
	sfn.nMaxFile = sizeof(filePathSize);
	sfn.nFilterIndex = true;
	sfn.lpstrFileTitle = NULL;
	sfn.nMaxFileTitle = NULL;
	sfn.lpstrInitialDir = NULL;
	sfn.lpstrFilter = "MapFile\0*.map";
	sfn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetSaveFileName(&sfn) == FALSE) return;

	char temp[1028];
	strncpy_s(temp, strlen(sfn.lpstrFile) + 1, sfn.lpstrFile, strlen(sfn.lpstrFile));

	char* context = NULL;
	char* token = strtok_s(temp, "\\", &context);

	while (strlen(context))
	{
		token = strtok_s(NULL, "\\", &context);
	}

	file = CreateFile(strcat(token,".map"), GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// _tileX _tileY의 값을 먼저 저장
	WriteFile(file, &_tileX, sizeof(int), &write, NULL);
	WriteFile(file, &_tileY, sizeof(int), &write, NULL);

	for (int i = 0; i < _tileX * _tileY; ++i)
	{
		WriteFile(file, _vIsoTiles[i], sizeof(tagIsometricTile), &write, NULL);
	}

	CloseHandle(file);

}

void maptool::load(void)
{

	HANDLE file;
	DWORD read;

	OPENFILENAME ofn;
	char filePathSize[1028] = "";
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePathSize;
	ofn.nMaxFile = sizeof(filePathSize);
	ofn.nFilterIndex = true;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFilter = "MapFile\0*.map";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn) == FALSE) return;

	char temp[1028];
	strncpy_s(temp, strlen(ofn.lpstrFile) + 1, ofn.lpstrFile, strlen(ofn.lpstrFile));

	char* context = NULL;
	char* token = strtok_s(temp, "\\", &context);
	while (strlen(context))
	{
		token = strtok_s(NULL, "\\", &context);
	}


	file = CreateFile(token, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	while (_vIsoTiles.size())
	{
		// 불러오기 후 불러오기 누르면 터지는데 이유가 뭐지??
		SAFE_DELETE(_vIsoTiles[0]);
		_vIsoTiles.erase(_vIsoTiles.begin());
	}
	
	ReadFile(file, &_tileX, sizeof(int), &read, NULL);
	ReadFile(file, &_tileY, sizeof(int), &read, NULL);

	for (int i = 0; i < _tileY; ++i)
	{
		for (int k = 0; k < _tileX; ++k)
		{
			tagIsometricTile* tempIso = new tagIsometricTile;

			ReadFile(file, tempIso, sizeof(tagIsometricTile), &read, NULL);
			_vIsoTiles.push_back(tempIso);

		}
	}

	CloseHandle(file);

}
