// C++ ALLEGRO 5 MADE EASY TUTORIAL 12 - LOADING IMAGES
// CODINGMADEEASY

#include<allegro5\allegro5.h> 
#include<allegro5\allegro_native_dialog.h> 
#include<allegro5\allegro_image.h>

#define ScreenWidth 800 
#define ScreenHeight 600

int main()
{
	ALLEGRO_DISPLAY *display;

	const float FPS = 60.0;

	if(!al_init())
		al_show_native_message_box(NULL, "Error", NULL, "Could not Initialize Allegro", NULL, NULL); 
	
	display = al_create_display(ScreenWidth, ScreenHeight);

	if(!display)
		al_show_native_message_box(NULL, "Error", NULL, "Could not create Allegro Display", NULL, NULL);

	al_set_window_position(display, 200, 200);

	ALLEGRO_COLOR electricBlue = al_map_rgb(44, 117, 255);
	ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
	ALLEGRO_COLOR playerColor = electricBlue;

	bool done = false;
	int x = 10, y = 10, moveSpeed = 5;

	al_install_mouse();
	al_init_image_addon();

	ALLEGRO_BITMAP *player = al_load_bitmap("PlayerImage1.png");

	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_hide_mouse_cursor(display);

	al_start_timer(timer);

	while(!done)
	{
		ALLEGRO_EVENT events; 
		al_wait_for_event(event_queue, &events);

		if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			x = events.mouse.x;
			y = events.mouse.y;
		}
		else if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if(events.mouse.button & 1)
				playerColor = electricBlue; 
			else if (events.mouse.button & 2)
				playerColor = yellow;
		}

		al_draw_bitmap(player, x, y, NULL);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_bitmap(player);
	al_destroy_event_queue(event_queue);

	return 0;
}
