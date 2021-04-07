#include "Include/head.hpp"

Window window1(600,400);
Pong pong1;
AI ai1;
bool keyBuff[256];

int main(int argc, char* argv[]) {
	srand((unsigned int)time(0));
	GLUT main(&argc,argv);

	glutMainLoop();
}