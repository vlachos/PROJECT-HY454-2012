#include <stdio.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <windows.h>
#include <PathNames.h>
#include <allegro5\allegro5.h> 
#include <allegro5\allegro_native_dialog.h> 
#include <allegro5\allegro_image.h>
#include "FrameRangeAnimation.h"
#include "AnimationFilmHolder.h"
#include "AnimationFilm.h"
#include "FrameRangeAnimator.h"
#include "AnimatorHolder.h"
#include "EventCallbacks.h"
#include "TileBitmap.h"
#include "TileLayer.h"
#include "Main.h"


const float FPS = 60;
unsigned int gameTime=0;

unsigned int CurrTime (void){
    SYSTEMTIME st;

    GetSystemTime(&st);
	return st.wMilliseconds + st.wSecond*1000 + 
			st.wMinute*60*1000 + st.wHour*3600*1000 + 
			st.wDay*24*3600*1000;
}

unsigned int GetGameTime (void){
	return gameTime;
}


TileLayer* init_terrain(){
	DNEWPTR(TileLayer, actionLayer);
	DNEWPTR(TileBitmap, tilesBitmap);
	tilesBitmap = DNEW(TileBitmap);
	actionLayer = DNEWCLASS(TileLayer, (tilesBitmap) );
	
	actionLayer->ReadStage(BubblePathnames::GetStageInfo(1));
	actionLayer->WriteMap(BubblePathnames::GetTestActionLayerInfo() );

	return actionLayer;
}


int Draw_Terrain(){
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_BITMAP *palette = NULL;
     
 
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
 
   display = al_create_display(VIEW_WINDOW_WIDTH, VIEW_WINDOW_HEIGHT);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }

   palette = al_create_bitmap(VIEW_WINDOW_WIDTH, VIEW_WINDOW_HEIGHT);
   if(!palette) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
	al_set_window_position(display, 0, 0);
	al_install_keyboard();
	al_init_image_addon();

   al_set_target_bitmap(palette);
 
   al_clear_to_color(BB_BLACK);
 
   al_set_target_bitmap(al_get_backbuffer(display));
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(palette);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_clear_to_color(BB_BLACK);
 
   al_flip_display();

	TileLayer* terrain = init_terrain();
	AnimationFilmHolder afh("..\\data\\bitmaps\\sprites\\data.xml");
	FrameRangeAnimation *fra=new FrameRangeAnimation(0,7,-2,0,100,false,1);
	Sprite *sprite=new Sprite(400,50,false,afh.GetFilm("Bubopenmouth"), terrain);
	FrameRangeAnimator *frtor=new FrameRangeAnimator(); 

	frtor->SetOnFinish( EventCallbacks::BubbleWalkStop, 0 );
   al_start_timer(timer);

    gameTime = CurrTime();

	frtor->Start(sprite,fra,gameTime);
	AnimatorHolder::Register(frtor);
	AnimatorHolder::MarkAsRunning(frtor);

	bool redraw = true;
   while(1)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);

      if(ev.type == ALLEGRO_EVENT_TIMER) {

		 unsigned int   nowTime = CurrTime();
		 AnimatorHolder::Progress(nowTime);

		 al_set_target_bitmap(palette);
		 al_clear_to_color(BB_BLACK);

		 terrain->Display(palette);
		 AnimatorHolder::Display(palette);
 
         redraw = true;

		 gameTime = gameTime + ( nowTime - gameTime);
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;

 al_set_target_bitmap(al_get_backbuffer(display));
         
         al_draw_bitmap(palette, 0, 0, 0);
         al_flip_display();
      }
   }
 
   al_destroy_bitmap(palette);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   std::cout << terrain->isSolid(0, 0, BBUp);
   std::cout << terrain->isSolid(50, 0, BBUp);
   std::cout << terrain->isSolid(50, 0, BBLeft);
   std::cout << terrain->isSolid(50, 0, BBDown);
   std::cout << terrain->isSolid(50, 0, BBRight);

   return 0;
}

int main(int argc, char **argv){
	Draw_Terrain();
	system( "pause" );
}