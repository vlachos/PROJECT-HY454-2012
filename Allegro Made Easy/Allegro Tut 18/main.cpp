// ALLEGRO TUTORIAL 18 - MOUSE[PART 1] (SOURCE CODE) 
// CODE MADE BY: CODINGMADEEASY
// ALLEGRO VERSION: 4

// Preprocessor Directives 
#define ScreenWidth 640 
#define ScreenHeight 480

#include<allegro.h> 

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
		if(key[KEY_ESC])
			done = true; 
		if(mouse_x < x)
			x -= moveSpeed; 
		else if(mouse_x > x)
			x += moveSpeed; 
		if(mouse_y < y)
			y -= moveSpeed; 
		else if(mouse_y > y)
			y += moveSpeed;

		// Display The Mouse on the screen
		show_mouse(Buffer);
		
		// Draw Everything to the Buffer then to the Screen
		rectfill(Buffer, x, y, x + 10, y + 10, makecol(255, 0, 0));
		blit(Buffer, screen, 0, 0, 0, 0, 640, 480); 
		rest(60); 
		clear_bitmap(Buffer);
	}
	return 0;
}
END_OF_MAIN()