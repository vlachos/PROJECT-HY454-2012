// ALLEGRO TUTORIAL 5 - KEYBOARD INPUT (SOURCE CODE) 
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
	set_window_title("Game Window Name");
	
	// Loading Fonts
	FONT *newFont = load_font("NewFontName", NULL, NULL);
	
	// Creating and Declaring Variables
	bool done = false; 
	
	// Game Loop
	while(!done)
	{
		if(key[KEY_ESC])
			done = true; 
		if(key[KEY_UP])
			textout_ex(screen, newFont, "Sample Text", 0, 0, makecol(255, 255, 255), -1);
	    else 
			textout_ex(screen, newFont, "Sample Text", 0, 0, makecol(0, 0, 0), -1);
	}
	
	return 0;
}
END_OF_MAIN()