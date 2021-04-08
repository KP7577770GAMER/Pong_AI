#include "Include/head.hpp"

void Display::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glBegin(GL_QUADS); {
		glColor3f(0.1f, 0.1f, 0.2f);
		glVertex2f(-window1.width / 2 - 2.0f, -window1.height / 2 - 2.0f);
		glVertex2f(window1.width / 2 + 2.0f, -window1.height / 2 - 2.0f);
		glVertex2f(window1.width / 2 + 2.0f, window1.height / 2 + 2.0f);
		glVertex2f(-window1.width / 2 - 2.0f, window1.height / 2 + 2.0f);
	}
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	for (int i = -window1.height/2; i < window1.height/2; i += window1.height / 21)
		glVertex2f(0.0f, (GLfloat)i);
	glEnd();

	pong1.pong_dispaly();
	pong1.pong_scores();
	ai1.AI_display();
	if (pong1.paused)pong1.pong_menu();

	glutSwapBuffers();
}

void Display::refresh() {
	if (!pong1.paused && !pong1.check_win())pong1.pong_script(window1.width, window1.height);
	if (!pong1.check_win())ai1.AI_script(window1.width, window1.height);
	if (!pong1.paused && !pong1.check_win())Input::key_Ck();
	Sleep(1000 / 60);
	glutPostRedisplay();
}

Window::Window(int w, int h) {
	width = w; height = h;
}

void GLUT::Init()
{
	glViewport(0,0,window1.width + 10,window1.height + 40);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-window1.width / 2 - 5.0, window1.width / 2 + 5.0, -window1.height / 2 - 5.0, window1.height / 2 + 35.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
}

GLUT::GLUT(int* argc, char** argv) {
	glutInit(argc, argv);
	glutInitDisplayMode(GL_RGB | GL_DOUBLE);
	glutInitWindowPosition(GetSystemMetrics(SM_CXSCREEN) / 2 - window1.width / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - window1.height / 2);
	glutInitWindowSize(window1.width, window1.height);
	window1.winadd = glutCreateWindow("");

	glutDisplayFunc(display);
	glutIdleFunc(refresh);
	glutKeyboardFunc(key_Dn);
	glutKeyboardUpFunc(key_Up);

	Init();
}