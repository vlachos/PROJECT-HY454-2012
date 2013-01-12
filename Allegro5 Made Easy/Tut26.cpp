// C++ ALLEGRO 5 MADE EASY TUTORIAL 26 - PIXEL PERFECT COLLISION
// CODINGMADEEASY

#include<allegro5\allegro5.h> 
#include<allegro5\allegro_native_dialog.h> 
#include<allegro5\allegro_image.h>
#include<cmath>

#define ScreenWidth 800 
#define ScreenHeight 600

int top, bottom, left, right;

bool Collision(ALLEGRO_BITMAP *player, ALLEGRO_BITMAP *enemy,
	float x, float y, float ex, float ey, int width, int height, float &moveSpeed, int dir)
{
	if(x + width < ex || x > ex + width || y + height < ey || y > ey + height)
	{
		return false;
	}
	else 
	{
		top = max(y, ey); 
		bottom = min(y + height, ey + height);
		left = max(x, ex); 
		right = min(x + width, ex + width); 

		for(int i = top; i < bottom; i++)
		{
			for(int j = left; j < right; j++)
			{
				al_lock_bitmap(player, al_get_bitmap_format(player), ALLEGRO_LOCK_READONLY);
				al_lock_bitmap(enemy, al_get_bitmap_format(enemy), ALLEGRO_LOCK_READONLY);
				ALLEGRO_COLOR color = al_get_pixel(player, j - x, i - y);
				ALLEGRO_COLOR color2 = al_get_pixel(enemy, j - ex, i - ey);
				
				if(color.a != 0 && color2.a != 0)
				{
					if(dir == 0 || dir == 3)
						moveSpeed = (i - y);
					else 
						moveSpeed = (j - x);
					return true;
				}
			}
		}

	}
	return false;
}

int main()
{
	ALLEGRO_DISPLAY *display;

	enum Direction { DOWN, LEFT, RIGHT, UP };

	const float FPS = 60.0;
	const float frameFPS = 15.0;

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

	ALLEGRO_BITMAP *player = al_load_bitmap("image.png");
	ALLEGRO_BITMAP *player2 = al_load_bitmap("image2.png");

	ALLEGRO_KEYBOARD_STATE keyState;

	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_TIMER *frameTimer = al_create_timer(1.0 / frameFPS);

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(frameTimer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	al_start_timer(frameTimer);

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
			if(events.timer.source == timer)
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

			}

			else if (events.timer.source == frameTimer)
			{
				if(active)
					sourceX += al_get_bitmap_width(player) / 3;
				else 
					sourceX = 32; 

				if(sourceX >= al_get_bitmap_width(player))
					sourceX = 0;

				sourceY = dir;
			}

							
			if(Collision(player, player2, x, y, 200, 200, 32, 32, moveSpeed, dir))
			{
				if(dir == 0)
					y -= moveSpeed;
				else if(dir == 1)
					x += moveSpeed; 
				else if(dir == 2)
					x -= moveSpeed; 
				else if(dir == 3)
					y += moveSpeed;

				moveSpeed = 5;
			}
			else 
				draw = true;

		}

		if(draw)
		{
			al_draw_bitmap(player, x, y, NULL);
			al_draw_bitmap(player2, 200, 200, NULL);
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