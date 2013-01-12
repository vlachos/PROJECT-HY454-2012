// C++ ALLEGRO 5 MADE EASY TUTORIAL 38 - JOYSTICKS & CONTROLLERS
// CODINGMADEEASY

#include<allegro5\allegro5.h> 
#include<allegro5\allegro_native_dialog.h> 
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_image.h>
#include<fstream>
#include<string> 
#include<vector>
#include<sstream>
#include<iostream>

#define ScreenWidth 800 
#define ScreenHeight 600
#define BlockSize 40

enum LoadState { TileSet, Map }; 

int state = NULL;

ALLEGRO_BITMAP *tileSet;

void LoadMap(const char *filename, std::vector< std::vector <int> > &map);
void DrawMap(std::vector <std::vector <int> > map);

int main()
{
	ALLEGRO_DISPLAY *display;

	const float FPS = 60.0;
	bool done = false;

	if(!al_init())
		al_show_native_message_box(NULL, "Error", NULL, "Could not Initialize Allegro", NULL, NULL); 
	
	display = al_create_display(ScreenWidth, ScreenHeight);

	if(!display)
		al_show_native_message_box(NULL, "Error", NULL, "Could not create Allegro Display", NULL, NULL);

	al_set_window_position(display, 200, 200);

	al_init_primitives_addon();
	al_init_image_addon();
	al_install_keyboard();
	al_install_joystick();

	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);	

	ALLEGRO_JOYSTICK *joy = al_get_joystick(0);

	ALLEGRO_JOYSTICK_STATE joyState;

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_joystick_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	
	std::vector< std::vector <int> > map;
	
	LoadMap("Map1.txt", map);

	std::cout << al_get_joystick_num_buttons(joy) << std::endl;
	std::cout << al_get_num_joysticks() << std::endl;

	al_start_timer(timer);

	while(!done)
	{
		ALLEGRO_EVENT events; 
		al_wait_for_event(event_queue, &events);
		al_get_joystick_state(joy, &joyState);

		if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (events.type == ALLEGRO_EVENT_TIMER)
		{
			if(joyState.stick[0].axis[0])
			{
				std::cout << joyState.stick[0].axis[0] << std::endl;
			}
		}
		else if (events.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if(events.keyboard.keycode == ALLEGRO_KEY_L)
			{
				//map.clear();
				//LoadMap("Map1.txt", map);
			}
		}
		else if (events.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN)
		{
			//std::cout << events.joystick.button << std::endl;
		}
		else if (events.type == ALLEGRO_EVENT_JOYSTICK_AXIS)
		{
			//std::cout << events.joystick.axis << std::endl;
		}

		DrawMap(map);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	return 0;
}

void LoadMap(const char *filename, std::vector< std::vector <int> > &map)
{
	std::ifstream openfile(filename); 
	if(openfile.is_open())
	{
		std::string line, value;
		int space;

		while(!openfile.eof())
		{
			std::getline(openfile, line);

			if(line.find("[TileSet]") != std::string::npos)
			{
				state = TileSet;
				continue;
			}
			else if (line.find("[Map]") != std::string::npos)
			{
				state = Map;
				continue;
			}

			switch(state)
			{
			case TileSet:
				if(line.length() > 0)
					tileSet = al_load_bitmap(line.c_str());
				break;
			case Map: 
				std::stringstream str(line);
				std::vector<int> tempVector;

				while(!str.eof())
				{
					std::getline(str, value, ' ');
					if(value.length() > 0)
						tempVector.push_back(atoi(value.c_str()));
				}
				map.push_back(tempVector);
				break;
			}
		}
	}
	else
	{
	}
}


void DrawMap(std::vector <std::vector <int> > map)
{
	for(int i = 0; i < map.size(); i++)
	{
		for(int j = 0; j < map[i].size(); j++)
		{
			al_draw_bitmap_region(tileSet, map[i][j] * BlockSize, 0, BlockSize, 32, j * BlockSize,
				i * BlockSize, NULL);
		}
	}
}