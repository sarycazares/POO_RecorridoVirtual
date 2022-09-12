#pragma once
#include <string>
using namespace std;
#include "glm.h"
#include "BMPLoader.h"


////////////////// EJEMPLO
namespace EDXFramework {

class Model {
private:
	GLMmodel* model;
	BMPClass texture;
	unsigned int textureId;
	unsigned int drawMode;
public:
	Model();
	Model(string modelPath, string texturePath, bool mode);
	virtual ~Model();
	void Draw();

};

}


/////////////////// Casa01
namespace EDXFramework {

	class Casa01 : private Model {
	private:
		GLMmodel* model;
		BMPClass texture;
		unsigned int textureId;
		unsigned int drawMode;
	public:
		Casa01();
		Casa01(string modelPath, string texturePath, bool mode);
		virtual ~Casa01();
		void Draw();
	};

}


/////////////////// Sol
namespace EDXFramework {

	class Sol : private Model {
	private:
		GLMmodel* model;
		BMPClass texture;
		unsigned int textureId;
		unsigned int drawMode;
	public:
		Sol();
		Sol(string modelPath, string texturePath, bool mode);
		virtual ~Sol();
		void Draw();
	};

}


