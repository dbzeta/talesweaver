#pragma once
//혹시 구버전 쓰는 사람 있을까봐 걸어둠
#include <cmath>

#define DEG_TO_RAD 0.017453f	//1도에 대한 라디안 값
#define PI 3.141592654f
#define PI2 PI * 2
#define PI8 float(PI / 8.0f)
#define PI16 float(PI / 16.0f)
#define PI32 float(PI / 32.0f)
#define PI64 float(PI / 64.0f)
#define PI128 float(PI / 128.0f)


#define FLOAT_EPSILON	0.001f		//실수의 가장 작은 단위 (그리스어)
#define FLOAT_TO_INT(f1) static_cast<int>(f1 + FLOAT_EPSILON)
#define FLOAT_EQUAL(f1, f2) (fabs(f1, f2) <= FLOAT_EPSILON)


namespace BLUE_UTIL
{
	//거리
	float getDistance(float startX, float startY, float endX, float endY);
	
	//각도
	float getAngle(float x1, float y1, float x2, float y2);
}