// C++ ALLEGRO 5 MADE EASY TUTORIAL 31 - SPLIT SCREEN [CAMERA EFFECTS]
// CODINGMADEEASY

#include<allegro5\allegro5.h> 
#include<allegro5\allegro_native_dialog.h> 
#include<allegro5\allegro_image.h>

#define ScreenWidth 800 
#define ScreenHeight 600

struct Player
{
	float x, y;
	int dir, sourceX, sourceY;
	bool active;
};

struct Camera
{
	float x, y, scale, degrees;
	ALLEGRO_TRANSFORM transform;
};

void CameraUpdate(float *cameraPosition, float x, float y, int width, int height)
{
	cameraPosition[0] = -(ScreenWidth / 2 / 2) + (x + width / 2); 
	cameraPosition[1] = -(ScreenHeight / 2) + (y + height / 2);

	if(cameraPosition[0] < 0)
		cameraPosition[0] = 0; 
	if(cameraPosition[1] < 0)
		cameraPosition[1] = 0;
}

int main()
{
	ALLEGRO_DISPLAY *display;

	enum Direction { DOWN, LEFT, RIGHT, UP };

	const float FPS = 60.0;
	const float frameFPS = 15.0;

	float degrees = 0.0f;
	float scale = 1.0f;

	if(!al_init())
		al_show_native_message_box(NULL, "Error", NULL, "Could not Initialize Allegro", NULL, NULL); 
	
	display = al_create_display(ScreenWidth, ScreenHeight);

	if(!display)
		al_show_native_message_box(NULL, "Error", NULL, "Could not create Allegro Display", NULL, NULL);

	al_set_window_position(display, 200, 200);

	bool toggle = false, done = false, draw = true;

	al_install_keyboard();
	al_init_image_addon();

	ALLEGRO_BITMAP *player = al_load_bitmap("PlayerImage1.png");
	ALLEGRO_BITMAP *background = al_load_bitmap("background.png");
	ALLEGRO_BITMAP *divider = al_load_bitmap("divider.png");

	ALLEGRO_BITMAP *screens[2]; 

	ALLEGRO_KEYBOARD_STATE keyState;

	Player _player[2];
	Camera _camera[2];

	float x = 10, y = 10, moveSpeed = 5, cameraPosition[2];
	int dir = DOWN;
	bool active;
	int playerNumber = 0;

	for(int i = 0; i < 2; i++)
	{
		screens[i] = al_create_bitmap(ScreenWidth / 2, ScreenHeight);
		
		_player[i].x = _player[i].y = 10; 
		_player[i].dir = DOWN;
		_camera[i].x = _camera[i].y = _player[i].sourceY = 0;
		_player[i].sourceX = 32;
		_camera[i].degrees = 0.0f; 
		_camera[i].scale = 1.0f;
	}

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
		else if(events.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if(events.keyboard.keycode == ALLEGRO_KEY_T)
				toggle = true;
		}
		else if (events.type == ALLEGRO_EVENT_TIMER)
		{
			if(events.timer.source == timer)
			{
				x = _player[playerNumber].x; 
				y = _player[playerNumber].y;
				dir = _player[playerNumber].dir;

				degrees = _camera[playerNumber].degrees; 
				scale = _camera[playerNumber].scale;

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

				_player[playerNumber].x = x; 
				_player[playerNumber].y = y;
				_player[playerNumber].dir = dir;
				_player[playerNumber].active = active;
				

				if(al_key_down(&keyState, ALLEGRO_KEY_W))
					degrees++; 
				else if(al_key_down(&keyState, ALLEGRO_KEY_S))
					degrees--;
				if(al_key_down(&keyState, ALLEGRO_KEY_D))
					scale += 0.1f; 
				else if(al_key_down(&keyState, ALLEGRO_KEY_A))
					scale -= 0.1f;
					
				if(degrees <= -360 || degrees >= 360)
					degrees = 0;

				_camera[playerNumber].degrees = degrees;
				_camera[playerNumber].scale = scale;

				if(toggle)
				{
					playerNumber = (playerNumber == 0) ? 1 : 0;
					toggle = false;
				}

				for(int i = 0; i < 2; i++)
				{
					cameraPosition[0] = _camera[i].x;
					cameraPosition[1] = _camera[i].y;

					CameraUpdate(cameraPosition, _player[i].x, _player[i].y, 32, 32);

					_camera[i].x = cameraPosition[0]; 
					_camera[i].y = cameraPosition[1];

					al_identity_transform(&_camera[i].transform);
					al_translate_transform(&_camera[i].transform, -(_player[i].x + 16) , -(_player[i].y + 16));
					al_scale_transform(&_camera[i].transform, _camera[i].scale, _camera[i].scale);
					al_rotate_transform(&_camera[i].transform, _camera[i].degrees * 3.1415 / 180);
					al_translate_transform(&_camera[i].transform, -_camera[i].x + (_player[i].x + 16), 
						-_camera[i].y + (_player[i].y + 16));
				}
			}

			else if (events.timer.source == frameTimer)
			{
				if(active)
					_player[playerNumber].sourceX += al_get_bitmap_width(player) / 3;
				else 
					_player[playerNumber].sourceX = 32; 

				if(_player[playerNumber].sourceX >= al_get_bitmap_width(player))
					_player[playerNumber].sourceX = 0;

				_player[playerNumber].sourceY = _player[playerNumber].dir;
			}

			draw = true;

		}

		if(draw)
		{
			ALLEGRO_BITMAP *subBitmap;

			for(int i = 0; i < 2; i++)
			{
				al_set_target_bitmap(screens[i]);
				subBitmap = al_create_sub_bitmap(player, _player[i].sourceX, _player[i].sourceY * 32, 32, 32);
				al_use_transform(&_camera[i].transform);
			    al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_bitmap(background, 0, 0, NULL);
				al_draw_bitmap(subBitmap, _player[i].x, _player[i].y, NULL);

				if(i == 0)
				{
					subBitmap = al_create_sub_bitmap(player, _player[1].sourceX, _player[1].sourceY * 32, 32, 32);
					al_draw_bitmap(subBitmap, _player[1].x, _player[1].y, NULL);
				}
				else
				{
					subBitmap = al_create_sub_bitmap(player, _player[0].sourceX, _player[0].sourceY * 32, 32, 32);
					al_draw_bitmap(subBitmap, _player[0].x, _player[0].y, NULL);
				}
			}

			al_set_target_bitmap(al_get_backbuffer(display));
			al_draw_bitmap(screens[0], 0, 0, NULL);
			al_draw_bitmap(screens[1], ScreenWidth / 2, 0, NULL);
			al_draw_bitmap(divider, ScreenWidth / 2 - 1, 0, NULL);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_destroy_bitmap(subBitmap);
		}
	}
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_timer(frameTimer);
	al_destroy_bitmap(player);
	al_destroy_bitmap(background);
	al_destroy_event_queue(event_queue);

	return 0;
}