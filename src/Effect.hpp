#ifndef INCLUDED_EFFECT
#define INCLUDED_EFFECT
#include"DxLib.h"
#define PI2 (3.141592654f*2)

class effect{
	int back;
	int mask;
	int overlay;
	int count;
public:
	effect();
	~effect();
	void graph();
};
#endif