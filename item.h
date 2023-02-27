#pragma once
#include "gameNode.h"
#include <bitset>

// #define ITEMMAX 0x1111111111111 // ���/�Ҹ�ǰ/��Ÿ/�̺�Ʈ +  �Ӹ�/��/ + ��/��/����/ + ������ ��ȣ

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
	TYPE_HAT		= TYPE_HEAD + 100,					// ����
	// ARMOR
	TYPE_MAIL		= TYPE_ARMOR + 100,					// ����
	TYPE_LIGHTARMOR = TYPE_ARMOR + 200,					// ����Ʈ�Ƹ�
	// ARMS
	TYPE_SWORD		= TYPE_ARMS + 100,					// ���
	TYPE_KNIFE		= TYPE_ARMS + 200,					// ��
	// SUBARMS
	TYPE_SHIELD		= TYPE_SUBARMS + 100,				// ����
	TYPE_BAND		= TYPE_SUBARMS + 200,				// ���
	// FACE
	TYPE_NECKLACE	= TYPE_FACE + 100,					// �����
	// BACK
	TYPE_BROOM		= TYPE_BACK + 100,					// ���ڷ�
	// HAND
	TYPE_GLOVE		= TYPE_HAND + 100,					// �尩
	// FOOT
	TYPE_SHOES		= TYPE_FOOT + 100,					// �Ź�

};


enum CONSUMPTIONTYPE
{
	TYPE_PORTION = TYPE_CONSUMPTION + 1000,		// ����
};

enum CONSUMPTIONINDEX
{
	TYPE_HP = TYPE_PORTION + 100,					// HP����
	TYPE_MP = TYPE_PORTION + 200,					// MP����
	TYPE_SP = TYPE_PORTION + 300,					// SP����
};

enum ETCTYPE
{
	TYPE_MATERIAL = TYPE_ETC + 1000,				// ���
};

enum ETCINDEX
{
	TYPE_MONSTER = TYPE_MATERIAL + 100,				// ���� ���
};

struct tagEquipmentItem
{
	// ��� ������
	
	int _requireLevel = 0;						// ���� ����

	int _stab = 0;								// ��� ���ݷ�
	int _hack = 0;								// ���� ���ݷ�
	int _int = 0;								// ���� ���ݷ�
	int _def = 0;								// �������
	int _mr = 0;								// �������
	int _dex = 0;								// ���ߺ���
	int _agi = 0;								// ��ø / ȸ�Ǻ���

	bool _isEventItem = false;					// �̺�Ʈ �������ΰ�
};

struct tagConsumptionItem
{
	// �Һ� ������
	int _hp = 0;								// ü��
	int _mp = 0;								// ����
	int _sp = 0;								// ���׹̳�

	bool _isEventItem = false;					// �̺�Ʈ �������ΰ�
};

struct tagEtcItem
{
	bool _isEventItem = false;
};

class item : public gameNode
{
protected:
	int _itemNum;								// ������ ��ȣ
	
	char _itemName[128];						// ������ �̸�
	char _iconImageName[128];					// ������ ������ �̹��� Ű��
	char _useImageName[128];					// ������ �÷��̾� ���� �̹��� Ű��

	int _cost;									// ������ ����
	
	tagEquipmentItem _equipmentItem;			// ��� ������
	tagConsumptionItem _consumptionItem;		// �Һ� ������
	tagEtcItem _etcItem;						// ��Ÿ ������

	
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

