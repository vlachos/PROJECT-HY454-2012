// ALLEGRO TUTORIAL 2 - CREATING THE SCREEN (SOURCE CODE)
// DO NOT FORGET TO SETUP THE LINKER
// CODE MADE BY: CODINGMADEEASY
// ALLEGRO VERSION: 4

#include<allegro.h> 

int main()
{
	// Initializing Allegro
	allegro_init(); 
	install_keyboard(); 
	install_mouse(); 
	set_color_depth(16); 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0); 
	
	// Pauses Program until a Key is Pressed
	readkey(); 
	return 0;
}
END_OF_MAIN()