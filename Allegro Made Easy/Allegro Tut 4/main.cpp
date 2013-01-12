// ALLEGRO TUTORIAL 4 - CHANGING THE FONT (SOURCE CODE) 
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
	
	
	// Change newFontName.pcx to the desired font you're trying to load
	FONT *newFont = load_font("NewFontName.pcx", NULL, NULL); 
	
	// Drawing Text to the screen
	textout_ex(screen, newFont, "Hello World", 0, 0, makecol(255, 255, 255), -1);
	
	// Pauses Program until a Key is Pressed
	readkey(); 
	return 0;
}
END_OF_MAIN()