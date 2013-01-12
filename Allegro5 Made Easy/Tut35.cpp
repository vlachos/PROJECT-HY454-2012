// C++ ALLEGRO 5 MADE EASY TUTORIAL 35 - LOADING TILE MAPS [HARD]
// CODINGMADEEASY

#include<allegro5\allegro5.h> 
#include<allegro5\allegro_native_dialog.h> 
#include<allegro5\allegro_primitives.h>
#include<fstream>
#include<string> 
#include<vector>
#include<sstream>

#define ScreenWidth 800 
#define ScreenHeight 600
#define BlockSize 40

int loadCounterX = 0, loadCounterY = 0, mapSizeX, mapSizeY; 

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

			std::stringstream str(line);
			std::vector<int> tempVector;

			while(!str.eof())
			{
				std::getline(str, value, ' ');
				if(value.length() > 0)
					tempVector.push_back(atoi(value.c_str()));
			}
			map.push_back(tempVector);
		}
	}
	else
	{
	}
}

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

	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);	

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	
	std::vector< std::vector <int> > map;
	
	LoadMap("Map1.txt", map);

	al_start_timer(timer);

	while(!done)
	{
		ALLEGRO_EVENT events; 
		al_wait_for_event(event_queue, &events);

		if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (events.type == ALLEGRO_EVENT_TIMER)
		{
			
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

void DrawMap(std::vector <std::vector <int> > map)
{
	for(int i = 0; i < map.size(); i++)
	{
		for(int j = 0; j < map[i].size(); j++)
		{
			if(map[i][j] == 0)
				al_draw_filled_rectangle(j * BlockSize, i * BlockSize, 
					j * BlockSize + BlockSize, i * BlockSize + BlockSize, al_map_rgb(0, 0, 255));
			else 
				al_draw_filled_rectangle(j * BlockSize, i * BlockSize, 
					j * BlockSize + BlockSize, i * BlockSize + BlockSize, al_map_rgb(0, 255, 0));
		}
	}
}