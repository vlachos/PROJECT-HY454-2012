// ALLEGRO TUTORIAL 20 - FRAMES PER SECOND (SOURCE CODE) 
// CODE MADE BY: CODINGMADEEASY
// ALLEGRO VERSION: 4

// Preprocessor Directives 
#define ScreenWidth 640 
#define ScreenHeight 480

#include<allegro.h> 

// Global Declarations
volatile long Counter = 0; 
void Increment(){ Counter ++; }

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

	// Creating and Declaring Variables
	bool done = false;
	
	// Locking the Variable and Function and Setting the timer(Locking is used for DOS Programs)
	LOCK_VARIABLE(Counter);
	LOCK_FUNCTION(Increment);
	install_int_ex(Increment, BPS_TO_TIMER(100));

	// Game Loop 
	while(!done)
	{
		// Frame Loop
		while(Counter > 0)
		{
			if(key[KEY_ESC])
				done = true; 

			Counter -- ;
		}
		// Draw Everything to the Buffer then to the Screen
		blit(Buffer, screen, 0, 0, 0, 0, 640, 480); 
		rest(60); 
		clear_bitmap(Buffer);
	}
	return 0;
}
END_OF_MAIN()
