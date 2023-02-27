#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}

HRESULT item::init()
{
	_itemNum = 0;
	memset(_itemName, 0, sizeof(char) * 128);
	memset(_iconImageName, 0, sizeof(char) * 128);
	memset(_useImageName, 0, sizeof(char) * 128);

	return S_OK;
}

void item::release()
{
	
}

void item::update()	
{
	
}

void item::render()	
{
	
}


void item::makeEquipmentItem(string iconImageName, string itemName, int itemNum, int requireLevel, int stab, int hack, int intelligence, int def, int mr, int dex, int agi, int cost, bool isEventItem)
{
	strcpy(_iconImageName, iconImageName.c_str());
	_itemNum = itemNum;
	strcpy(_itemName, itemName.c_str());
	_cost = cost;
	_equipmentItem._requireLevel = requireLevel;
	_equipmentItem._stab = stab;
	_equipmentItem._hack = hack;
	_equipmentItem._int = intelligence;
	_equipmentItem._def = def;
	_equipmentItem._mr = mr;
	_equipmentItem._dex = dex;
	_equipmentItem._agi = agi;
	_equipmentItem._isEventItem = isEventItem;
}

void item::makeEquipmentItem(string useImageName, string iconImageName, string itemName, int itemNum, int requireLevel, int stab, int hack, int intelligence, int def, int mr, int dex, int agi, int cost, bool isEventItem)
{
	strcpy(_useImageName, useImageName.c_str());
	strcpy(_iconImageName, iconImageName.c_str());
	_itemNum = itemNum;
	strcpy(_itemName, itemName.c_str());
	_cost = cost;
	_equipmentItem._requireLevel = requireLevel;
	_equipmentItem._stab = stab;
	_equipmentItem._hack = hack;
	_equipmentItem._int = intelligence;
	_equipmentItem._def = def;
	_equipmentItem._mr = mr;
	_equipmentItem._dex = dex;
	_equipmentItem._agi = agi;
	_equipmentItem._isEventItem = isEventItem;
}
void item::makeConsumptionItem(string iconImageName, string itemName, int itemNum, int requireLevel, int hp, int mp, int sp, int cost, bool isEventItem)
{
	strcpy(_iconImageName, iconImageName.c_str());
	_itemNum = itemNum;
	strcpy(_itemName, itemName.c_str());
	_cost = cost; 
	_consumptionItem._hp = hp;
	_consumptionItem._mp = mp;
	_consumptionItem._sp = sp;
	_consumptionItem._isEventItem = isEventItem;
	
}
void item::makeConsumptionItem(string useImageName, string iconImageName, string itemName, int itemNum, int requireLevel, int hp, int mp, int sp, int cost, bool isEventItem)
{
	strcpy(_useImageName, useImageName.c_str());
	strcpy(_iconImageName, iconImageName.c_str());
	_itemNum = itemNum;
	strcpy(_itemName, itemName.c_str());
	_cost = cost;
	_consumptionItem._hp = hp;
	_consumptionItem._mp = mp;
	_consumptionItem._sp = sp;
	_consumptionItem._isEventItem = isEventItem;

}


void item::makeEtcItem(string iconImageName, string itemName, int itemNum, bool isEventItem)
{
	strcpy(_iconImageName, iconImageName.c_str());
	_itemNum = itemNum;
	strcpy(_itemName, itemName.c_str());
	_etcItem._isEventItem = isEventItem;
}

void item::makeItem(long itemNum, string itemName, int requireLevel, int stab, int hack, int intelligence, int def, int mr, int dex, int agi, bool isEventItem)
{
	// 대분류 ( 장비 소모품 기타 이벤트 )

	if (itemNum / TYPE_EQUIPMENT == 1)
	{
		_itemNum = itemNum;
		strcpy(_itemName, itemName.c_str());
		_equipmentItem._requireLevel = requireLevel;
		_equipmentItem._stab = stab;
		_equipmentItem._hack = hack;
		_equipmentItem._int = intelligence;
		_equipmentItem._def = def;
		_equipmentItem._mr = mr;
		_equipmentItem._dex = dex;
		_equipmentItem._agi = agi;
		_equipmentItem._isEventItem = isEventItem;

	}
	else if (itemNum / TYPE_EQUIPMENT == 2)
	{
		_itemNum = itemNum;
		strcpy(_itemName, itemName.c_str());
		_consumptionItem._hp = stab;
		_consumptionItem._mp = hack;
		_consumptionItem._sp = intelligence;
		_consumptionItem._isEventItem = isEventItem;
	}
	else if (itemNum / TYPE_ETC == 3) 
	{
		_itemNum = itemNum;		
		strcpy(_itemName, itemName.c_str());
	}
}
