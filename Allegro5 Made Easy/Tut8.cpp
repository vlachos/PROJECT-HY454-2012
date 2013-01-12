// C++ ALLEGRO 5 MADE EASY TUTORIAL 8 - TIMERS
// CODINGMADEEASY

#include<allegro5\allegro5.h> 
#include<allegro5\allegro_native_dialog.h> 
#include<allegro5\allegro_primitives.h>

#define ScreenWidth 800 
#define ScreenHeight 600

int main()
{
	ALLEGRO_DISPLAY *display; 

	const float FPS = 60.0;

	enum Direction { UP, DOWN, LEFT, RIGHT };

	if(!al_init())
		al_show_native_message_box(NULL, "Error", NULL, "Could not Initialize Allegro", NULL, NULL); 
	
	display = al_create_display(ScreenWidth, ScreenHeight);

	if(!display)
		al_show_native_message_box(NULL, "Error", NULL, "Could not create Allegro Display", NULL, NULL);

	al_set_window_position(display, 200, 200);

	bool done = false, draw = true;
	int x = 10, y = 10, moveSpeed = 5;
	int dir = DOWN;

	al_init_primitives_addon(); 
	al_install_keyboard();

	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	while(!done)
	{
		ALLEGRO_EVENT events; 
		al_wait_for_event(event_queue, &events);

		if(events.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(events.keyboard.keycode)
			{
			case ALLEGRO_KEY_DOWN: 
				dir = DOWN;
				break;
			case ALLEGRO_KEY_UP: 
				dir = UP;
				break;
			case ALLEGRO_KEY_RIGHT: 
				dir = RIGHT;
				break;
			case ALLEGRO_KEY_LEFT: 
				dir = LEFT;
				break;
			case ALLEGRO_KEY_ESCAPE: 
				done = true;
				break;
			}
		}

		if(events.type == ALLEGRO_EVENT_TIMER)
		{
			switch(dir)
			{
			case DOWN: 
				y += moveSpeed;
				break;
			case UP: 
				y -= moveSpeed;
				break;
			case RIGHT: 
				x += moveSpeed;
				break;
			case LEFT: 
				x -= moveSpeed;
				break;
			}

			draw = true;
		}

		if(draw)
		{
			draw = false;
			al_draw_rectangle(x, y, x + 10, y + 10, al_map_rgb(44, 117, 255), 1);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	
	return 0;
}