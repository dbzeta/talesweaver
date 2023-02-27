#pragma once
#include "gameNode.h"
#include "skillNode.h"

class skills : public gameNode
{
protected:
	int _skillNum;						// ��ų �ѹ�

	image* _skillIconImage;				// ��ų ������ �̹���
	image* _skillUsingImage;			// ��ų ��� �̹���


	string _skillName;					// ��ų �̸�
	SKILLTYPE _skillType;				// ��ų Ÿ�� ( �˰迭 , ����迭 �� �� ... )
	int _damage;						// ������
	int _requirePoint;					// ��ų�� �ø������� �ʿ� ����ġ
	int _maxSkillLevel;					// �ִ� ��ų����
	int _currentSkillLevel;				// ���� ��ų����
	
	bool _isUse;						// ��ų�� ����ϱ����� bool����

public:
	skills();
	~skills();

	HRESULT init();
	void release();
	void update();
	void render();


};

