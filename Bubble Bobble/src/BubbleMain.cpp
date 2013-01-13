#include <stdio.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <allegro5\allegro5.h> 
#include <allegro5\allegro_native_dialog.h> 
#include <allegro5\allegro_image.h>

const int TILE_SIZE = /*2**/16;

const char* TERRAIN_DATA_PATH = "..\\data\\bitmaps\\terrain";
const char*	STAGE1_PATH = "..\\data\\bitmaps\\terrain\\stage1.txt";
const char* TILE_BITMAP_PATH = "..\\data\\bitmaps\\terrain\\tile_bitmap_16x16.png";// <-----  32x32

#define SCREEN_W /*2**/512
#define SCREEN_H /*2**/416
unsigned char **terrain;
unsigned int terrain_x, terrain_y;


unsigned char get_terrain_tile(int row, int col){
	return terrain[row][col];
}

void Load_Terrain_Text(const char* filename){
	unsigned int load_counter_x = 0, load_counter_y = 0;

	std::ifstream openfile(STAGE1_PATH);
	if (openfile.is_open()){
		openfile >> terrain_x >> terrain_y;

		terrain = new unsigned char *[terrain_y];
		for (int i=0; i<terrain_y; ++i){
			terrain[i] = new unsigned char [terrain_x];
			for (int j=0; j<terrain_x; ++j){
				openfile >> terrain[i][j];
				assert( terrain[i][j] >= 'a' && terrain[i][j] <='l'  );
			}
		}
		openfile.close();
	}
}

void Draw_Terrain(const char* bitmap_path){

	ALLEGRO_DISPLAY *display = 0;
	ALLEGRO_BITMAP *tile_bitmap = 0;
	ALLEGRO_BITMAP *a_stage = 0;
	ALLEGRO_EVENT_QUEUE *event_queue = 0;
	unsigned int source_x = 0, source_y = 0;
	boolean tile_is_empty = true;

	/*init*/
	if(!al_init())
		al_show_native_message_box(NULL, "Error", NULL, "Could not Initialize Allegro", NULL, NULL); 

	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display)
		al_show_native_message_box(NULL, "Error", NULL, "Could not create Allegro Display", NULL, NULL);

	al_set_window_position(display, 0, 0);
	al_install_keyboard();
	al_init_image_addon();

	a_stage = al_create_bitmap(SCREEN_W,SCREEN_H);
	al_set_target_bitmap(a_stage);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	tile_bitmap = al_load_bitmap(bitmap_path);
	/*display each tile based on the already readen stage1.txt*/
	for (int i=0; i<terrain_x; ++i){
		for (int j=0; j<terrain_y; ++j){
			switch ( get_terrain_tile(j,i)){
				case 'a':
					tile_is_empty = false;
					break;
				case 'b':
					source_x = 0;
					break;
				case 'c':
					source_x = 16;
					break;
				case 'd':
					source_x = 32;
					break;
				case 'e':
					source_x = 48;
					break;
				case 'f':
					source_x = 64;
					break;
				case 'g':
					source_x = 80;
					break;
				case 'h':
					source_x = 96;
					break;
				case 'i':
					source_x = 112;
					break;
				case 'j':
					source_x = 128;
					break;
				case 'k':
					source_x = 144;
					break;
				case 'l':
					source_x = 160;
					break;
				default:
					al_show_native_message_box(NULL, "Error", NULL,
						"Unrecognized tile, program terminated.", NULL, NULL);
					std::exit;
					break;
			}
			if (tile_is_empty){
				al_draw_bitmap_region(tile_bitmap, /*2**/source_x, source_y, TILE_SIZE, TILE_SIZE,
									  i*TILE_SIZE, j*TILE_SIZE, NULL);
			}
			else{
				tile_is_empty = true;
			}
		}
	}
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(a_stage, 0, 0, 0);
	al_flip_display();
	
	event_queue = al_create_event_queue();
	if(!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(tile_bitmap);
		al_destroy_bitmap(a_stage);
		al_destroy_display(display);
        std::exit;
	}
	al_register_event_source(event_queue, al_get_display_event_source(display));
	while(1){
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			al_destroy_bitmap(tile_bitmap);
			al_destroy_bitmap(a_stage);
			al_destroy_display(display);
			al_destroy_event_queue(event_queue);
			break;
		}

	}
}

void run_terrain_test(){
	ALLEGRO_BITMAP *stage1;

	Load_Terrain_Text(STAGE1_PATH);
	Draw_Terrain(TILE_BITMAP_PATH);
}

int main(int argc, char **argv){
	run_terrain_test();
	system( "pause" );
}