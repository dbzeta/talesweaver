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
	//���� �����
	//C - FILE*
	//C++ -> ifstream, ofstream
	//API - CreateFile

	HANDLE file;

	char str[128] = "�����̴� ���߿� ����ο�����";
	DWORD write;

	file = CreateFile("�����ټ�����.txt", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);
}

void saveLoadTest::load()
{
	HANDLE file;

	char str[128];
	DWORD read;

	file = CreateFile("�����ټ�����.txt", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);

	CloseHandle(file);

	MessageBox(_hWnd, str, "������º!", MB_OK);
}