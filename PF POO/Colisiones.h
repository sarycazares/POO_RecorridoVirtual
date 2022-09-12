
#include <stdlib.h>
#include <cmath>
#include <math.h>

//template <class T> class Colision {
//public:
//
//	int AX, AY, AZ, BX, BY, BZ, CX, CY, CZ, DX, DY, DZ, aX, aY, aZ, bX, bY, bZ, cX, cY, cZ, dX, dY, dZ;
//	int numEspacio;
//
//	Colision() {};
//
//
//	void CalculoRecPosicion(abs(T x), abs(T y), abs(T z), T numEspacio) {
//
//		aX = x - numEspacio;        aZ = z - numEspacio;
//		bX = x + numEspacio;		bZ = z - numEspacio;
//		cX = x + numEspacio;		cZ = z + numEspacio;
//		dX = x - numEspacio;		dZ = z + numEspacio;
//
//	}
//
//	bool ColisionRectangular(T AX, T  AZ, T  BX, T  BZ, T  CX, T  CZ, T  DX, T  DZ, T  aX, T  aZ, T  bX, T  bZ, T  cX, T  cZ, T  dX, T dZ) {
//
//		if (C < d || D > c || A < d || D > a) {
//			return true;
//		}
//		else {
//			return false;
//		}
//
//	}
//
//}

class Colision {
	public:

	int bx, by, lx1, ly1, lx2, ly2;
	bool ColisionPared;


 
	Colision() {};

	template <class T>
	bool EsferaLinea(T _bx, T _by, T _br, T _lx1, T _ly1, T _lx2, T _ly2)
	{
		// Largo de la linea
		float distanciaX = _lx1 - _lx2;
		float distanciaY = _ly1 - _ly2;
		float TamañoLinea = sqrt(distanciaX*distanciaX + distanciaY*distanciaY);

		// Resolvemos R
		float r = (((_bx - _lx1)*(_lx2 - _lx1)) + ((_by - _ly1)*(_ly2 - _ly1))) / pow(TamañoLinea, 2);

		// Obtenemos el X e Y mas cercano de la linea a la esfera
		float closestX = _lx1 + r * (_lx2 - _lx1);
		float closestY = _ly1 + r * (_ly2 - _ly1);

		// Obtenemos distancia de este punto a la esfera
		float DistanciaPuntoX = closestX - _bx;
		float DistanciaPuntoY = closestY - _by;
		float DistanciaPunto = sqrt(DistanciaPuntoX*DistanciaPuntoX + DistanciaPuntoY*DistanciaPuntoY);

		// Si la distancia es menor o igual al radio de la esfera, es colision
		if (DistanciaPunto <= _br)
			return true;
		else
			return false;
	}


	template <class T>
	bool PuntoLinea(T bx, T by, T lx1, T ly1, T lx2, T ly2)
	{
		if (bx < 0 && ColisionPared == true) {
			bx = abs(bx);
			lx1 = abs(lx1);
			lx2 = abs(lx2);
		}

		if (by < 0 && ColisionPared == false) {
			by = abs(by);
			ly1 = abs(ly1);
			ly2 = abs(ly2);
		}

		if (bx >= lx1 && bx <= lx2 && by <= ly1 && by >= ly2) {
			return true;
		}
		else {
			return false;
		}
	}
};