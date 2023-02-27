#include "stdafx.h"
#include "player.h"
#include "uiManager.h"
#include "itemManager.h"
#include "enemyManager.h"
#include "npcManager.h"
#include "mapManager.h"

player::player()
{
}

player::~player()
{
}

HRESULT player::init()
{

	_frameX = _frameY = 0;
	_count = 0;
	_comboCount = 0;

	// 초기 스테이터스 ( 처음 캐릭터를 만들었을때의 스테이터스 init + 저장된 캐릭터 데이터 로드 )

	_isUseAStar = false;
	_isAttack = false;
	_isAutoAttack = false;
	_isMove = false;
	_isLive = true;


	IMAGEMANAGER->findImage("루시안_IDLE")->alphaRender(getMemDC(), 255);

	_attackTarget = NULL;

	return S_OK;
}

void player::release()
{
}

void player::update() 
{
	POINT center;

	_rc = RectMakeCenter(_cx, _by  - _image->getFrameHeight() / 2, _image->getFrameWidth(), _image->getFrameHeight());

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_currentExp += 78;
	}

	if (_target.x == _cx && _target.y == _by)
	{
		if (!_isMove)
		{
			_state = P_IDLE;
			changeState();
		}
	}

	// 포커스 범위 설정 ( 플레이어 현재 위치에서 창 크기만큼 )
	_focus = RectMakeCenter(_cx, _by - _image->getFrameHeight() / 2, WINSIZEX, WINSIZEY);


	checkLevel();

	checkStatus();

	move();
	// changeDirection();
	// attack();

	


	// 프레임 증가
	if (++_count % 6 == 0) _frameX++;

	if (_state == P_ATTACK_NORMAL)
	{
		if (_vCombo[0] == P_ATTACK_STAB)
		{
			if (_frameX == 2 && _count % 6 == 1) _attackTarget->addDamage(RND->getFromIntTo(_minDamage, _maxDamage));
		}
		else if (_vCombo[0] == P_ATTACK_VERTICAL_HACK)
		{
			if (_frameX == 4 && _count % 6 == 1) _attackTarget->addDamage(RND->getFromIntTo(_minDamage, _maxDamage));
		}
		else if (_vCombo[0] == P_ATTACK_HORIZONTAL_HACK)
		{
			if (_frameX == 3 && _count % 6 == 1) _attackTarget->addDamage(RND->getFromIntTo(_minDamage, _maxDamage));
		}
	}

	if (_frameX > _image->getMaxFrameX())
	{
		_frameX = 0;

		if (_state == P_ATTACK_NORMAL)
		{
			_state = P_IDLE;
			changeState();
			_isAttack = false;
			_isMove = false;
		}
	}


}

void player::render() 
{


	if(_debug) Rectangle(getMemDC(), _rc.left - _focus.left, _rc.top - _focus.top, _rc.right - _focus.left, _rc.bottom - _focus.top);
	if(_debug) Rectangle(getMemDC(), _target.x - _focus.left, _target.y - _focus.top, _target.x - _focus.left + 10, _target.y - _focus.top + 10);
	// _image->frameRender(getMemDC(), WINSIZEX / 2 - _image->getFrameWidth() / 2, WINSIZEY / 2 - _image->getFrameHeight() / 2, _frameX, _frameY);

	char str[100];
	sprintf_s(str, "TARGET = %d, %d", _target.x, _target.y);
	TextOut(getMemDC(), 100, 100, str, strlen(str));
	sprintf_s(str, "left = %d, top =  %d", _rc.left, _rc.top);
	TextOut(getMemDC(), 100, 120, str, strlen(str));
	sprintf_s(str, "right = %d, bottom = %d", _rc.right, _rc.bottom);
	TextOut(getMemDC(), 100, 140, str, strlen(str));
	sprintf_s(str, "centerX = %d, centerY = %d", (_rc.right + _rc.left) / 2, (_rc.bottom + _rc.top) / 2);
	TextOut(getMemDC(), 100, 160, str, strlen(str));

	sprintf_s(str, "[%4d, %4d]", (int)_cx, (int)_by);
	TextOut(getMemDC(), _cx - 32 - _focus.left, _by + 10 - _focus.top, str, strlen(str));



	DRAWMANAGER->addDrawList(DRAW_FRAMERENDER, "PLAYER", _image, _frameX, _frameY, _rc, 0);

	// 장비가 보일때 무기류가 아닐경우 idle에서만 보인다
	for (int i = 0; i < _vEquipment.size(); ++i)
	{
		if (_state != P_RUN && _state != P_WALK)
		{
			// HEAD
			if ((_vEquipment[i] % TYPE_EQUIPMENT) / (TYPE_HEAD % TYPE_EQUIPMENT) == 1)
			{

				if (IMAGEMANAGER->findImage(_im->getItem(_vEquipment[i])->getUseImageName()) != NULL)
				{
					DRAWMANAGER->addDrawList(DRAW_FRAMERENDER, "HEADITEM", IMAGEMANAGER->findImage(_im->getItem(_vEquipment[i])->getUseImageName()), _frameX, _frameY, _rc, 0);
				}
			}
			// ARM 
			else if ((_vEquipment[i] % TYPE_EQUIPMENT) / (TYPE_HEAD % TYPE_EQUIPMENT) == 3)
			{
				if (IMAGEMANAGER->findImage(_im->getItem(_vEquipment[i])->getUseImageName()) != NULL)
				{
					char str[128];
					RECT drawRc;
					strcpy_s(str, _im->getItem(_vEquipment[i])->getUseImageName());
					if (_state == P_ATTACK_NORMAL)
					{
						if (_vCombo[_comboCount%3] == P_ATTACK_STAB)
						{
							drawRc = RectMake(_rc.left - 50, _rc.top - 50, (_rc.right - _rc.left) + 100, (_rc.bottom - _rc.top) + 100);
							strcat_s(str, "_ATTACK_STAB");
						}
						else if (_vCombo[_comboCount%3] == P_ATTACK_VERTICAL_HACK)
						{
							drawRc = RectMake(_rc.left - 50, _rc.top - 50, (_rc.right - _rc.left) + 100, (_rc.bottom - _rc.top) + 100);
							strcat_s(str, "_ATTACK_VERTICAL_HACK");
						}
						else if (_vCombo[_comboCount%3] == P_ATTACK_HORIZONTAL_HACK)
						{
							drawRc = RectMake(_rc.left - 50, _rc.top - 10, (_rc.right - _rc.left) + 100, (_rc.bottom - _rc.top) + 20);
							strcat_s(str, "_ATTACK_HORIZONTAL_HACK");
						}
					}			
					else if (_state == P_IDLE)
					{
						drawRc = RectMake(_rc.left - 50, _rc.top, (_rc.right - _rc.left) + 100, _rc.bottom - _rc.top);
					}
					DRAWMANAGER->addDrawList(DRAW_FRAMERENDER, "ARMITEM", IMAGEMANAGER->findImage(str), _frameX, _frameY, drawRc, 0);
				}
			}
			// SUBARM (오직 방패류만)
			else if ((_vEquipment[i] % TYPE_EQUIPMENT) / (TYPE_HEAD % TYPE_EQUIPMENT) == 4)
			{
				if (_state != P_ATTACK_NORMAL && _state != P_ATTACK_SKILL)
				{
					// 쉴드 인지 구분하는 조건문 4201 % 4000 = 201 104100 / 104000 = 100
					if ((((_vEquipment[i] % TYPE_EQUIPMENT) % (TYPE_SUBARMS % TYPE_EQUIPMENT))) / (TYPE_SHIELD % TYPE_SUBARMS) == 1)
					{
						if (IMAGEMANAGER->findImage(_im->getItem(_vEquipment[i])->getUseImageName()) != NULL)
						{
							DRAWMANAGER->addDrawList(DRAW_FRAMERENDER, "SUBARMSITEM", IMAGEMANAGER->findImage(_im->getItem(_vEquipment[i])->getUseImageName()), _frameX, _frameY, _rc, 0);
						}
					}
				}
			}
			// FACE 
			else if ((_vEquipment[i] % TYPE_EQUIPMENT) / (TYPE_HEAD % TYPE_EQUIPMENT) == 5)
			{
				if (IMAGEMANAGER->findImage(_im->getItem(_vEquipment[i])->getUseImageName()) != NULL)
				{
					DRAWMANAGER->addDrawList(DRAW_FRAMERENDER, "FACEITEM", IMAGEMANAGER->findImage(_im->getItem(_vEquipment[i])->getUseImageName()), _frameX, _frameY, _rc, 0);
				}
			}
			// BACK
			else if ((_vEquipment[i] % TYPE_EQUIPMENT) / (TYPE_HEAD % TYPE_EQUIPMENT) == 6)
			{
				if (IMAGEMANAGER->findImage(_im->getItem(_vEquipment[i])->getUseImageName()) != NULL)
				{
					DRAWMANAGER->addDrawList(DRAW_FRAMERENDER, "BACKITEM", IMAGEMANAGER->findImage(_im->getItem(_vEquipment[i])->getUseImageName()), _frameX, _frameY, _rc, 0);
				}
			}
		}
	}

	if (_state == P_ATTACK_NORMAL)
	{
		RECT drawRc;
		if (_vCombo[_comboCount%3] == P_ATTACK_STAB)
		{
			drawRc = RectMake(_rc.left - 50, _rc.top - 50, (_rc.right - _rc.left) + 100, (_rc.bottom - _rc.top) + 100);
			DRAWMANAGER->addDrawList(DRAW_FRAMERENDER, "ATTACK", IMAGEMANAGER->findImage("찌르기이펙트"), _frameX, _frameY, drawRc, 0);
		}
		else if (_vCombo[_comboCount%3] == P_ATTACK_VERTICAL_HACK && _frameX > 2)
		{
			drawRc = RectMake(_rc.left - 50, _rc.top - 30, (_rc.right - _rc.left) + 100, (_rc.bottom - _rc.top) + 100);
			DRAWMANAGER->addDrawList(DRAW_FRAMERENDER, "ATTACK", IMAGEMANAGER->findImage("종베기이펙트"), _frameX - 3, _frameY, drawRc, 0);
		}
		else if (_vCombo[_comboCount%3] == P_ATTACK_HORIZONTAL_HACK && _frameX > 1)
		{
			drawRc = RectMake(_rc.left - 50, _rc.top - 10, (_rc.right - _rc.left) + 100, (_rc.bottom - _rc.top) + 20);
			DRAWMANAGER->addDrawList(DRAW_FRAMERENDER, "ATTACK", IMAGEMANAGER->findImage("횡베기이펙트"), _frameX - 2, _frameY, drawRc, 0);
		}
	}

}

void player::move()
{
	if (!_isMove) return;


	// 에이스타 검출

	// 타일 차이가 1이하면 좌표를 사용하여 사거리까지 접근
	if(!_isUseAStar)
	{

		// 위 아래 왼쪽 오른쪽 어디로 갈건지 선택 ( 좌표 이동 )
		changeDirection(_cx, _by, _target.x, _target.y);

		// 공격을 해야하는 것 이면
		if (_isAttack)
		{
			// 평타 사거리 ( 100 ) 안에 있으면 바로 공격
			if (abs(getDistance(_cx, _by, _target.x, _target.y)) <= 100)
			{
				_state = P_ATTACK_NORMAL;
				changeState();
				_isAttack = false;
				_isMove = false;
			}
		}
		// 그냥 걸어 다니는 거면
		else
		{
			if (abs(_cx - _target.x) <= 6 && abs(_by - _target.y) <= 6)
			{
				_state = P_IDLE;
				changeState();
				_isMove = false;
			}	
		}
	}

	// 클릭 -> 에이스타를 사용하여 경로를 얻음 -> 플레이어가 다음 경로를 알고 있다.
	

	// 타일 차이가 2이상이면 에이스타를 사용하여 사거리까지 접근
	else
	{
		// 에이스타 사용시 최종 타겟의 전 타일까지 return 해주므로 중간중간 넣어줄 타겟을 임시로 만들어준다.
	
		if (_vPath.size() > 0)
		{
			_aStarTarger.x = _mm->getTile(_vPath[0])->center.x;
			_aStarTarger.y = _mm->getTile(_vPath[0])->center.y;
		}
		else
		{
			_isUseAStar = false;
			return;
		}
		// 에이스타에서 얻은 경로를 향해서 이동
		
		changeDirection(_cx, _by, (int)_aStarTarger.x, (int)_aStarTarger.y);
		
		if (abs(_cx - _aStarTarger.x) <= 6 && abs(_by - _aStarTarger.y) <= 6  && _vPath.size() > 0)
		{
			_vPath.erase(_vPath.begin());
		}

		// 마지막 타일의 센터로는 가지 않기위해
		if (_vPath.size() == 1)
		{
			if (_mm->isPickTile(_cx, _by, true))
			{
				int left = _mm->getTile(_vPath[0])->center.x - (_mm->getTile(_vPath[0])->width / 2);
				int up = _mm->getTile(_vPath[0])->center.y - (_mm->getTile(_vPath[0])->height / 2);
				int right = _mm->getTile(_vPath[0])->center.x + (_mm->getTile(_vPath[0])->width / 2);
				int down = _mm->getTile(_vPath[0])->center.y + (_mm->getTile(_vPath[0])->height / 2);
				
				RECT checkTile = RectMakeCenter(
						_mm->getTile(_vPath[0])->center.x, _mm->getTile(_vPath[0])->center.y,
						_mm->getTile(_vPath[0])->width, _mm->getTile(_vPath[0])->height
				);
				POINT tempPt = { _cx, _by };
				// 마지막 타일에 플레이어가 들어왔다면
				if (PtInRect(&checkTile, tempPt))
				{
					_isUseAStar = false;
				}

			}
		}
		

		// 공격을 해야하는 것 이면
		if (_isAttack)
		{
			// 평타 사거리 ( 100 ) 안에 있으면 바로 공격
			if (abs(getDistance(_cx, _by, _target.x, _target.y)) <= 100)
			{
				_state = P_ATTACK_NORMAL;
				changeState();
				_isUseAStar = false;
				_isAttack = false;
				_isMove = false;
				_vPath.empty();
			}
		}
		// 그냥 걸어 다니는 거면
		else
		{
			// 타겟의 거리에도달하면 
			if (abs(_cx - _aStarTarger.x) <= 2 && abs(_by - _aStarTarger.y) <= 2)
			{
				_state = P_IDLE;
				changeState();				
				_isUseAStar = false;
				_isMove = false;
			}
		}
	}


}

void player::attack()
{

}

void player::changeDirection(float startX, float startY, float endX, float endY)
{

	
	_angle = getAngle(startX, startY, endX, endY);
	

	// RIGHT
	if ((0 <= _angle &&  _angle < PI2 / 16) || (15 * (PI2 / 16) <= _angle && _angle < PI2))
		_dir = P_DIR_RIGHT;
	// RIGHT UP
	else if (PI2 / 16 <= _angle &&  _angle < 3 *( PI2 / 16))
		_dir = P_DIR_RIGHT_UP; 
	// UP
	else if (3 *( PI2 / 16) <= _angle &&  _angle < 5 * (PI2 / 16))
		_dir = P_DIR_UP; 
	// LEFT UP
	else if (5 * (PI2 / 16) <= _angle &&  _angle < 7 *( PI2 / 16))
		_dir = P_DIR_LEFT_UP;
	// LEFT
	else if (7 * (PI2 / 16) <= _angle &&  _angle < 9 *( PI2 / 16))
		_dir = P_DIR_LEFT; 
	// LEFT DOWN
	else if (9 * (PI2 / 16) <= _angle &&  _angle < 11 *( PI2 / 16))
		_dir = P_DIR_LEFT_DOWN; 
	// DOWN
	else if (11 *( PI2 / 16) <= _angle &&  _angle < 13 * (PI2 / 16))
		_dir = P_DIR_DOWN; 
	// RIGHT DOWN
	else if (13 * (PI2 / 16) <= _angle &&  _angle < 15 * (PI2 / 16))
		_dir = P_DIR_RIGHT_DOWN; 

	// 움직일 떄
	if (_isMove)
	{
		int speed;
		if (P_RUN) speed = _runningSpeed * 150 / 16;
		else if (P_WALK) speed = _walkSpeed * 150 / 16;

		_cx += cosf(_angle) * TIMEMANAGER->getElapsedTime() * speed;
		_by += -sinf(_angle) * TIMEMANAGER->getElapsedTime() * speed;

	}

	// 
	switch (_dir)
	{
	case P_DIR_DOWN:					_frameY = 0;
		break;
	case P_DIR_LEFT_DOWN:				_frameY = 1;
		break;
	case P_DIR_LEFT:					_frameY = 2;
		break;
	case P_DIR_LEFT_UP:					_frameY = 3;
		break;
	case P_DIR_UP:						_frameY = 4;
		break;
	case P_DIR_RIGHT_UP:				_frameY = 5;
		break;
	case P_DIR_RIGHT:					_frameY = 6;
		break;
	case P_DIR_RIGHT_DOWN:				_frameY = 7;
		break;
	default:
		break;
	}

	

}

void player::changeState()
{
	switch (_state)
	{
	case P_IDLE:
		_image = IMAGEMANAGER->findImage("루시안_IDLE");
		break;
	case P_WALK:

		break;
	case P_RUN:
		_image = IMAGEMANAGER->findImage("루시안_RUN");
		break;
	case P_ATTACK_NORMAL:
		_comboCount++;
		switch (_vCombo[_comboCount%3])
		{
		case P_ATTACK_STAB:
			_frameX = 0;
			_image = IMAGEMANAGER->findImage("루시안_ATTACK_STAB");
			break;
		case P_ATTACK_VERTICAL_HACK:
			_frameX = 0;
			_image = IMAGEMANAGER->findImage("루시안_ATTACK_VERTICAL_HACK");
			break;
		case P_ATTACK_HORIZONTAL_HACK:
			_frameX = 0;
			_image = IMAGEMANAGER->findImage("루시안_ATTACK_HORIZONTAL_HACK");
			break;
		default:
			break;
		}
		break;
	case P_COLLISION:
		break;
	default:
		break;
	}


}

void player::initStatus()
{

	// 꼭 받아와야하는것들
	// strcpy_s(_nickName, "즈코벨계기투전");
	// _type = P_TYPE_MIX;
	// _currentHp = 100;
	// _currentMp = 100;
	// _currentSp = 100;

	_image = IMAGEMANAGER->findImage("루시안_IDLE");
	_state = P_IDLE;
	_comboCount = 0;

	// 기본 초기화
	_hp = _equipHp = 0;
	_mp = _equipMp = 0;	
	_sp = _equipSp = 0;

	_stab = _equipStab = 0;
	_hack = _equipHack = 0;
	_int = _equipInt = 0;
	_def = _equipDef = 0;
	_mr = _equipMr = 0;
	_dex = _equipDex = 0;
	_agi = _equipAgi = 0;

	_currentExp = 0;

	_level = 1;
	_point = 0;

	_money = 10000;
	
	_cx = _target.x = WINSIZEX / 2;
	_by = _target.y = WINSIZEY / 2;
	
	

	this->load();

	// 저장된 캐릭터 정보 로드

	// 닉네임	
	// 레벨
	// 타입
	// 스테이터스 ( 직접찍은 )
	// 인벤토리
	// 장비
	// 스킬
	// 좌표 ( CX,BY)
	// 돈
	// 현재 경험치량
	// 현재 HP, MP, SP량


	// 로드로 불러올것들
	// strcpy_s(_nickName, "즈코벨계기투전");
	// _level = 1;
	// _type = P_TYPE_MIX;
	// 
	// _hp = _equipHp = 0;
	// _mp = _equipMp = 0;
	// _sp = _equipSp = 0;
	// 
	// _stab = _equipStab = 0;
	// _hack = _equipHack = 0;
	// _int = _equipInt = 0;
	// _def = _equipDef = 0;
	// _mr = _equipMr = 0;
	// _dex = _equipDex = 0;
	// _agi = _equipAgi = 0;
	// 
	// _money = 10000;
	// 
	// _currentExp = 0;
	// _point = 0;
	// 
	// _attackType = P_ATTACK_VERTICAL_HACK;
	// _currentHp = _maxHp = 200;
	// _currentMp = _maxMp = 200;
	// _currentSp = _maxSp = 200;

	// 캐릭터 타입별 초기 스테이터스 설정
	switch (_type)
	{
	case P_TYPE_MIX:
	{
		// 물리복합				
		_initHp = 220;
		_initMp = 50;
		_initSp = 1000;

		_initHack = 4;
		_initStab = 3;
		_initInt = 1;
		_initDef = 2;
		_initMr = 1;
		_initDex = 2;
		_initAgi = 2;

	} break;
	case P_TYPE_HACK:
	{
		// 베기				
		_initHp = 240;
		_initMp = 55;
		_initSp = 900;
		
		_initHack = 3;
		_initStab = 4;
		_initInt = 1;
		_initDef = 3;
		_initMr = 1;
		_initDex = 2;
		_initAgi = 1;
	} break;
	case P_TYPE_STAB:
	{
		// 찌르기				
		_initHp = 200;
		_initMp = 55;
		_initSp = 1100;
		
		_initHack = 4;
		_initStab = 3;
		_initInt = 1;
		_initDef = 1;
		_initMr = 1;
		_initDex = 2;
		_initAgi = 3;
	} break;
	default:
		break;
	}
	// 초기 이동속도
	_walkSpeed = 10;
	_runningSpeed = 16;


}

void player::changeExp()
{
	// 현재 레벨에 따라 maxExp와 requireExp가 결정된다.

	// 초기 경험치 량
	_requireExp = 50;

	for (int i = 0; i < _level-1; ++i)
	{
		_requireExp *= 2;
	}
	
	_maxExp = _requireExp * 2;
}

void player::checkLevel()
{
	changeExp();

	// 현재 경험치가 max를 넘으면 레벨업
	if (_currentExp >= _maxExp)
	{
		levelUp();
	}
	// 현재 경험치가 requireExp를 넘으면 레벨업 가능 ( 직접 레벨업 버튼을 누르기 위해 사용 )
	else if (_currentExp >= _requireExp)
	{
		_isPossibleLevelUp = true;
	}
	else if (_currentExp < _requireExp)
	{
		_isPossibleLevelUp = false;
	}


}

void player::levelUp()
{
	// 예외처리
	if (_isPossibleLevelUp)
	{
		_level++;
		_currentExp -= _requireExp;
		//changeExp();

		if (2 <= _level && _level <= 6) _point += 2;
		else if (7 <= _level && _level <= 22) _point += 3;
		else if (23 <= _level && _level <= 48) _point += 4;
		else if (49 <= _level && _level <= 80) _point += 5;
		else if (81 <= _level && _level <= 129) _point += 6;
		else if (130 <= _level && _level <= 175) _point += 7;
		else if (176 <= _level && _level <=	235) _point += 8;
		else if (236 <= _level && _level <= 255) _point += 9;
		else if (256 <= _level) _point += 10;


		_isPossibleLevelUp = false;
	}

}

void player::checkStatus()
{
	// 장비 스텟

	// 장비 스텟 초기화
	_equipHack = 0;
	_equipStab = 0;
	_equipInt = 0;
	_equipDef = 0;
	_equipMr = 0;
	_equipDex = 0;
	_equipAgi = 0;

	_equipHp = 0;
	_equipMp = 0;
	_equipSp = 0;

	// 모든 장비에 붇은 스텟을 더해준다
	for (int i = 0; i < _vEquipment.size(); ++i)
	{
		_equipHack += _im->getItem(_vEquipment[i])->getEquipItem()._hack;
		_equipStab += _im->getItem(_vEquipment[i])->getEquipItem()._stab;
		_equipInt += _im->getItem(_vEquipment[i])->getEquipItem()._int;
		_equipDef += _im->getItem(_vEquipment[i])->getEquipItem()._def;
		_equipMr += _im->getItem(_vEquipment[i])->getEquipItem()._mr;
		_equipDex += _im->getItem(_vEquipment[i])->getEquipItem()._dex;
		_equipAgi += _im->getItem(_vEquipment[i])->getEquipItem()._agi;
	}

	// 스텟에 따른 hp mp sp
	_hp = _hack * 15 + _stab * 7 + _int * 2 + _def * 40 + _mr * 2 + _dex * 5 + _agi * 8;
	_mp = _hack * 2 + _stab * 4 + _int * 6 + _def * 0 + _mr * 20 + _dex * 3 + _agi * 2;
	_sp = _hack * 4 + _stab * 8 + _int * 2 + _def * 3 + _mr * 6 + _dex * 30 + _agi * 10;


	// 최종 스텟
	_totalHack = _initHack + _hack + _equipHack;
	_totalStab = _initStab + _stab + _equipStab;
	_totalInt = _initInt + _int + _equipInt;
	_totalDef = _initDef + _def + _equipDef;
	_totalMr = _initMr + _mr + _equipMr;
	_totalDex = _initDex + _dex + _equipDex;
	_totalAgi = _initAgi + _agi + _equipAgi;

	_maxHp = _initHp + _hp + _equipHp;
	_maxMp = _initMp + _mp + _equipMp;
	_maxSp = _initSp + _sp + _equipSp;

	if (_type == P_TYPE_MIX)
	{
		_statusAtk = _hack*1.8 + _stab*1.8;
		_equipAtk = _equipHack*4.55 + _equipStab*4.55;
		_dexterity = 85 + (_totalStab + _totalHack) * 0.05;
		_avoidability = _totalAgi *	1.2 + 10 + (_totalDef + +_totalMr) * 0.15;
	}
	else if (_type == P_TYPE_HACK)
	{
		_statusAtk = _hack*2.1 + _stab*1.08;
		_equipAtk = _equipHack*6.67 + _equipStab * 1;
		_dexterity = 85 + _totalHack * 0.1;
		_avoidability = _totalAgi *	1.2 + 10 + _totalDef * 0.3;
	}
	else if (_type == P_TYPE_STAB)
	{
		_statusAtk = _hack*1.08 + _stab*2.1;
		_equipAtk = _equipHack * 1 + _equipStab*6.67;
		_dexterity = 85 + _totalStab * 0.1;
		_avoidability = _totalAgi *	1.2 + 10 + _totalDef * 0.3;
	}

	_minDamage = _statusAtk + (_equipAtk * 1) + 1;
	_maxDamage = _statusAtk + (_equipAtk * 1) + 1 + _statusAtk + (((_dex + _equipDex) * 3) / 18);
	_defense = _totalDef * 3;
	_magicRegi = _totalMr * 3;



}

void player::save()
{
	HANDLE file;
	DWORD write;

	// 파일 이름
	file = CreateFile(_currentCharacter.c_str(), GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	
	// 닉네임	
	WriteFile(file, _nickName, sizeof(char) * 128, &write, NULL);
	// 레벨
	WriteFile(file, &_level, sizeof(int), &write, NULL);
	// 타입
	WriteFile(file, &_type, sizeof(PLAYERATTACKTYPE), &write, NULL);
	// 공격타입
	for (int i = 0; i < 3; ++i)
	{
		WriteFile(file, &_vCombo[i], sizeof(PLAYERATTACKTYPE), &write, NULL);
	}
	// 스테이터스 ( 직접찍은 )
	WriteFile(file, &_stab, sizeof(int), &write, NULL);
	WriteFile(file, &_hack, sizeof(int), &write, NULL);
	WriteFile(file, &_int, sizeof(int), &write, NULL);
	WriteFile(file, &_def, sizeof(int), &write, NULL);
	WriteFile(file, &_mr, sizeof(int), &write, NULL);
	WriteFile(file, &_dex, sizeof(int), &write, NULL);
	WriteFile(file, &_agi, sizeof(int), &write, NULL);

	int size = _vInventory.size();
	// 인벤토리 크기
	WriteFile(file, &size, sizeof(int), &write, NULL);
	// 인벤토리
	for (int i = 0; i < _vInventory.size(); ++i)
	{
		WriteFile(file, &_vInventory[i], sizeof(int), &write, NULL);
	}

	size = _vEquipment.size();
	// 장비창 크기
	WriteFile(file, &size, sizeof(int), &write, NULL);
	// 장비창 
	for (int i = 0; i < _vEquipment.size(); ++i)
	{
		WriteFile(file, &_vEquipment[i], sizeof(int), &write, NULL);
	}

	size = _vSkill.size();
	// 스킬창 크기
	WriteFile(file, &size, sizeof(int), &write, NULL);
	// 스킬창 
	for (int i = 0; i < _vSkill.size(); ++i)
	{
		WriteFile(file, &_vSkill[i], sizeof(int), &write, NULL);
	}


	// 어떤 맵에 위치하고 있는지
	MAP currentMap = _mm->getCurrentMap();
	WriteFile(file, &currentMap, sizeof(MAP), &write, NULL);
	// 좌표 ( CX,BY)
	WriteFile(file, &_cx, sizeof(float), &write, NULL);
	WriteFile(file, &_by, sizeof(float), &write, NULL);
	// 돈
	WriteFile(file, &_money, sizeof(int), &write, NULL);
	// 현재 경험치량
	WriteFile(file, &_currentExp, sizeof(int), &write, NULL);
	// 현재 포인트량	
	WriteFile(file, &_point, sizeof(int), &write, NULL);
	// 현재 HP, MP, SP량
	WriteFile(file, &_currentHp, sizeof(int), &write, NULL);
	WriteFile(file, &_currentMp, sizeof(int), &write, NULL);
	WriteFile(file, &_currentSp, sizeof(int), &write, NULL);

	CloseHandle(file);
}

void player::load()
{
	HANDLE file;
	DWORD read;

	// 파일 이름
	file = CreateFile(_currentCharacter.c_str(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	// 닉네임	
	ReadFile(file, _nickName, sizeof(char) * 128, &read, NULL);
	// 레벨
	ReadFile(file, &_level, sizeof(int), &read, NULL);
	// 타입
	ReadFile(file, &_type, sizeof(CHARACTERTYPE), &read, NULL);
	// 공격타입
	for (int i = 0; i < 3; ++i)
	{
		PLAYERATTACKTYPE attackType;
		ReadFile(file, &attackType, sizeof(PLAYERATTACKTYPE), &read, NULL);
		_vCombo.push_back(attackType);
	}

	// 스테이터스 ( 직접찍은 )
	ReadFile(file, &_stab, sizeof(int), &read, NULL);
	ReadFile(file, &_hack, sizeof(int), &read, NULL);
	ReadFile(file, &_int, sizeof(int), &read, NULL);
	ReadFile(file, &_def, sizeof(int), &read, NULL);
	ReadFile(file, &_mr, sizeof(int), &read, NULL);
	ReadFile(file, &_dex, sizeof(int), &read, NULL);
	ReadFile(file, &_agi, sizeof(int), &read, NULL);


	int size;
	// 인벤토리 크기
	ReadFile(file, &size, sizeof(int), &read, NULL);
	// 인벤토리
	for (int i = 0; i < size; ++i)
	{
		int item1;
		ReadFile(file, &item1, sizeof(int), &read, NULL);
		addInventory(item1);
	}

	// 장비창 크기
	ReadFile(file, &size, sizeof(int), &read, NULL);
	// 장비창 
	for (int i = 0; i < size; ++i)
	{
		int item1;
		ReadFile(file, &item1, sizeof(int), &read, NULL);
		addEquipment(item1);
	}
	
	// 스킬창 크기
	ReadFile(file, &size, sizeof(int), &read, NULL);
	// 스킬창 
	for (int i = 0; i < size; ++i)
	{
		int skill;
		ReadFile(file, &skill, sizeof(int), &read, NULL);
		_vSkill.push_back(skill);
	}

	// 어떤 맵에 위치하고 있는지
	MAP currentMap;
	ReadFile(file, &currentMap, sizeof(MAP), &read, NULL);
	// 좌표 ( CX,BY)
	float cx, by;
	ReadFile(file, &cx, sizeof(float), &read, NULL);
	ReadFile(file, &by, sizeof(float), &read, NULL);
	_cx = cx;	_by = by;
	// 돈
	ReadFile(file, &_money, sizeof(int), &read, NULL);
	// 현재 경험치량
	ReadFile(file, &_currentExp, sizeof(int), &read, NULL);
	// 현재 포인트량	
	ReadFile(file, &_point, sizeof(int), &read, NULL);
	// 현재 HP, MP, SP량
	ReadFile(file, &_currentHp, sizeof(int), &read, NULL);
	ReadFile(file, &_currentMp, sizeof(int), &read, NULL);
	ReadFile(file, &_currentSp, sizeof(int), &read, NULL);

	CloseHandle(file);

}


void player::addInventory(int itemNum)
{
	_vInventory.push_back(itemNum);
	_um->getInventoryScreen()->addInventoryItem(itemNum);
}

void player::addEquipment(int itemNum)
{
	// 이미 착용하고 있는 장비가 있을 때
	for (int i = 0; i < _vEquipment.size(); ++i)
	{
		// 이미 있는 장비 타입이면 인벤토리에 넣고 장비에서 빼준다.
		if ((_vEquipment[i] % TYPE_EQUIPMENT) / (TYPE_HEAD % TYPE_EQUIPMENT) == (itemNum % TYPE_EQUIPMENT) / (TYPE_HEAD % TYPE_EQUIPMENT))
		{
			addInventory(_vEquipment[i]);
			_vEquipment.erase(_vEquipment.begin() + i);
		}
	}

	for (int i = 0; i < _vInventory.size(); ++i)
	{
		if (_vInventory[i] == itemNum) _vInventory.erase(_vInventory.begin() + i);
	}

	_vEquipment.push_back(itemNum);
	_um->getEquipmentScreen()->updateEquipmentItem();
}

void player::addHp(int hp)
{
	_currentHp += hp;	
	if (_currentHp >= _maxHp) _currentHp = _maxHp;
}

void player::addMp(int mp)
{
	_currentMp += mp; 
	if (_currentMp >= _maxMp) _currentMp = _maxMp;
}

void player::addSp(int sp)
{
	_currentSp += sp;
	if (_currentSp >= _maxSp) _currentSp = _maxSp;
}

void player::removeEquipment(int itemNum)
{
	for (int i = 0; i < _vEquipment.size(); ++i)
	{
		if (_vEquipment[i] == itemNum)
		{
			addInventory(_vEquipment[i]);
			_vEquipment.erase(_vEquipment.begin() + i);
			break;
		}
	}
}

int player::getRequirePoint(bool stab,bool hack,bool inte, bool def, bool mr, bool dex, bool agi)
{
	switch (_type)
	{
	case P_TYPE_MIX:
	{
		if (stab) return 1;
		else if (hack) return 1;
		else if (inte) return 3;
		else if (def) return 2;
		else if (mr) return 3;
		else if (dex) return 2;
		else if (agi) return 2;
	}break;
	case P_TYPE_HACK:
	{
		if (stab) return 2;
		else if (hack) return 1;
		else if (inte) return 3;
		else if (def) return 2;
		else if (mr) return 3;
		else if (dex) return 2;
		else if (agi) return 1;
	}break;
	case P_TYPE_STAB:
	{
		if (stab) return 1;
		else if (hack) return 2;
		else if (inte) return 3;
		else if (def) return 2;
		else if (mr) return 3;
		else if (dex) return 1;
		else if (agi) return 2;
	}break;
	default:
		break;
	}
	return 0;
}

void player::addDamage(int damage)
{
	if (damage < (_defense + _magicRegi)) damage = 1;
	else damage = (damage - (_defense + _magicRegi));
	_currentHp -= damage;
	EFFECTMANAGER->play("타격이펙트", _rc.left, _rc.top);
	if (_currentHp <= 0)
	{
		_isLive = false;
	}
}

bool player::isOnceClick()
{
	_target.x = (_ptMouse.x + _focus.left);
	_target.y = (_ptMouse.y + _focus.top);

	// 피킹이 됬니?
	if (_em->isOnceClick())
	{
		// 에너미를 잘 클릭햇다면 에너미의 좌표가 피킹이 되는지 확인
		if (_mm->isPickTile(_target.x, _target.y, true))
		{
			// 예외처리 ( 이미 공격을 하고 있는 중이면 넘어간다 )
			if (_isAttack) return true;
			// 평타 사거리 ( 100 ) 안에 있으면 바로 공격
			if (abs(getDistance( _cx,_by,_target.x,_target.y)) <= 100 )
			{
				_isMove = false;
				_isAttack = true;
				_state = P_ATTACK_NORMAL;
				changeState();
				changeDirection(_cx, _by, _target.x, _target.y);
			}
			// 아니면 이동 후 공격
			else
			{
				if (abs(_mm->getCurrentTileX() - _mm->getTargetTileX()) <= 1 &&
					abs(_mm->getCurrentTileY() - _mm->getTargetTileY()) <= 1)
					_isUseAStar = false;
				else _isUseAStar = true;

				_isMove = true;
				_isAttack = true;
				_state = P_RUN;
				changeState();
			}
		}

		return true;
	}

	if (_nm->isOnceClick()) return true;

	if (_mm->isOnceClick())
	{
		_isMove = true;
		_isAttack = false;
		_state = P_RUN;
		changeState();

		if (abs(_mm->getCurrentTileX() - _mm->getTargetTileX()) <= 1 &&
			abs(_mm->getCurrentTileY() - _mm->getTargetTileY()) <= 1)
			_isUseAStar = false;
		else _isUseAStar = true;

		return true;
	}

	return false;
}

