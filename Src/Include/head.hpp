#include "GL/glut.h"
#include <iostream>
#include <time.h>

extern bool keyBuff[256];

class Window {
public:
	int width, height;
	int winadd = 0;
	Window(int, int);
};

extern Window window1;

class Player {
public:
	int width = 10, height = 50;
	float px = -window1.width / 2.0f + width, py = 0;
};

class AI {
private:
	float Intelligence = 3;
public:
	int width = 10, height = 50;
	float px = window1.width / 2.0f - width, py = 0;
	float sy = 0;
	void AI_script(int, int);
	void AI_display();
};

extern AI ai1;

struct Lifes {
	int p = 5, a = 5;
};

class Pong {
private:
	Player player1;
	float px = 0, py = 0;
	float sx = 7, sy = 0;
	int size = 10;
	Lifes life;
	bool paused = 1;
public:
	void pong_script(int, int);
	void pong_dispaly();
	void pong_scores();
	void pong_menu();
	int check_win();

	friend class AI;
	friend class Input;
	friend class Display;
};

extern Pong pong1;

class Display : public Pong {
protected:
	static void display();
	static void refresh();
};

class Input {
protected:
	static void key_Dn(unsigned char, int, int);
	static void key_Up(unsigned char, int, int);
};

class GLUT : public Display, public Input {
private:
	static void Init();
public:
	GLUT(int*, char**);
};