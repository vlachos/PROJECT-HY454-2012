#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>

#define TILE_SIZE 8
#define TERRAIN__DATA_PATH "..\data\terrain_data"
#define STAGE1 "stage1.txt"
#define TILE_BITMAP "tile_bitmap.png"

const int SCREEN_W = 800;
const int SCREEN_H = 600;
unsigned char *terrain;
unsigned int terrain_x, terrain_y;

unsigned int get_terrain_tile(int row, int col){
	return terrain[row+col*terrain_y];
}

void Load_Terrain(std::string filename){
	unsigned int load_counter_x = 0, load_counter_y = 0;

	std::ifstream openfile(filename);
	if (openfile.is_open()){
		openfile >> terrain_x >> terrain_y;
		std::putchar(terrain_x);
		std::putchar('\t');

		terrain = new unsigned char[terrain_x * terrain_y];
		for (int i=0; i<terrain_x; ++i)
			for (int j=0; j<terrain_y; ++j)
				openfile >> terrain[i*j];
		
	}

}

void DrawMap(){
	for (int i=0; i<terrain_x; ++i){
		for (int j=0; j<terrain_y; ++j){
			std::putchar(get_terrain_tile(i,j));
/*
			switch ( get_terrain_tile(i,j)){
				case 'a':
					break;
				case 'b':
					break;
				case 'c':
					break;
				case 'd':
					break;
				case 'e':
					break;
				case 'f':
					break;
				case 'g':
					break;
				case 'h':
					break;
				case 'i':
					break;
				case 'j':
					break;
				case 'k':
					break;
				case 'l':
					break;
				default:
					std::puts("Unrecognized tile, program terminated.");
					std::exit;
					break;

			}
*/		}
		std::putchar('\n');
	}
}

int main(int argc, char **argv){

	ALLEGRO_DISPLAY *display;
	bool done = false;

	std::string terrain_data_path = TERRAIN__DATA_PATH;
	terrain_data_path.append(STAGE1);
	Load_Terrain(terrain_data_path);
	
	terrain_data_path = TERRAIN__DATA_PATH;
/*
	if (!al_init()){
		al_show_native_message_box(NULL,"Error", NULL, "Could not initialize Allegro", NULL, NULL);
	}

	if ( (display = al_create_display(SCREEN_W, SCREEN_H)) == NULL){
	}
*/
	DrawMap();
	getchar();
}