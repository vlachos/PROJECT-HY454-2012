// C++ ALLEGRO 5 MADE EASY TUTORIAL 20 - CREATING AND SAVING BITMAPS

// CODINGMADEEASY

#include<allegro5\allegro5.h> 
#include<allegro5\allegro_native_dialog.h> 
#include<allegro5\allegro_image.h>

#define ScreenWidth 800 
#define ScreenHeight 600

int main()
{
	ALLEGRO_DISPLAY *display;

	enum Direction { DOWN, LEFT, RIGHT, UP };

	const float FPS = 60.0;

	if(!al_init())
		al_show_native_message_box(NULL, "Error", NULL, "Could not Initialize Allegro", NULL, NULL); 
	
	display = al_create_display(ScreenWidth, ScreenHeight);

	if(!display)
		al_show_native_message_box(NULL, "Error", NULL, "Could not create Allegro Display", NULL, NULL);

	al_set_window_position(display, 200, 200);

	bool done = false, draw = true, active = false;
	float x = 10, y = 10, moveSpeed = 5;
	int dir = DOWN, sourceX = 32, sourceY = 0;

	al_install_keyboard();
	al_init_image_addon();

	ALLEGRO_BITMAP *person = al_load_bitmap("person.png"); 
	ALLEGRO_BITMAP *hair = al_load_bitmap("hair.png");
	ALLEGRO_BITMAP *player = al_create_bitmap(al_get_bitmap_width(person), al_get_bitmap_height(person));

	al_set_target_bitmap(player);

	al_draw_bitmap(person, 0, 0, NULL); 
	al_draw_bitmap(hair, 0, 0, NULL);

	al_save_bitmap("player1.png", player);

	al_set_target_bitmap(al_get_backbuffer(display));

	ALLEGRO_KEYBOARD_STATE keyState;

	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);

	while(!done)
	{
		ALLEGRO_EVENT events; 
		al_wait_for_event(event_queue, &events);
		al_get_keyboard_state(&keyState);

		if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (events.type == ALLEGRO_EVENT_TIMER)
		{
			active = true;
			if(al_key_down(&keyState, ALLEGRO_KEY_DOWN))
			{
				y += moveSpeed; 
				dir = DOWN;
			}
			else if(al_key_down(&keyState, ALLEGRO_KEY_UP))
			{
				y -= moveSpeed; 
				dir = UP;
			}
			else if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
			{
				x += moveSpeed; 
				dir = RIGHT;
			}
			else if(al_key_down(&keyState, ALLEGRO_KEY_LEFT))
			{
				x -= moveSpeed; 
				dir = LEFT;
			}
			else 
				active = false;

			if(active)
				sourceX += al_get_bitmap_width(player) / 4;
			else 
				sourceX = 0; 

			if(sourceX >= al_get_bitmap_width(player))
				sourceX = 0;

			sourceY = dir;

			draw = true;
		}

		if(draw)
		{
			al_draw_bitmap_region(player, sourceX, sourceY * al_get_bitmap_height(player) / 4, 32, 32, 
				x, y, NULL);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_bitmap(player);
	al_destroy_event_queue(event_queue);

	return 0;
}