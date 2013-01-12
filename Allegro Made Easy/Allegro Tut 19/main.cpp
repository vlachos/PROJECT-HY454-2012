// ALLEGRO TUTORIAL 19 - MOUSE[PART 2] (SOURCE CODE) 
// CODE MADE BY: CODINGMADEEASY
// ALLEGRO VERSION: 4

// Preprocessor Directives 
#define ScreenWidth 640 
#define ScreenHeight 480

#include<allegro.h> 

// Pre Function Declaration
void ButtonUp(int x, int y, int x2, int y2, BITMAP *Buffer); 
void ButtonDown(int x, int y, int x2, int y2, BITMAP *Buffer); 

int main()
{
	// Initializing Allegro
	allegro_init(); 
	install_keyboard();
	install_mouse();
	set_color_depth(32); 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, ScreenWidth, ScreenHeight, 0, 0); 

	// Creating the Buffer
	BITMAP *Buffer = create_bitmap(ScreenWidth, ScreenHeight);

	// Creating and Declaring Variables
	int x = 100, y = 100, moveSpeed = 2;
	bool done = false;

	// Game Loop 
	while(!done)
	{
		// Clear the Screen to the specified Color
		clear_to_color(Buffer, makecol(0, 255, 0));
		if(key[KEY_ESC])
			done = true; 
		
		ButtonUp(100, 100, 200, 130, Buffer);
		if(mouse_b & 1 || mouse_b & 2) 
			ButtonDown(100, 100, 200, 130, Buffer);

		// Display The Mouse on the screen
		show_mouse(Buffer);
		
		// Draw Everything to the Buffer then to the Screen
		blit(Buffer, screen, 0, 0, 0, 0, 640, 480); 
		rest(60); 
		clear_bitmap(Buffer);
	}
	return 0;
}
END_OF_MAIN()

// What to draw when the button is up
void ButtonUp(int x, int y, int x2, int y2, BITMAP *Buffer)
{
	rectfill(Buffer, x - 2, y - 2, x2 + 2, y2 + 2, makecol(0, 0, 0));
	rectfill(Buffer, x, y, x2, y2, makecol(128, 128, 128));
	rectfill(Buffer, x - 1, y, x, y2, makecol(255, 255, 255)); 
    rectfill(Buffer, x - 1, y - 1, x2, y, makecol(255, 255, 255));
}

// What to draw when the button is down
void ButtonDown(int x, int y, int x2, int y2, BITMAP *Buffer)
{
	rectfill(Buffer, x - 2, y - 2, x2 + 2, y2 + 2, makecol(0, 0, 0));
	rectfill(Buffer, x, y, x2, y2, makecol(128, 128, 128));
	rectfill(Buffer, x - 1, y2, x2, y2, makecol(255, 255, 255)); 
    rectfill(Buffer, x2, y, x2 + 1, y2, makecol(255, 255, 255));
}