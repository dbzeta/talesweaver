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

	_returnBtn.btnImage = IMAGEMANAGER->addPngFrameImage("돌아가기버튼", "돌아가기버튼.png", 190, 33, 2, 1, false, false);
	_returnBtn.frameX = _loadBtn.frameY = 0;
	_returnBtn.rc = RectMake(50, WINSIZEY - 10 - _returnBtn.btnImage->getFrameHeight(), _returnBtn.btnImage->getFrameWidth(), _returnBtn.btnImage->getFrameHeight());

	_saveBtn.btnImage = IMAGEMANAGER->addPngFrameImage("저장하기버튼", "저장하기버튼.png", 190, 33, 2, 1, false, false);
	_saveBtn.frameX = _saveBtn.frameY = 0;
	_saveBtn.rc = RectMake(50, 320, _saveBtn.btnImage->getFrameWidth(), _saveBtn.btnImage->getFrameHeight());
	_loadBtn.btnImage = IMAGEMANAGER->addPngFrameImage("불러오기버튼", "불러오기버튼.png", 190, 33, 2, 1, false, false);
	_loadBtn.frameX = _loadBtn.frameY = 0;
	_loadBtn.rc = RectMake(50, _saveBtn.rc.bottom + 20, _loadBtn.btnImage->getFrameWidth(), _loadBtn.btnImage->getFrameHeight());
	_eraseBtn.rc = RectMake(50, _loadBtn.rc.bottom + 20, _loadBtn.btnImage->getFrameWidth(), _loadBtn.btnImage->getFrameHeight());

	_rightUIScreen.screenImage = IMAGEMANAGER->addPngImage("맵툴UI", "맵툴UI.png", 252, 552, false, false);
	_rightUIScreen.rc = RectMake(WINSIZEX - _rightUIScreen.screenImage->getWidth(), WINSIZEY - _rightUIScreen.screenImage->getHeight(), _rightUIScreen.screenImage->getFrameWidth(), _rightUIScreen.screenImage->getFrameHeight());
	_leftUIScreen.screenImage = IMAGEMANAGER->addPngImage("맵툴UI", "맵툴UI.png", 252, 552, false, false);
	_leftUIScreen.rc = RectMake(WINSIZEX - _rightUIScreen.screenImage->getWidth(), WINSIZEY - _rightUIScreen.screenImage->getHeight(), _rightUIScreen.screenImage->getFrameWidth(), _rightUIScreen.screenImage->getFrameHeight());

	_addTileBtn.btnImage = IMAGEMANAGER->addPngFrameImage("추가버튼", "추가버튼.png",99, 23, 2, 1, false, false);
	_addTileBtn.frameX = _addTileBtn.frameY = 0;
	_addTileBtn.rc = RectMake(50, 200, _addTileBtn.btnImage->getFrameWidth(), _addTileBtn.btnImage->getFrameHeight());
	_removeTileBtn.btnImage = IMAGEMANAGER->addPngFrameImage("삭제버튼", "삭제버튼.png", 99, 23, 2, 1, false, false);
	_removeTileBtn.frameX = _removeTileBtn.frameY = 0; 
	_removeTileBtn.rc = RectMake(50, 270, _removeTileBtn.btnImage->getFrameWidth(), _removeTileBtn.btnImage->getFrameHeight());

	_terrainBtn.btnImage = IMAGEMANAGER->addPngFrameImage("타일버튼", "타일버튼2.png", 152, 18, 2, 1, false, false);
	_terrainBtn.frameX = _terrainBtn.frameY = 0;
	_terrainBtn.rc = RectMake(WINSIZEX - 244, 276, _terrainBtn.btnImage->getFrameWidth(), _terrainBtn.btnImage->getFrameHeight());
	_terrainBtn.isClick = true;
	_objectBtn.btnImage = IMAGEMANAGER->addPngFrameImage("오브젝트버튼", "오브젝트버튼1.png", 152, 18, 2, 1, false, false);
	_objectBtn.frameX = 1;
	_objectBtn.frameY = 0;
	_objectBtn.rc = RectMake(WINSIZEX - 244 + _terrainBtn.btnImage->getFrameWidth(), 276, _objectBtn.btnImage->getFrameWidth(), _objectBtn.btnImage->getFrameHeight());
	_objectBtn.isClick = false;

	_focus = RectMake(0, 0, WINSIZEX, WINSIZEY);

	IMAGEMANAGER->addPngFrameImage("샘플타일", "타일.png", 394 / 2, 96 / 2, 2, 1, false, false);
	IMAGEMANAGER->addFrameImage("샘플오브젝트", "벽.bmp", 576 / 3, 1410 / 3, 3, 5, true, RGB(255, 0, 255));

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

	for (int i = 0; i < _vIsoTile.size(); ++i)
	{
		_vIsoTile[i]->tileRender(_focus);
	}
	for (int i = 0; i < _vIsoTile.size(); ++i)
	{
		_vIsoTile[i]->objectRender(_focus);
	}

	// 버튼
	_addTileBtn.btnImage->frameRender(getMemDC(), _addTileBtn.rc.left, _addTileBtn.rc.top, _addTileBtn.frameX, _addTileBtn.frameY);
	_removeTileBtn.btnImage->frameRender(getMemDC(), _removeTileBtn.rc.left, _removeTileBtn.rc.top, _removeTileBtn.frameX, _removeTileBtn.frameY);

	_saveBtn.btnImage->frameRender(getMemDC(), _saveBtn.rc.left, _saveBtn.rc.top);
	_loadBtn.btnImage->frameRender(getMemDC(), _loadBtn.rc.left, _loadBtn.rc.top);
	Rectangle(getMemDC(), _eraseBtn.rc.left, _eraseBtn.rc.top, _eraseBtn.rc.right, _eraseBtn.rc.bottom);
	_returnBtn.btnImage->frameRender(getMemDC(), _returnBtn.rc.left, _returnBtn.rc.top);

	// 샘플 타일 및 오브젝트 클릭시 마우스 포인터에 랜더되는 이미지
	if (_isPickingSample) _currentPicking->sampleImage->frameRender(getMemDC(), 
		_ptMouse.x - _currentPicking->sampleImage->getFrameWidth() / 2, 
		_ptMouse.y - _currentPicking->sampleImage->getFrameHeight() / 2, 
		_currentPicking->frameX, _currentPicking->frameY);

	// 타일 창
	_rightUIScreen.screenImage->render(getMemDC(), _rightUIScreen.rc.left, _rightUIScreen.rc.top);

	// 타일 & 오브젝트 버튼
	_terrainBtn.btnImage->frameRender(getMemDC(), _terrainBtn.rc.left, _terrainBtn.rc.top, _terrainBtn.frameX, _terrainBtn.frameY);
	_objectBtn.btnImage->frameRender(getMemDC(), _objectBtn.rc.left, _objectBtn.rc.top, _objectBtn.frameX, _objectBtn.frameY);

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
	else
	{
		for (int i = 0; i < _vSampleObject.size(); ++i)
		{
			IMAGEMANAGER->findImage("샘플오브젝트")->frameRender(getMemDC(),
				_vSampleObject[i]->rc.left, _vSampleObject[i]->rc.top,
				_vSampleObject[i]->frameX, _vSampleObject[i]->frameY);
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
			isometricTile* iso = new isometricTile;
			iso->init(k, i, _tileWidth, _tileHeight);
			_vIsoTile.push_back(iso);
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

}

void maptool::addTile()
{

	_addTileBtn.frameX = 1;

	for (int i = 0; i < _tileY + 1; ++i)
	{
		for (int k = 0; k < _tileX + 1; ++k)
		{
			if (i < _tileY && k < _tileX) continue;

			isometricTile* iso = new isometricTile;
			iso->init(k, i, _tileWidth, _tileHeight);
			_vIsoTile.push_back(iso);
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
			if (_vIsoTile[i * _tileX + k]->getIdY() < _tileY - 1 && _vIsoTile[i * _tileX + k]->getIdX() < _tileX - 1) continue;
			
			// 돌겠네 왜 터져;;
			SAFE_DELETE(_vIsoTile[i * _tileX + k]);
			_vIsoTile.erase(_vIsoTile.begin() + i * _tileX + k);
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
			save();
			return;
		}

		// 불러오기
		else if(PtInRect(&_loadBtn.rc, _ptMouse))
		{
			load();
			return;
		}

		// 지우기
		else if (PtInRect(&_eraseBtn.rc, _ptMouse))
		{
			_isEraseObject = true;
			_isPickingSample = false;
			return;
		}
		// 뒤로가기
		else if(PtInRect(&_returnBtn.rc, _ptMouse))
		{
			PostQuitMessage(0);
			return;
		}

		// Terrain Tab 선택
		else if (PtInRect(&_terrainBtn.rc, _ptMouse))
		{
			selectTerrain();
			return;
		}

		// 오브젝트 Tab 선택
		else if (PtInRect(&_objectBtn.rc, _ptMouse))
		{
			selectObject();
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

		// 샘플 오브젝트 선택
		for (int i = 0; i < _vSampleObject.size(); ++i)
		{
			if (PtInRect(&_vSampleObject[i]->rc, _ptMouse) &&
				_objectBtn.isClick)
			{
				_isPickingSample = true; 
				_isEraseObject = false;
				_currentPicking = _vSampleObject[i];
				return;
			}
		}

		// 피킹 확인
		for (int i = 0; i < _tileX * _tileY; ++i)
		{
			if (isPicking(_vIsoTile[i]->getCenter().x, _vIsoTile[i]->getCenter().y))
			{
				pickingTile(i);
			}
		}

	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (_addTileBtn.frameX != 0) _addTileBtn.frameX = 0;
		if (_removeTileBtn.frameX != 0) _removeTileBtn.frameX = 0;

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
	_objectBtn.frameX = 1;
	_objectBtn.isClick = false;

	_isPickingSample = false;
	_isEraseObject = false;

}

void maptool::selectObject()
{
	_objectBtn.frameX = 0;
	_objectBtn.isClick = true;
	_terrainBtn.frameX = 1;
	_terrainBtn.isClick = false;

	_isPickingSample = false;
	_isEraseObject = false;

}



void maptool::pickingTile(int pickingIndex)
{
	if (_currentPicking == NULL) return;

	if (_isEraseObject) _vIsoTile[pickingIndex]->eraseObject();
	else if(_terrainBtn.isClick) _vIsoTile[pickingIndex]->selectTerrain(_currentPicking->frameX, _currentPicking->frameY);
	else if(_objectBtn.isClick) _vIsoTile[pickingIndex]->selectObject(_currentPicking->frameX, _currentPicking->frameY);
	
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
		WriteFile(file, _vIsoTile[i], sizeof(isometricTile), &write, NULL);
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

	while (_vIsoTile.size())
	{
		// 불러오기 후 불러오기 누르면 터지는데 이유가 뭐지??
		// SAFE_DELETE(_vIsoTile[0]);
		_vIsoTile.erase(_vIsoTile.begin());
	}
	
	
	ReadFile(file, &_tileX, sizeof(int), &read, NULL);
	ReadFile(file, &_tileY, sizeof(int), &read, NULL);

	for (int i = 0; i < _tileY; ++i)
	{
		for (int k = 0; k < _tileX; ++k)
		{
			isometricTile* tempIso = new isometricTile;

			ReadFile(file, tempIso, sizeof(isometricTile), &read, NULL);

			_vIsoTile.push_back(tempIso);
		}
	}
	CloseHandle(file);
}
