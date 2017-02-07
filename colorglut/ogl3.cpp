/*


  Simple Demo for GLSL

  www.lighthouse3d.com

*/

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GL/glut.h>
#include "textfile.h"


GLint loc;
GLhandleARB v,f,f2,p;



void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,100);
	glMatrixMode(GL_MODELVIEW);


}


void drawCube() {

	float hd = 1.0;

	glColor3f(1,0,0);
	glBegin(GL_QUADS);
		glVertex3f(-hd,-hd,-hd);
		glVertex3f(-hd,hd,-hd);
		glVertex3f(hd,hd,-hd);
		glVertex3f(hd,-hd,-hd);
	glEnd();

	glColor3f(1,1,0);
	glBegin(GL_QUADS);
		glVertex3f(-hd,-hd,-hd);
		glVertex3f(hd,-hd,-hd);
		glVertex3f(hd,-hd,hd);
		glVertex3f(-hd,-hd,hd);
	glEnd();

	glColor3f(1,0,1);
	glBegin(GL_QUADS);
		glVertex3f(-hd,-hd,-hd);
		glVertex3f(-hd,-hd,hd);
		glVertex3f(-hd,hd,hd);
		glVertex3f(-hd,hd,-hd);
	glEnd();

	glColor3f(0,1,0);
	glBegin(GL_QUADS);
		glVertex3f(-hd,-hd,hd);
		glVertex3f(hd,-hd,hd);
		glVertex3f(hd,hd,hd);
		glVertex3f(-hd,hd,hd);
	glEnd();

	glColor3f(0,0,1);
	glBegin(GL_QUADS);
		glVertex3f(-hd,hd,-hd);
		glVertex3f(-hd,hd,hd);
		glVertex3f(hd,hd,hd);
		glVertex3f(hd,hd,-hd);
	glEnd();

	glColor3f(0,1,1);
	glBegin(GL_QUADS);
		glVertex3f(hd,-hd,-hd);
		glVertex3f(hd,hd,-hd);
		glVertex3f(hd,hd,hd);
		glVertex3f(hd,-hd,hd);
	glEnd();


}

float a = 0;

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	glRotatef(a,0,1,0);

	drawCube();;
	a+=0.01;

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27) 
		exit(0);
}

#define printOpenGLError() printOglError(__FILE__, __LINE__)

int printOglError(char *file, int line)
{
    //
    // Returns 1 if an OpenGL error occurred, 0 otherwise.
    //
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}


void printInfoLog(GLhandleARB obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB,
                                         &infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetInfoLogARB(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}



void setShaders() {

	char *vs = NULL,*fs = NULL;

	v = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	f = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	f2 = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);


	vs = textFileRead("color.vert");
	fs = textFileRead("color.frag");

	const char * vv = vs;
	const char * ff = fs;

	glShaderSourceARB(v, 1, &vv,NULL);
	glShaderSourceARB(f, 1, &ff,NULL);

	free(vs);free(fs);

	glCompileShaderARB(v);
	glCompileShaderARB(f);

	printInfoLog(v);
	printInfoLog(f);
	printInfoLog(f2);

	p = glCreateProgramObjectARB();
	glAttachObjectARB(p,v);
	glAttachObjectARB(p,f);

	glLinkProgramARB(p);
	printInfoLog(p);

	glUseProgramObjectARB(p);

	loc = glGetUniformLocationARB(p,"time");


}




int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Lighthouse 3D");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0,1.0,1.0,1.0);
	glEnable(GL_CULL_FACE);

	glewInit();
	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		printf("Ready for GLSL\n");
	else {
		printf("No GLSL support\n");
		exit(1);
	}

	setShaders();

	glutMainLoop();

	return 0;
}

