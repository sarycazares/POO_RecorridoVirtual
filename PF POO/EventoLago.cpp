#include "EventoLago.h"



EventoLago::EventoLago()
{
	PosicionRandomX();
	PosicionRandomY();
	PosicionRandomZ();
}

EventoLago::EventoLago(bool burbujear) : _burbujear(burbujear)
{
	PosicionRandomX();
	PosicionRandomY();
	PosicionRandomZ();
	LagoNegativo(burbujear);
}


int EventoLago::PosicionRandomX()
{
	RandomX = (rand() % 50);
	return RandomX;
}

int EventoLago::PosicionRandomY()
{
	RandomY = rand() % 20;
	return RandomY;
}

int EventoLago::PosicionRandomZ()
{
	RandomZ = (rand() % 50);
	return RandomZ;
}

int EventoLago::LagoNegativo(bool burbujear)
{
	if (burbujear = true) {
		RandomX = RandomX - (RandomX * 2);
		RandomY = RandomY - (RandomY * 2);
		RandomZ = RandomZ - (RandomZ * 2);
		burbujear = false;
	}
	else {
		burbujear = true;
	}
	return burbujear, RandomX, RandomY, RandomZ;
}

EventoLago::~EventoLago()
{
}
