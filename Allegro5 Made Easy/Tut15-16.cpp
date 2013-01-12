// C++ ALLEGRO 5 MADE EASY TUTORIAL 15~16 - INDIVIDUAL SPRITE ANIMATION
// CODINGMADEEASY

#include<allegro5\allegro5.h> 
#include<allegro5\allegro_native_dialog.h> 
#include<allegro5\allegro_image.h>
#include<sstream>

#define ScreenWidth 800 
#define ScreenHeight 600

int main()
{
	ALLEGRO_DISPLAY *display;

	enum Direction { DOWN = 0, LEFT = 3, RIGHT = 6, UP = 9 };

	const float FPS = 60.0;
	const int interval = 3;

	if(!al_init())
		al_show_native_message_box(NULL, "Error", NULL, "Could not Initialize Allegro", NULL, NULL); 
	
	display = al_create_display(ScreenWidth, ScreenHeight);

	if(!display)
		al_show_native_message_box(NULL, "Error", NULL, "Could not create Allegro Display", NULL, NULL);

	al_set_window_position(display, 200, 200);

	bool done = false, draw = true, active = false;
	float x = 10, y = 10, moveSpeed = 5;
	int dir = DOWN, prevDir, index = 0;

	ALLEGRO_BITMAP *playerWalk[12];

	al_install_keyboard();
	al_init_image_addon();

	for(int i = 0; i < 12; i++)
	{
		std::stringstream str; 
		if(i == 1)
			str << "Sprites/" << i + 1 << ".png";
		else
			str << "Sprites/" << i + 1 << ".jpg";
		playerWalk[i] = al_load_bitmap(str.str().c_str());
	}

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
			prevDir = dir;
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
				index++;
			else 
				index = dir + 1;

			if(index >= dir + 3)
				index = dir;

			if(dir != prevDir)
				index = dir;

			draw = true;
		}

		if(draw)
		{
			al_convert_mask_to_alpha(playerWalk[index], al_map_rgb(255, 255, 255));
			al_draw_bitmap(playerWalk[index], x, y, NULL);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}
	al_destroy_display(display);
	al_destroy_timer(timer);
	for(int i = 0; i < 12; i++)
		al_destroy_bitmap(playerWalk[i]);
	al_destroy_event_queue(event_queue);

	return 0;
}