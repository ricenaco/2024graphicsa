///先把 week08-1_glm_gundam 的程式貼上來
///等一下, 要再加貼圖的 18行程式
#include <opencv/highgui.h> ///使用 OpenCV 2.1 比較簡單, 只要用 High GUI 即可
#include <opencv/cv.h>
#include <GL/glut.h>
#include <stdio.h>


int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCV讀圖
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV轉色彩 (需要cv.h)
    glEnable(GL_TEXTURE_2D); ///1. 開啟貼圖功能
    GLuint id; ///準備一個 unsigned int 整數, 叫 貼圖ID
    glGenTextures(1, &id); /// 產生Generate 貼圖ID
    glBindTexture(GL_TEXTURE_2D, id); ///綁定bind 貼圖ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖T, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖S, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// 貼圖參數, 放大時的內插, 用最近點
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// 貼圖參數, 縮小時的內插, 用最近點
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}
#include <GL/glut.h>
#include "glm.h"
GLMmodel*pmodel=NULL;
GLMmodel*handa=NULL;
GLMmodel*handb=NULL;
GLMmodel*upperA=NULL;
GLMmodel*lowerA=NULL;
FILE*fin=NULL;
FILE*fout=NULL;
GLMmodel*body=NULL;
void drawbody(void)
{
    if (!body) {
	body = glmReadOBJ("data/body.obj");
	if (!body) exit(0);
	glmUnitize(body);
	glmFacetNormals(body);
	glmVertexNormals(body, 90.0);
    }

    glmDraw(body, GLM_SMOOTH | GLM_TEXTURE);
}
void drawhanda(void)
{
    if (!handa) {
	handa = glmReadOBJ("data/handa.obj");
	if (!handa) exit(0);
	glmUnitize(handa);
	glmFacetNormals(handa);
	glmVertexNormals(handa, 90.0);
    }

    glmDraw(handa, GLM_SMOOTH | GLM_TEXTURE);
}
void drawhandb(void)
{
    if (!handb) {
	handb = glmReadOBJ("data/handb.obj");
	if (!handb) exit(0);
	glmUnitize(handb);
	glmFacetNormals(handb);
	glmVertexNormals(handb, 90.0);
    }

    glmDraw(handb, GLM_SMOOTH | GLM_TEXTURE);
}
void drawupperA(void)
{
    if (!upperA) {
	upperA = glmReadOBJ("data/upperA.obj");
	if (!upperA) exit(0);
	glmUnitize(upperA);
	glmFacetNormals(upperA);
	glmVertexNormals(upperA, 90.0);
    }

    glmDraw(upperA, GLM_SMOOTH | GLM_TEXTURE);
}
void drawlowerA(void)
{
    if (!lowerA) {
	lowerA = glmReadOBJ("data/lowerA.obj");
	if (!lowerA) exit(0);
	glmUnitize(lowerA);
	glmFacetNormals(lowerA);
	glmVertexNormals(lowerA, 90.0);
    }

    glmDraw(lowerA, GLM_SMOOTH | GLM_TEXTURE);
}
void myBody()
{
    glPushMatrix();
        glColor3f(1,0,0);
        glutSolidCube(0.6);
    glPopMatrix();
}

float oldangleX[10]={},newangleX[10]={};
float oldangleY[10]={},newangleY[10]={};
float angleX[10]={},angleY[10]={};
int angleID=0;
int oldX=0, oldY=0;
void motion(int x,int y)
{
    angleY[angleID]-=x-oldX;
    angleX[angleID]-=y-oldY;
    oldX=x;
    oldY=y;
    glutPostRedisplay();
}
void mouse(int button,int state, int x,int y)
{
    oldX=x;
    oldY=y;
}
void timer(int t)
{
    glutTimerFunc(10,timer,t+1);
    if(t%20==0)
    {
        if(fin==NULL) fin=fopen("angle.txt","r");
        for(int i=0;i<10;i++)
        {
            oldangleX[i]=newangleX[i];
            oldangleY[i]=newangleY[i];
            fscanf(fin,"%f",&newangleX[i]);
            fscanf(fin,"%f",&newangleY[i]);
        }
    }
    float alpha=(t%20)/20.0;
    for(int i=0;i<10;i++)
    {
        angleX[i]=newangleX[i]*alpha+oldangleX[i]*(1-alpha);
        angleY[i]=newangleY[i]*alpha+oldangleY[i]*(1-alpha);
    }
    glutPostRedisplay();
}
void keyboard(unsigned char key,int x,int y)
{
    if(key=='p')
    {
        glutTimerFunc(0,timer,0);
    }
    if(key=='r')
    {
        if(fin==NULL) fin=fopen("angle.txt","r");
        for(int i=0;i<10;i++)
        {
            fscanf(fin,"%f",&angleX[i]);
            fscanf(fin,"%f",&angleY[i]);
        }
        glutPostRedisplay();
    }else if(key=='s')
    {
        if(fout==NULL) fout=fopen("angle.txt","w+");
        for(int i=0;i<10;i++)
        {
            printf("%.1f ",angleX[i]);
            printf("%.1f ",angleY[i]);
            fprintf(fout,"%1.f ",angleX[i]);
            fprintf(fout,"%1.f ",angleY[i]);
        }
        printf("\n");
        fprintf(fout,"\n");
    }
    if(key=='0') angleID=0;
    if(key=='1') angleID=1;
    if(key=='2') angleID=2;
    if(key=='3') angleID=3;
    if(key=='4') angleID=4;
    if(key=='5') angleID=5;
    if(key=='6') angleID=6;
    if(key=='7') angleID=7;
    if(key=='8') angleID=8;
    if(key=='9') angleID=9;


}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glRotatef(angleX[0],1,0,0);
        glRotatef(angleY[0],0,1,0);
        drawbody();
        glEnable(GL_TEXTURE_2D);
        glColor3f(1,1,1);

        glPushMatrix();
            glTranslatef(-0.1,0,0);
            glRotatef(angleX[1],1,0,0);
            glRotatef(angleY[1],0,1,0);
            glTranslatef(0,-0.07,0);
            drawupperA();
            glEnable(GL_TEXTURE_2D);
            glPushMatrix(); ///加這行, 讓它轉動
                glTranslatef(-0.02,-0.09,0);
                glRotatef(angleX[2],1,0,0);
                glRotatef(angleY[2],0,1,0);
                glTranslatef(0,-0.21,0);
                drawlowerA();
                glEnable(GL_TEXTURE_2D);
            glPopMatrix(); ///加這行, 讓它轉動
        glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, -5.0f, 0.0f };///加這行, 讓它轉動

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

int main(int argc, char*argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week14- Gundam");
    glutDisplayFunc(display);
    glutIdleFunc(display); ///加這行, 讓它轉動
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    //glutTimerFunc(0,timer,0);

    myTexture("data/Diffuse.jpg");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();
}
