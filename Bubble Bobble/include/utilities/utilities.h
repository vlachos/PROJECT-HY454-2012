#ifndef UTILITIES_H
#define UTILITIES_H

#include <allegro5\allegro5.h>

#define BB_ELECTRIC_BLUE al_map_rgb(15,79,174)
#define BB_BLACK al_map_rgb(0, 0 ,0)

typedef ALLEGRO_BITMAP* Bitmap;
typedef ALLEGRO_DISPLAY* Display;
typedef ALLEGRO_TIMER* Timer;
typedef ALLEGRO_EVENT_QUEUE* EventQueue;
typedef ALLEGRO_KEYBOARD_STATE KeyBoardState;

extern unsigned int GetGameTime(void);
extern unsigned int GetCurrTime (void);
extern void SetGameTime(unsigned int time);




#endif