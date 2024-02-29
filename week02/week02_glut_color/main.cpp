#include <GL/glut.h>
void display()
{
    glColor3f(247/255.0,180/255.0,1710/255.0);

    glutSolidTeapot(0.3);
    glColor3f(217/255.0,130/255.0,120/255.0);
    glutSolidTeapot(0.2);
    glutSwapBuffers();
}
int main(int argc,char *argv[])

{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("GLUT Shapes");
    glutDisplayFunc(display);
    glutMainLoop();



}
