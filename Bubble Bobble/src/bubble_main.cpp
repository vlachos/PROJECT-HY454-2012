#include <stdio.h>
#include "bubble_main.h"
#include <allegro5\allegro.h>

int main(){
	ALLEGRO_DISPLAY *display = NULL;

	if(!al_init()){
		fprintf(stderr, "failes to init allegro!\n");
		return -1;
	}

	display = al_create_display(640, 480);

	if(!display){
		fprintf(stderr, "failes to create display!\n");
		return -1;
	}

	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();
	al_rest(10.0);
	al_destroy_display(display);

	return 0;
}