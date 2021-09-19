#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glsl.h"
#include "./glm/glm.h"

class Object_3D
{

	GLMmodel* objmodel_ptr;

	public:
		Object_3D();
		void AbrirMalla(char *);
		void DibujarMalla(float x, float y, float z);
};

