#include  <GL/glut.h>
#include <math.h>

void display()
{
    glBegin(GL_POLYGON);
        for(float a=0;a<=3.1415*2;a+=0.1)
        {
            glVertex2f(0.2*cos(a)+0.5,0.2*sin(a)+0.5);
        }
    glEnd();
    glutSwapBuffers();
}
int main(int argc, char*argv[])
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("2024�q���Ͼǲ�01�P");
    glutDisplayFunc(display);
    glutMainLoop();

}
