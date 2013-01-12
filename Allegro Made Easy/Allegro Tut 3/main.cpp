// ALLEGRO TUTORIAL 3 - TEXT (SOURCE CODE) 
// CODE MADE BY: CODINGMADEEASY
// ALLEGRO VERSION: 4

#include<allegro.h> 

int main()
{
	// Initializing Allegro
	allegro_init(); 
	install_keyboard(); 
	set_color_depth(16); 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	
	// Clear the Screen to a certain Color
	clear_to_color(screen, makecol(0, 255, 0));
	
	// Drawing text to the screen
	textout_ex(screen, font, "Hello World", 0, 0, makecol(255, 255, 255), -1);
	//        (Buffer, Font, Text, X Position, Y Position, Font Color, Background Color)
	
	// Pauses Program until a Key is Pressed
	readkey(); 
	return 0;
}
END_OF_MAIN()