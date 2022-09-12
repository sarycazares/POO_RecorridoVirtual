
#pragma once
#include <stdlib.h>

class Random
{
protected:
	int RandomX;
	int RandomY;
	int RandomZ;
	bool nevar;

public:
	Random();
	Random(int RandX, int RandY, int RandZ);
	virtual int PosicionRandomX();
	virtual int PosicionRandomY();
	virtual int PosicionRandomZ();


};


/*
RandomX = rand() % 50;
RandomY = rand() % 20;
RandomZ = rand() % 50;
*/