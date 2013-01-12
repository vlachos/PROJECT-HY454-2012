// ALLEGRO TUTORIAL 23 - BOUNDING BOX COLLISION (SOURCE CODE) 
// CODE MADE BY: CODINGMADEEASY
// ALLEGRO VERSION: 4

// Preprocessor Directives 
#define ScreenWidth 640 
#define ScreenHeight 480

#include<allegro.h> 

// Pre-Defined Functions 
bool Collision(int x, int y, int x2, int y2)
{
	if(x + 10 < x2 || x > x2 + 10 || y + 10 < y2 || y > y2 + 20)
		return false; // No Collision 
	return true; // Collision
}

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
	int x = 10, y = 10, x2 = 100, y2 = 100; 
	int moveSpeed = 5;
	bool done = false;

	// Game Loop 
	while(!done)
	{
		if(key[KEY_ESC])
			done = true;
		if(key[KEY_RIGHT])
			x += moveSpeed; 
		else if(key[KEY_LEFT])
			x -= moveSpeed; 
		else if(key[KEY_UP])
			y -= moveSpeed; 
		else if(key[KEY_DOWN])
			y += moveSpeed;

		// Check to see if a collision has occurred
		if(Collision(x, y, x2, y2))
			allegro_message("Collision");

		// Draw Everything to the Buffer then to the Screen
		rectfill(Buffer, x, y, x + 10, y + 10, makecol(255, 0, 0)); 
		rectfill(Buffer, x2, y2, x2 + 10, y2 + 10, makecol(0, 0, 255));
		blit(Buffer, screen, 0, 0, 0, 0, 640, 480); 
		rest(60); 
		clear_bitmap(Buffer);
	}
	return 0;
}
END_OF_MAIN()