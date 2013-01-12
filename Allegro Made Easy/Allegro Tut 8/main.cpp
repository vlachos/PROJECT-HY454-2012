// ALLEGRO TUTORIAL 8 - BITMAPS BACKGROUND - LOADING IMAGES (SOURCE CODE) 
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
	
	// Creating and Loading Bitmaps
	BITMAP *Buffer = create_bitmap(640, 480);
	BITMAP *BackgroundImage = load_bitmap("ImageName.bmp", NULL);
	
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
		
		// Drawing Bitmaps to the Buffer and then to the Screen
		blit(BackgroundImage, Buffer, 0, 0, 0, 0, 640, 480);
		rectfill(Buffer, x, y, x + 10, y + 10, makecol(255, 0, 0));
		blit(Buffer, screen, 0, 0, 0, 0, 640, 480);
		rest(100); 
		clear_bitmap(Buffer);
	}

	return 0;
}
END_OF_MAIN()