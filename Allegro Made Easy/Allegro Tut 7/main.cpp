// ALLEGRO TUTORIAL 7 - DOUBLE BUFFERING (SOURCE CODE) 
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
	
	// Creating the Buffer
	BITMAP *Buffer = create_bitmap(640, 480);
	
	// Creating and Declaring Variables
	bool done = false; 
	int x = 10, y = 10, speed = 5;
	
	// Game Loop
	while(!done)
	{
		if(key[KEY_ESC])
			done = true; 
		if(key[KEY_UP])
			y -= speed;
	    else if(key[KEY_DOWN])
			y += speed; 
		else if(key[KEY_RIGHT])
			x += speed; 
		else if(key[KEY_LEFT])
			x -= speed;
		
		// Drawing to the Buffer then drawing everything to the screen
		rectfill(Buffer, x, y, x + 10, y + 10, makecol(255, 0, 0));
		blit(Buffer, screen, 0, 0, 0, 0, 640, 480);
		rest(100); 
		clear_bitmap(Buffer);
	}

	return 0;
}
END_OF_MAIN()