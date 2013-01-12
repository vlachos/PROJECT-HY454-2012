// C++ ALLEGRO 5 MADE EASY TUTORIAL 33 - LOADING TILE MAPS [EASY]
// CODINGMADEEASY

#include<allegro5\allegro5.h> 
#include<allegro5\allegro_native_dialog.h> 
#include<allegro5\allegro_primitives.h>
#include<fstream>

#define ScreenWidth 800 
#define ScreenHeight 600

int loadCounterX = 0, loadCounterY = 0, mapSizeX, mapSizeY; 
int map[100][100];

void LoadMap(const char*filename)
{
	std::ifstream openfile(filename);
	if(openfile.is_open())
	{
		openfile >> mapSizeX >> mapSizeY; 
		while(!openfile.eof())
		{
			openfile >> map[loadCounterX][loadCounterY]; 
			loadCounterX++; 
			if(loadCounterX >= mapSizeX)
			{
				loadCounterX = 0; 
				loadCounterY++;
			}
		}
	}
	else 
	{
	}
}

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
	
	LoadMap("Map1.txt");

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

		for(int i = 0; i < mapSizeX; i++)
		{
			for(int j = 0; j < mapSizeY; j++)
			{
				if(map[i][j] == 0)
					al_draw_filled_rectangle(i * 40, j * 40, i * 40 + 40, j * 40 + 40, al_map_rgb(0, 0, 255));
				else if(map[i][j] == 1)
					al_draw_filled_rectangle(i * 40, j * 40, i * 40 + 40, j * 40 + 40, al_map_rgb(0, 255, ));
			}
		}

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	return 0;
}