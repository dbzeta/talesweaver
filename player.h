#pragma once
#include "gameNode.h"

class enemyManager;
class npcManager;
class mapManager;
class uiManager;
class itemManager;

class enemy;

enum PLAYERATTACKTYPE
{
	P_ATTACK_STAB,
	P_ATTACK_VERTICAL_HACK,
	P_ATTACK_HORIZONTAL_HACK,
};

enum PLAYERDIRECTION
{
	P_DIR_LEFT,
	P_DIR_RIGHT,
	P_DIR_UP,
	P_DIR_DOWN,
	P_DIR_LEFT_UP,
	P_DIR_LEFT_DOWN,
	P_DIR_RIGHT_UP,
	P_DIR_RIGHT_DOWN,
};

enum PLAYERSTATE
{
	P_IDLE,
	P_WALK,
	P_RUN,
	P_ATTACK_NORMAL,
	P_ATTACK_SKILL,
	P_COLLISION,
};


enum CHARACTERTYPE
{
	P_TYPE_MIX,			// ��������
	P_TYPE_HACK,		// ����
	P_TYPE_STAB,		// ���
};


class player : public gameNode
{
private:
	enemyManager* _em;
	npcManager* _nm;
	mapManager* _mm;

	uiManager* _um;
	itemManager* _im;

	vector<int> _vPath;									// ���̽�Ÿ�� ����Ͽ� ���� ���� ���;

	vector<PLAYERATTACKTYPE> _vCombo;							// �޺�

	image* _image;
	int _frameX, _frameY;
	int _count;
	RECT _rc;
	float _cx, _by;
	int _width, _height;
	float _angle;

	int _comboCount;
	
	POINT _target;									// ���콺�� Ŭ���� ���� Ÿ��
	POINT _aStarTarger;								// ���̽�Ÿ ���� ���Ǵ� Ÿ��;

	enemy* _attackTarget;							// ������ Ÿ��

	bool _isLive;									// ����ִ���
	bool _isPossibleLevelUp;						// �������� �����Ѱ�

	bool _isUseAStar;								// ���̽�Ÿ�� ��ߵǴ°�
	bool _isAttack;									// ��..������?
	bool _isMove;									// �����ϱ�?
	bool _isAutoAttack;								// �ڵ� ����.

	PLAYERSTATE _state;
	PLAYERDIRECTION _dir;				

	char _nickName[128];							// ĳ���� �̸�

	int _level;										// ����

	int _currentExp;								// ���� ����ġ
	int _requireExp;								// �ʿ� ����ġ 
	int _maxExp;									// �ִ� ����ġ 

	int _currentHp;									// ���� hp
	int _currentMp;									// ���� mp
	int _currentSp;									// ���� sp
	
	// Ÿ�� (���� , ��� ,  �������� )
	CHARACTERTYPE _type;							// ĳ���� Ÿ��


	// ���� ���� = �ʱ� ���� + //( �������� ����ġ ) + ���� ���� ���� + ��� ����
	
	// �ʱ� ���� Status
	int _initStab;
	int _initHack;
	int _initInt;
	int _initDef;
	int _initMr;
	int _initDex;
	int _initAgi;

	int _initHp;
	int _initMp;
	int _initSp;

	// ���� ���� ����
	int _point;										// ������ ���� �� �ִ� ����Ʈ
	int _requirePoint;										// ������ ���� �� �ִ� �ʿ�����Ʈ

	int _hack;
	int _stab;
	int _int;
	int _def;
	int _mr;
	int _dex;
	int _agi;
	
	// ���ݿ� ���� hp mp sp
	int _hp;										
	int _mp;										
	int _sp;										

	// ��� ����
	int _equipStab;
	int _equipHack;
	int _equipInt;
	int _equipDef;
	int _equipMr;
	int _equipDex;
	int _equipAgi;

	int _equipHp;
	int _equipMp;
	int _equipSp;

	// ���� ����
	int _totalStab;
	int _totalHack;
	int _totalInt;
	int _totalDef;
	int _totalMr;
	int _totalDex;
	int _totalAgi;


	// ��Ʋ					  
	int _maxHp;					// ���� hp								
	int _maxMp;					// ���� mp								
	int _maxSp;					// ���� sp

	int _statusAtk;				// ���� ���ݷ�
	int _equipAtk;				// ��� ���ݷ�
	int _minDamage;				// �ּ� ������
	int _maxDamage;				// �ִ� ������
	int _defense;				// ���� ����
	int _magicRegi;				// ���� ����
	int _dexterity;				// ���߷� 
	int	_avoidability;			// ȸ����
	int _walkSpeed;				// �ȱ� �ӵ�
	int _runningSpeed;			// �޸��� �ӵ�


	// ��
	int _money;										// money ( SEED )

	// �κ��丮â �� ���â
	vector<int> _vInventory;						// inventory
	vector<int> _vEquipment;						// equipment
	vector<int> _vSkill;							// skill

public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	void move();
	void attack();

	void changeDirection(float startX, float startY, float endX, float endY);
	void changeState();
	void initStatus();

	void changeExp();

	void checkLevel();
	void levelUp();
	
	void checkHp() { if (_currentHp <= 0) _isLive = false; }

	void checkStatus();

	void load();
	void save();
		
	void setMoney(int money) { _money = money; }

	void setState(PLAYERSTATE state) { _state = state; }
	void setTarget(int targetX, int targetY) { _target.x = targetX; _target.y = targetY; }

	void setAttackTarget(enemy* attackTarget) { _attackTarget = attackTarget; }

	void addMoney(int money) { _money += money; }			// �� �߰� Ȥ�� ����	
	void addInventory(int itemNum);							//
	void addEquipment(int itemNum);							//

	void addHp(int hp);										// 
	void addMp(int mp);										// 
	void addSp(int sp);										// 

	void addStab()	{ _stab += 1; addPoint(-1 * getRequirePoint(true, false, false, false, false, false, false)); }										// 
	void addHack()	{ _hack += 1; addPoint(-1 * getRequirePoint(false, true, false, false, false, false, false)); }										// 
	void addInt()	{ _int += 1; addPoint(-1 * getRequirePoint(false, false, true, false, false, false, false)); }											// 
	void addDef()	{ _def += 1; addPoint(-1 * getRequirePoint(false, false, false, true, false, false, false)); }											// 
	void addMr()	{ _mr += 1;   addPoint(-1 * getRequirePoint(false, false, false, false, true, false, false)); }												// 
	void addDex()	{ _dex += 1; addPoint(-1 * getRequirePoint(false, false, false, false, false, true, false)); }											// 
	void addAgi()	{ _agi += 1; addPoint(-1 * getRequirePoint(false, false, false, false, false, false, true)); }											// 

	void addPoint(int point) { _point += point; }
	void addExp(int exp) { _currentExp += exp; }

	void removeEquipment(int itemNum);


	RECT getRect() { return _rc; }

	int getLevel() { return _level; }
	char* getNickName() { return _nickName; }
	CHARACTERTYPE getType() { return _type; }

	int getCurrentExp() { return _currentExp; }
	int getRequireExp() { return _requireExp; }
	int getMaxExp() { return _maxExp; }

	// equipment Status
	int getEquipStab() { return _equipStab; }
	int getEquipHack() { return _equipHack; }
	int getEquipInt() { return _equipInt; }
	int getEquipDef() { return _equipDef; }
	int getEquipMr() { return _equipMr; }
	int getEquipDex() { return _equipDex; }
	int getEquipAgi() { return _equipAgi; }


	// status
	int getStab() { return _stab + _initStab; }
	int getHack() { return _hack + _initHack; }
	int getInt() { return _int + _initInt; }
	int getDef() { return _def + _initDef; }
	int getMr() { return _mr + _initMr; }
	int getDex() { return _dex + _initDex; }
	int getAgi() { return _agi + _initAgi; }

	int getCurrentHp() { return _currentHp; }
	int getCurrentMp() { return _currentMp; }
	int getCurrentSp() { return _currentSp; }
	int getMaxHp() { return _maxHp; }
	int getMaxMp() { return _maxMp; }
	int getMaxSp() { return _maxSp; }

	int getMoney() { return _money; }
	int getPoint() { return _point; }
	int getRequirePoint(bool stab, bool hack, bool inte, bool def, bool mr, bool dex, bool agi);

	// battle
	int getAtk() { return _statusAtk + _equipAtk; }
	int getMinDamage() { return _minDamage; }
	int getMaxDamage() { return _maxDamage; }
	int getDefense() { return _defense; }
	int getMagicRegidense() { return _magicRegi; }
	int getDexterity() { return _dexterity; }
	int getAvoidability() { return _avoidability; }
	int getWalkSpeed() { return _walkSpeed; }
	int getRunningSpeed() { return _runningSpeed; }


	vector<int> getInventory() { return _vInventory; }
	vector<int>	getEquipment() { return _vEquipment; }
	vector<int>	getSkill() { return _vSkill; }

	bool getIsPossibleLevelUp() { return _isPossibleLevelUp; }

	void setEmAddressLink(enemyManager* em) { _em = em; }
	void setNmAddressLink(npcManager* nm) { _nm = nm; }
	void setMmAddressLink(mapManager* mm) { _mm = mm; }
	void setUmAddressLink(uiManager* um) { _um = um; }
	void setEmAddressLink(itemManager* im) { _im = im; }

	// 
	void setPath(vector<int> path) { _vPath = path; }

	int getX() { return _cx; }
	int getY() { return _by; }

	int getFrameX() { return _frameX; }
	int getFrameY() { return _frameY; }

	void addDamage(int damage);

	bool isOnceClick();
	
	void setCombo(int comboIndex, PLAYERATTACKTYPE attackType) { _vCombo[comboIndex] = attackType; }
};

// ĳ���� ���� -> ĳ���� Ŭ�� (������ �ε�) 

// 