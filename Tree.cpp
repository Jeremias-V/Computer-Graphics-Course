#include "Tree.h"

Tree::Tree(){}

int Tree::DrawTree(float x, float y, float z) {

	glPushMatrix();

		glTranslatef(x, y, z);
		glRotatef(90, 1, 0, 0);

		for (int i = 0; i < 360; i += 15) {
			glPushMatrix();
			glTranslatef(0, 0, 0.2);
			glRotatef(135, 0, 1, 0);
			glRotatef(i, 1, 0, 1);
			glutSolidCylinder(0.02, 0.5, 10, 10);
			glPopMatrix();
		}
		
		glPushMatrix();
			glTranslatef(0, 0, -0.50);
			glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		glutSolidCylinder(0.2, 1.0, 20, 20);

	glPopMatrix();

	return 0;
}
