#include "EventoNevar.h"



EventoNevar::EventoNevar()
{

}

EventoNevar::EventoNevar(bool nevar) : _nevar(nevar)
{
	PosicionRandomX();
	PosicionRandomY();
	PosicionRandomZ();
	NevarNegativo(nevar);

}


int EventoNevar::PosicionRandomX()
{
	do {
		RandomX = (rand() % 130);
	} while (60 > RandomX);
	return RandomX;
}

int EventoNevar::PosicionRandomY()
{
	RandomY = rand() % 200;
	return RandomY;
}

int EventoNevar::PosicionRandomZ()
{
	do {
		RandomZ = (rand() % 290);
	} while (210 > RandomZ);
	return RandomZ;
}

int EventoNevar::NevarNegativo(bool nevar)
{
	if (nevar = true) {
		RandomX = RandomX - (RandomX * 2);
		RandomY = RandomY - (RandomY * 2);
		RandomZ = RandomZ - (RandomZ * 2);
		nevar = false;
	}
	else {
		nevar = true;
	}
	return nevar, RandomX, RandomY, RandomZ;
}

EventoNevar::~EventoNevar()
{
}
