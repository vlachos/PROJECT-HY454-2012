// ALLEGRO TUTORIAL 22 - CLOSE WINDOW WITH THE X BUTTON(SOURCE CODE) 
// CODE MADE BY: CODINGMADEEASY
// ALLEGRO VERSION: 4

// Preprocessor Directives 
#define ScreenWidth 640 
#define ScreenHeight 480

#include<allegro.h> 

// Global Declarations
volatile bool done = false;
void Handler() { done = true; }

int main()
{
	// Initializing Allegro
	allegro_init(); 
	install_keyboard();
	install_timer();
	set_color_depth(32); 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, ScreenWidth, ScreenHeight, 0, 0); 

	// Creating the Buffer
	BITMAP *Buffer = create_bitmap(ScreenWidth, ScreenHeight);

	// Locking the Function and Creating the Close Button(Locking is used for DOS Programs)
	LOCK_FUNCTION(Handler);
	set_close_button_callback(Handler);

	// Game Loop 
	while(!done)
	{
		if(key[KEY_ESC])
			done = true;
		// Draw Everything to the Buffer then to the Screen
		blit(Buffer, screen, 0, 0, 0, 0, 640, 480); 
		rest(60); 
		clear_bitmap(Buffer);
	}
	return 0;
}
END_OF_MAIN()