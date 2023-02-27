#include "stdafx.h"
#include "saveLoadTest.h"


saveLoadTest::saveLoadTest()
{
}


saveLoadTest::~saveLoadTest()
{
}

void saveLoadTest::update()
{
	if (KEYMANAGER->isOnceKeyDown('T')) save();
	if (KEYMANAGER->isOnceKeyDown('Y')) load();


}

void saveLoadTest::save()
{
	//파일 입출력
	//C - FILE*
	//C++ -> ifstream, ofstream
	//API - CreateFile

	HANDLE file;

	char str[128] = "지용이는 나중에 강사로오지용";
	DWORD write;

	file = CreateFile("뒤진다성보미.txt", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);
}

void saveLoadTest::load()
{
	HANDLE file;

	char str[128];
	DWORD read;

	file = CreateFile("뒤진다성보미.txt", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);

	CloseHandle(file);

	MessageBox(_hWnd, str, "지용이쨘!", MB_OK);
}