#include <stdio.h>
#include <GL/glut.h>

void mouse(int button,int state,int x,int y)
{
    printf("Hello Mouse!\n");
}
void display()
{
    glutSolidTeapot(0.3);
    glutSwapBuffers();
}
int main(int argc,char *argv[])

{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("week 03 mouse");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
}
