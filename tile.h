#pragma once
#include "gameNode.h"
#include <string>

class tile : public gameNode
{
private:
	int _idX, _idY;

	POINT _center;
	RECT _rc;

	//A* 공식
	//F = G + H
	//F == TotalCost
	//G == 시작점으로부터 현재 노드까지 비용
	//H == 현재 노드부터 도착점까지 비용

	float _totalCost;		//F
	float _costFromStart;	//G
	float _costToGoal;		//H

	bool _isOpen;
	
	tile* _parentNode;

	COLORREF _color;
	HBRUSH _brush;
	HPEN _pen;

	string _attribute;


public:
	tile();
	~tile();

	HRESULT init(int idX, int idY);
	void release();
	void update();
	void render();

	int getIdX() { return _idX; }
	int getIdY() { return _idY; }

	void setColor(COLORREF color)
	{
		DeleteObject(_brush);
		_color = color;
		_brush = CreateSolidBrush(_color);
	}

	RECT getRect() { return _rc; }

	void setCenter(POINT center) { _center = center; }
	POINT getCenter() { return _center; }

	void setAttribute(string str) { _attribute = str; }
	string getAttribute() { return _attribute; }

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }

	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	void setParentNode(tile* t) { _parentNode = t; }
	tile* getParentNode() { return _parentNode; }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen(){ return _isOpen; }

};

