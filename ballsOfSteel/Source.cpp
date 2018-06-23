#include <GL/glut.h>

int rot = 0;
float xt = 0.0, yt = 0.0, zt = 0.0;
//void kob() {
//	glBegin(GL_QUADS);
//	// Front	  		
//	glNormal3f(0, 0, 1);
//	glVertex3f(-1, 0, 1);
//	glVertex3f(-1, 2, 1);
//	glVertex3f(1, 2, 1);
//	glVertex3f(1, 0, 1);
//
//	// Back
//	glNormal3f(0, 0, -1);
//	glVertex3f(-1, 0, -1);
//	glVertex3f(1, 0, -1);
//	glVertex3f(1, 2, -1);
//	glVertex3f(-1, 2, -1);
//
//	// Left side
//	glNormal3f(-1, 0, 0);
//	glVertex3f(-1, 0, 1);
//	glVertex3f(-1, 2, 1);
//	glVertex3f(-1, 2, -1);
//	glVertex3f(-1, 0, -1);
//
//	// Right side
//	glNormal3f(1, 0, 0);
//	glVertex3f(1, 0, 1);
//	glVertex3f(1, 0, -1);
//	glVertex3f(1, 2, -1);
//	glVertex3f(1, 2, 1);
//	glEnd();
//}

void leg() {
	glBegin(GL_QUADS);
	// Front	  		
	glNormal3f(0, 0, 0.5);
	glVertex3f(-0.5, 0, 0.5);
	glVertex3f(-0.5, -5, 0.5);
	glVertex3f(0.5, -5, 0.5);
	glVertex3f(0.5, 0, 0.5);

	// Back
	glNormal3f(0, 0, -0.5);
	glVertex3f(-0.5, 0, -0.5);
	glVertex3f(-0.5, -5, -0.5);
	glVertex3f(0.5, -5, -0.5);
	glVertex3f(0.5, 0, -0.5);

	// Left side
	glNormal3f(-0.5, 0, 0);
	glVertex3f(-0.5, 0, 0.5);
	glVertex3f(-0.5, -5, 0.5);
	glVertex3f(-0.5, -5, -0.5);
	glVertex3f(-0.5, 0, -0.5);

	// Right side
	glNormal3f(0.5, 0, 0);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, -5, 0.5);
	glVertex3f(0.5, -5, -0.5);
	glVertex3f(0.5, 0, -0.5);
	glEnd();
}
void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) exit(1);
	if (key == 'r') {
		rot += 5;
		rot %= 360;
	}
	if (key == '6') xt += 0.5;
	if (key == '4') xt -= 0.5;
	if (key == '8') zt -= 0.5;
	if (key == '2') zt += 0.5;
	glutPostRedisplay();
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0, -3, -15);
	glRotatef(rot, 1, 0, 0);
	/************************************************************/

	// Floor
	glBegin(GL_QUADS);
	glColor3f(0.2, 0.7, 0.3);
	glNormal3f(0, 1, 0);	// normal straight up
	glVertex3f(-5, 0, -5);
	glVertex3f(5, 0, -5);
	glVertex3f(5, 0, 5);
	glVertex3f(-5, 0, 5);
	glEnd();
	glTranslatef(-4.5, 0, -4.5);
	leg();
	glTranslatef(9, 0, 0);
	leg();
	glTranslatef(0, 0, 9);
	leg();
	glTranslatef(-9, 0, 0);
	leg();
	glTranslatef(4.5, 0, -4.5);
	glTranslatef(xt, yt, zt);
	glColor3f(0.3, 0.5, 0.4);
	kob();

	//kob();
	//glTranslatef(xt,yt,zt);
	//kob();

	glutSwapBuffers();			// display the output
}

// Set OpenGL parameters
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);

	// Lighting parameters

	GLfloat mat_ambdif[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular[] = { 0.0, 1.0, 0.0, 0.0 };
	GLfloat mat_shininess[] = { 80.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambdif);	// set both amb and diff components
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);		// set specular
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		// set shininess
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);		// set light "position", in this case direction
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);		// active material changes by glColor3f(..)
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char *argv[])

{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);	// RGB display, double-buffered, with Z-Buffer
	glutInitWindowSize(500, 500);					// 500 x 500 pixels
	glutCreateWindow("3D");
	glutDisplayFunc(draw);						// Set the display function
	glutKeyboardFunc(keyboard);					// Set the keyboard function

	init();
	glutMainLoop();							// Start the main event loop
}