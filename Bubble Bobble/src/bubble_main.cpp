#include <stdio.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <allegro5\allegro5.h> 
#include <allegro5\allegro_native_dialog.h> 
#include <allegro5\allegro_image.h>

const int TILE_SIZE = 8;

const char* TERRAIN_DATA_PATH = "..\\data\\terrain_data";
const char*	STAGE1_PATH = "..\\data\\terrain_data\\stage1.txt";
const char* TILE_BITMAP_PATH = "..\\data\\terrain_data\\tile_bitmap.png";

#define SCREEN_W 800
#define SCREEN_H 600
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
		std::cout << terrain_x << terrain_y;
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
	ALLEGRO_BITMAP *a_stage = 0;
	unsigned int source_x, source_y;

	/*init*/
			std::cout << "Hello";
	if(!al_init())
		al_show_native_message_box(NULL, "Error", NULL, "Could not Initialize Allegro", NULL, NULL); 

	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display)
		al_show_native_message_box(NULL, "Error", NULL, "Could not create Allegro Display", NULL, NULL);

	al_set_window_position(display, 200, 200);
	al_install_keyboard();
	al_init_image_addon();
	a_stage = al_load_bitmap(bitmap_path);

	/*display each tile based on the already readen stage1.txt*/
	for (int i=0; i<terrain_x; ++i){
		for (int j=0; j<terrain_y; ++j){
			switch ( get_terrain_tile(j,i)){
				case 'a':
					source_x = 0;
					source_y = 0;
					break;
				case 'b':
					source_x = 0;
					source_y = 8;
					break;
				case 'c':
					source_x = 8;
					source_y = 0;
					break;
				case 'd':
					source_x = 8;
					source_y = 8;
					break;
				case 'e':
					source_x = 16;
					source_y = 0;
					break;
				case 'f':
					source_x = 16;
					source_y = 8;
					break;
				case 'g':
					source_x = 24;
					source_y = 0;
					break;
				case 'h':
					source_x = 24;
					source_y = 8;
					break;
				case 'i':
					source_x = 32;
					source_y = 0;
					break;
				case 'j':
					source_x = 32;
					source_y = 8;
					break;
				case 'k':
					source_x = 40;
					source_y = 0;
					break;
				case 'l':
					source_x = 40;
					source_y = 8;
					break;
				default:
					al_show_native_message_box(NULL, "Error", NULL,
						"Unrecognized tile, program terminated.", NULL, NULL);
					std::exit;
					break;

				

			}
			al_draw_bitmap_region(a_stage, source_x, source_y, TILE_SIZE, TILE_SIZE,
									  i, j, NULL);
			al_flip_display();
			//al_clear_to_color(al_map_rgb(0, 0, 0));
			//std::cout <<  get_terrain_tile(i,j);
		}
		std::cout <<  '\n';
	}
}

void run_terrain_test(){
	ALLEGRO_BITMAP *stage1;

	Load_Terrain_Text(STAGE1_PATH);
	Draw_Terrain(TILE_BITMAP_PATH);
	getchar();
}

int main(int argc, char **argv){
	run_terrain_test();
}