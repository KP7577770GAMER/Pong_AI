#include "Include/head.hpp"

void Input::key_Dn(unsigned char key, int X, int Y) {
	if (key == 'q')ExitProcess(EXIT_SUCCESS);
	if(pong1.paused)pong1.paused = false;
	if (pong1.check_win())exit(0);
	keyBuff[key] = true;
}

void Input::key_Up(unsigned char key, int X, int Y) {
	keyBuff[key] = false;
}