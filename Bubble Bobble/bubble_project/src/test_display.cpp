#include <stdio.h>
#include <iostream>
#include <fstream>
#include <allegro5/allegro.h>

const int tile_size = 8;

const char* TERRAIN__DATA_PATH = "..\\data\\terrain_data";
const char*	STAGE1_PATH = "..\\data\\terrain_data\\stage1.txt";
const char* TILE_BITMAP_PATH = "..\\data\\terrain_data\\tile_bitmap.png";

const int SCREEN_W = 800;
const int SCREEN_H = 600;
unsigned char *terrain;
unsigned int terrain_x, terrain_y;


unsigned char get_terrain_tile(int row, int col){
	return terrain[row+col*terrain_x];
}

void Load_Terrain_Text(std::string filename){
	unsigned int load_counter_x = 0, load_counter_y = 0;

	std::ifstream openfile(filename);
	if (openfile.is_open()){
		openfile >> terrain_x >> terrain_y;

		terrain = new unsigned char [terrain_x*terrain_y];
		for (int i=0; i<terrain_y; ++i){
			for (int j=0; j<terrain_x; ++j){
				openfile >> terrain[i+j*terrain_x];
			}
		}
		
	}
}

void Draw_Terrain(){
	for (int i=0; i<terrain_y; ++i){
		for (int j=0; j<terrain_x; ++j){

			switch ( get_terrain_tile(i,j)){
				case 'a':
					std::putchar('a');
					break;
				case 'b':
					std::putchar('b');
					break;
				case 'c':
					std::putchar('c');
					break;
				case 'd':
					std::putchar('d');
					break;
				case 'e':
					std::putchar('e');
					break;
				case 'f':
					std::putchar('f');
					break;
				case 'g':
					std::putchar('g');
					break;
				case 'h':
					std::putchar('h');
					break;
				case 'i':
					std::putchar('i');
					break;
				case 'j':
					std::putchar('j');
					break;
				case 'k':
					std::putchar('k');
					break;
				case 'l':
					std::putchar('l');
					break;
				default:
					std::puts("Unrecognized tile, program terminated.");
					std::exit;
					break;

			}
		}
		std::putchar('\n');
	}
}

void run_terrain_test(){
	Load_Terrain_Text(STAGE1_PATH);
	Draw_Terrain();
	getchar();
}