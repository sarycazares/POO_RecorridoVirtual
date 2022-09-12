#include "Random.h"

Random::Random()
{
}

Random::Random(int RandX, int RandY, int RandZ)
{
	RandomX = RandX;
	RandomY = RandY;
	RandomZ = RandZ;
}

int Random::PosicionRandomX()
{
	RandomX = rand() % 50;
	return RandomX;
}

int Random::PosicionRandomY()
{
	RandomY = rand() % 20;
	return RandomY;
}

int Random::PosicionRandomZ()
{
	RandomZ = rand() % 50;
	return RandomZ;
}

//void Random::PosicionRandom()
//{
//}
