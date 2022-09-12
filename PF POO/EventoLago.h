#pragma once
#include "Random.h"

class EventoLago : public Random
{
public:
	int _RandomX;
	int _RandomY;
	int _RandomZ;
	bool _burbujear;

	EventoLago();
	EventoLago(bool burbujear);
	int PosicionRandomX();
	int PosicionRandomY();
	int PosicionRandomZ();
	int LagoNegativo(bool burbujear);
	~EventoLago();
};

