#include "Triangle.h"

Triangle::Triangle() {}

void Triangle::Draw(float x, float y, float z, float edge) {

    glPushMatrix();
        glTranslatef(x, y, z);
        glBegin(GL_TRIANGLES);
        glVertex3f(0, edge, 0);
        glVertex3f(-edge, 0, 0);
        glVertex3f(edge, 0, 0);
        glEnd();
    glPopMatrix();

}
