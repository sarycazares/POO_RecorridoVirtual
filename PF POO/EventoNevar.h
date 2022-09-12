#pragma once

#include "Random.h"

class EventoNevar : public Random
{
public:

	int _RandomX;
	int _RandomY;
	int _RandomZ;
	bool _nevar;
	EventoNevar();
	EventoNevar(bool nevar);
	int PosicionRandomX();
	int PosicionRandomY();
	int PosicionRandomZ();
	int NevarNegativo(bool nevar);
	~EventoNevar();
};

