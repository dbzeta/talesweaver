#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;
	int _x, _y;
	float _width;

	image* _progressBarTop;
	image* _progressBarBottom;

	image* _loadingImage;

	bool _running;

public:
	HRESULT init(int x, int y, int width, int height);
	HRESULT init(char* frontImage, char* backImage, float x, float y, int width, int height);
	void release();
	void update();
	void render();

	void threadProc(void);

	static DWORD WINAPI threadFunc(LPVOID lParam);

	inline bool getRunning(void) { return _running; }

	void setGauge(float currentGauge, float maxGauge);

	bool setRunning(bool runnig) { _running = runnig; }

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }


	progressBar();
	~progressBar();
};

