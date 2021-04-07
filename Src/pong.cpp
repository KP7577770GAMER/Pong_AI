#include "Include/head.hpp"

void Pong::pong_dispaly() {
	glBegin(GL_QUADS); {
		glColor3f(1, 1, 1);
		glVertex2f(px - size, py - size);
		glVertex2f(px + size, py - size);
		glVertex2f(px + size, py + size);
		glVertex2f(px - size, py + size);
	}
	glEnd();

	glBegin(GL_QUADS); {
		glColor3f(1, 1, 1);
		glVertex2f(player1.px - player1.width, player1.py - player1.height);
		glVertex2f(player1.px + player1.width, player1.py - player1.height);
		glVertex2f(player1.px + player1.width, player1.py + player1.height);
		glVertex2f(player1.px - player1.width, player1.py + player1.height);
	}
	glEnd();
}

void AI::AI_display()
{
	glBegin(GL_QUADS); {
		glColor3f(1, 1, 1);
		glVertex2f(ai1.px - ai1.width, ai1.py - ai1.height);
		glVertex2f(ai1.px + ai1.width, ai1.py - ai1.height);
		glVertex2f(ai1.px + ai1.width, ai1.py + ai1.height);
		glVertex2f(ai1.px - ai1.width, ai1.py + ai1.height);
	}
	glEnd();
}

void Pong::pong_script(int w, int h)
{
	if(!paused)pong1.px += pong1.sx;
	if(!paused)pong1.py += pong1.sy;

	if (pong1.px > w / 2 - pong1.size) {
		life.p--;
		sx *= -1; sy = rand() % 8 - 4.0f;
		player1.py = 0; ai1.py = 0; ai1.sy = 0;
		px = 0; py = 0; paused = true;
	}
	if (pong1.px < -w / 2 + pong1.size) {
		life.a--;
		sx *= -1; sy = rand() %  6 - 3.0f;
		player1.py = 0; ai1.py = 0; ai1.sy = 0;
		px = 0;py = 0; paused = true;
	}
	if (pong1.py > h / 2 - pong1.size)if (pong1.sy > 0)pong1.sy *= -1;
	if (pong1.py < -h / 2 + pong1.size)if (pong1.sy < 0)pong1.sy *= -1;

	if (keyBuff['w'] && player1.py < window1.height / 2 - 50)player1.py+=4;
	if (keyBuff['s'] && player1.py > -window1.height / 2 + 50)player1.py-=4;

	if (pong1.px - pong1.size < player1.px + player1.width
		&& pong1.py - pong1.size < player1.py + player1.height
		&& pong1.py + pong1.size > player1.py - player1.height) {
		if(pong1.sx < 0)pong1.sx *= -1;
		pong1.sy = (pong1.py - player1.py)*4.0f / (float)player1.height;
	}

	if (pong1.px + pong1.size > ai1.px - ai1.width
		&& pong1.py - pong1.size < ai1.py + ai1.height
		&& pong1.py + pong1.size > ai1.py - ai1.height) {
		if (pong1.sx > 0)pong1.sx *= -1;
		pong1.sy = (pong1.py - ai1.py) * 4.0f / (float)ai1.height;
	}
}

void AI::AI_script(int w, int h)
{
	static float tmp = 0;
	static int dir = 1;
	static float vary = (float)(rand() % 40 + 10);
	sy += (pong1.py - py) / (30.0f - Intelligence*5);/*
	if ((sy - 10) < py) py += (pong1.py - py) / 10.0f;
	if ((sy - 10) > py) py += (pong1.py - py) / 10.0f;*/

	if (dir) {
		if (tmp >= -1)tmp += (51.0f - tmp) / 10.0f;
		else tmp += (51 + tmp) / 10.0f;
	}
	else {
		if (tmp <= 1)tmp += (-51.0f - tmp) / 20.0f;
		else tmp -= (51 - tmp) / 20.0f;
	}
	if (tmp > vary) dir = 0, vary = (float)(rand() % (int)(50.0f - Intelligence * 10) + (Intelligence * 10));
	if (tmp < -vary) dir = 1, vary = (float)(rand() % (int)(50.0f - Intelligence * 10) + (Intelligence * 10));

	py = sy + tmp;
	if (py < -h / 2 + height)py = (-h / 2 + height + 1.0f);
	if (py > h / 2 - height)py = (h / 2 - height - 1.0f);
}

void Pong::pong_scores()
{
	glBegin(GL_QUADS); {
		glColor3f(0.1f, 0.1f, 0.2f);
		glVertex2f(-window1.width / 2 - 2.0f, window1.height / 2 + 5.0f);
		glVertex2f(window1.width / 2 + 2.0f, window1.height / 2 + 5.0f);
		glVertex2f(window1.width / 2 + 2.0f, window1.height / 2 + 31.0f);
		glVertex2f(-window1.width / 2 - 2.0f, window1.height / 2 + 31.0f);
	}
	glEnd();

	glColor3f(1, 0, 0);
	for (int i = 0; i < pong1.life.p; i++) {
		glBegin(GL_POLYGON);
		glVertex2f(window1.width / 2 - ((GLfloat)i * 20.0f + 10.0f), window1.height / 2 + 10.0f);
		glVertex2f(window1.width / 2 - ((GLfloat)i * 20.0f + 20.0f), window1.height / 2 + 10.0f);
		glVertex2f(window1.width / 2 - ((GLfloat)i * 20.0f + 20.0f), window1.height / 2 + 25.0f);
		glVertex2f(window1.width / 2 - ((GLfloat)i * 20.0f + 10.0f), window1.height / 2 + 25.0f);
		glEnd();
	}
	for (int i = 0; i < pong1.life.a; i++) {
		glBegin(GL_POLYGON);
		glVertex2f(-window1.width / 2 + ((GLfloat)i * 20.0f + 10.0f), window1.height / 2 + 10.0f);
		glVertex2f(-window1.width / 2 + ((GLfloat)i * 20.0f + 20.0f), window1.height / 2 + 10.0f);
		glVertex2f(-window1.width / 2 + ((GLfloat)i * 20.0f + 20.0f), window1.height / 2 + 25.0f);
		glVertex2f(-window1.width / 2 + ((GLfloat)i * 20.0f + 10.0f), window1.height / 2 + 25.0f);
		glEnd();
	}
}

void Pong::pong_menu()
{
	switch (pong1.check_win()) {
	case 1:
		std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\bComputer win !";
		break;
	case 2:
		std::cout << "\b\b\b\b\b\b\b\b\bYou win !";
		break;
	default:
		break;
	}
}

int Pong::check_win()
{
	if (pong1.life.a == 0)return 1;
	if (pong1.life.p == 0)return 2;
	return 0;
}
