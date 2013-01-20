#include "utilities.h"


static unsigned int nowTime=0;
static unsigned int gameTime=0;

unsigned int GetGameTime(void){
	return gameTime;
}

unsigned int GetCurrTime (void){
	SYSTEMTIME st;

	GetSystemTime(&st);
	return st.wMilliseconds + st.wSecond*1000 + 
			st.wMinute*60*1000 + st.wHour*3600*1000 + 
			st.wDay*24*3600*1000;
}

void SetGameTime(unsigned int time){
	gameTime=time;
}