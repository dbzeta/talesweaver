#include "stdafx.h"
#include "questManager.h"
#include "enemyManager.h"

questManager::questManager()
{
}


questManager::~questManager()
{
}

HRESULT questManager::init()		  
{

	huntingQuest* hq1 = new huntingQuest;
	hq1->init(1, 0, 201101, 200, false);
	hq1->setEmAddressLink(_em);
	hq1->setQuest(1, 20);
	_vTotalQuestList.push_back(hq1);

	huntingQuest* hq2 = new huntingQuest;
	hq2->init(2, 3, 201201, 400, false);
	hq2->setEmAddressLink(_em);
	hq2->setQuest(2, 20);
	_vTotalQuestList.push_back(hq2);

	huntingQuest* hq3 = new huntingQuest;
	hq3->init(3, 5, 104201, 1000, false);
	hq3->setEmAddressLink(_em);
	hq3->setQuest(3, 1);
	_vTotalQuestList.push_back(hq3);



	return S_OK;
}

void questManager::release()		  
{
	for (int i = 0; i < _vTotalQuestList.size(); ++i)
	{
		_vTotalQuestList[i]->release();
	}
}

void questManager::update()			  
{

	// if (KEYMANAGER->isOnceKeyDown(VK_F11))
	// {
	// 	HANDLE file;
	// 	DWORD write;
	// 
	// 	file = CreateFile("questdata.txt", GENERIC_WRITE, 0, NULL,
	// 		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	// 
	// 	int size = _vTotalQuestList.size();
	// 
	// 	WriteFile(file, &size, sizeof(int), &write, NULL);
	// 
	// 	for (int i = 0; i < _vTotalQuestList.size(); ++i)
	// 	{
	// 		WriteFile(file, _vTotalQuestList[i], sizeof(quest), &write, NULL);
	// 	}
	// 
	// 	CloseHandle(file);
	// }
	// 
	// if (KEYMANAGER->isOnceKeyDown(VK_F12))
	// {
	// 	HANDLE file;
	// 	DWORD read;
	// 
	// 	while (_vTotalQuestList.size())
	// 	{
	// 		// 불러오기 후 불러오기 누르면 터지는데 이유가 뭐지??
	// 		SAFE_DELETE(_vTotalQuestList[0]);
	// 		_vTotalQuestList.erase(_vTotalQuestList.begin());
	// 	}
	// 
	// 	int vectorSize;
	// 
	// 	file = CreateFile("questdata.txt", GENERIC_READ, 0, NULL,
	// 		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	// 
	// 	ReadFile(file, &vectorSize, sizeof(int), &read, NULL);
	// 
	// 	for (int k = 0; k < vectorSize; ++k)
	// 	{
	// 		quest* _quest = new quest;
	// 		ReadFile(file, _quest, sizeof(quest), &read, NULL);
	// 		_vTotalQuestList.push_back(_quest);
	// 
	// 	}
	// }

	for (int i = 0; i < _vTotalQuestList.size(); ++i)
	{
		_vTotalQuestList[i]->update();
	}

}

void questManager::render()			  
{
	for (int i = 0; i < _vTotalQuestList.size(); ++i)
	{
		_vTotalQuestList[i]->render();
	}
}