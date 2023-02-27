#pragma once
#include "gameNode.h"
#include <bitset>

// #define ITEMMAX 0x1111111111111 // 장비/소모품/기타/이벤트 +  머리/손/ + 검/도/쉴드/ + 아이템 번호

enum ITEMTYPE
{
	TYPE_EQUIPMENT = 1 * 100000,
	TYPE_CONSUMPTION = 2 * 100000,
	TYPE_ETC = 3 * 100000,
};


enum EQUIPTYPE
{
	TYPE_HEAD			= TYPE_EQUIPMENT + 1 * 1000,
	TYPE_ARMOR			= TYPE_EQUIPMENT + 2 * 1000,
	TYPE_ARMS			= TYPE_EQUIPMENT + 3 * 1000,
	TYPE_SUBARMS		= TYPE_EQUIPMENT + 4 * 1000,
	TYPE_FACE			= TYPE_EQUIPMENT + 5 * 1000,
	TYPE_BACK			= TYPE_EQUIPMENT + 6 * 1000,
	TYPE_HAND			= TYPE_EQUIPMENT + 7 * 1000,
	TYPE_FOOT			= TYPE_EQUIPMENT + 8 * 1000,
	TYPE_EFFECT			= TYPE_EQUIPMENT + 9 * 1000,
	TYPE_ARTIFACT		= TYPE_EQUIPMENT + 10 * 1000,
	TYPE_RELIC_RIGHT	= TYPE_EQUIPMENT + 11 * 1000,
	TYPE_RELIC_LEFT		= TYPE_EQUIPMENT + 12 * 1000,
	TYPE_VEHICLE		= TYPE_EQUIPMENT + 13 * 1000,
};

enum EQUIPINDEX
{
	// HEAD
	TYPE_HAT		= TYPE_HEAD + 100,					// 모자
	// ARMOR
	TYPE_MAIL		= TYPE_ARMOR + 100,					// 메일
	TYPE_LIGHTARMOR = TYPE_ARMOR + 200,					// 라이트아머
	// ARMS
	TYPE_SWORD		= TYPE_ARMS + 100,					// 장검
	TYPE_KNIFE		= TYPE_ARMS + 200,					// 평도
	// SUBARMS
	TYPE_SHIELD		= TYPE_SUBARMS + 100,				// 쉴드
	TYPE_BAND		= TYPE_SUBARMS + 200,				// 밴드
	// FACE
	TYPE_NECKLACE	= TYPE_FACE + 100,					// 목걸이
	// BACK
	TYPE_BROOM		= TYPE_BACK + 100,					// 빗자루
	// HAND
	TYPE_GLOVE		= TYPE_HAND + 100,					// 장갑
	// FOOT
	TYPE_SHOES		= TYPE_FOOT + 100,					// 신발

};


enum CONSUMPTIONTYPE
{
	TYPE_PORTION = TYPE_CONSUMPTION + 1000,		// 포션
};

enum CONSUMPTIONINDEX
{
	TYPE_HP = TYPE_PORTION + 100,					// HP포션
	TYPE_MP = TYPE_PORTION + 200,					// MP포션
	TYPE_SP = TYPE_PORTION + 300,					// SP포션
};

enum ETCTYPE
{
	TYPE_MATERIAL = TYPE_ETC + 1000,				// 재료
};

enum ETCINDEX
{
	TYPE_MONSTER = TYPE_MATERIAL + 100,				// 몬스터 재료
};

struct tagEquipmentItem
{
	// 장비 아이템
	
	int _requireLevel = 0;						// 권장 레벨

	int _stab = 0;								// 찌르기 공격력
	int _hack = 0;								// 베기 공격력
	int _int = 0;								// 마법 공격력
	int _def = 0;								// 물리방어
	int _mr = 0;								// 마법방어
	int _dex = 0;								// 명중보정
	int _agi = 0;								// 민첩 / 회피보정

	bool _isEventItem = false;					// 이벤트 아이템인가
};

struct tagConsumptionItem
{
	// 소비 아이템
	int _hp = 0;								// 체력
	int _mp = 0;								// 마나
	int _sp = 0;								// 스테미나

	bool _isEventItem = false;					// 이벤트 아이템인가
};

struct tagEtcItem
{
	bool _isEventItem = false;
};

class item : public gameNode
{
protected:
	int _itemNum;								// 아이템 번호
	
	char _itemName[128];						// 아이템 이름
	char _iconImageName[128];					// 아이템 아이콘 이미지 키값
	char _useImageName[128];					// 아이템 플레이어 장착 이미지 키값

	int _cost;									// 아이템 가격
	
	tagEquipmentItem _equipmentItem;			// 장비 아이템
	tagConsumptionItem _consumptionItem;		// 소비 아이템
	tagEtcItem _etcItem;						// 기타 아이템

	
public:
	item();
	~item();

	HRESULT init();
	void release();
	void update();
	void render();

	void makeItem(long itemNum, string itemName,int requireLevel, int stab, int hack, int intelligence, int def, int mr, int dex, int agi, bool isEventItem);

	void makeEquipmentItem(string iconImageName, string itemName, int itemNum, int requireLevel, int stab, int hack, int intelligence, int def, int mr, int dex, int agi, int cost, bool isEventItem);
	void makeEquipmentItem(string useImageName, string iconImageName, string itemName, int itemNum, int requireLevel, int stab, int hack, int intelligence, int def, int mr, int dex, int agi, int cost, bool isEventItem);
	void makeConsumptionItem(string iconImageName, string itemName, int itemNum, int requireLevel, int hp, int mp, int sp, int cost, bool isEventItem);
	void makeConsumptionItem(string useImageName, string iconImageName, string itemName, int itemNum, int requireLevel, int hp, int mp, int sp, int cost, bool isEventItem);
	void makeEtcItem(string iconImageName, string itemName, int itemNum, bool isEventItem);

	int getItemNum() { return _itemNum; }
	char* getItemName() { return _itemName; }
	char* getIconImageName() { return _iconImageName; }
	char* getUseImageName() { return _useImageName; }
	int getIconImageLength() { return strlen(_iconImageName); }

	tagEquipmentItem getEquipItem() { return _equipmentItem; }
	tagConsumptionItem getConsumptionItem() { return _consumptionItem; }
	tagEtcItem getEtcItem() { return _etcItem; }

	int getCost() { return _cost; }

};

