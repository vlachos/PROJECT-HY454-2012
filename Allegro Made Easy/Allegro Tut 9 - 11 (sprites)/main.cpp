// ALLEGRO TUTORIAL 9 - 11 ~ SPRITES (SOURCE CODE) 
// CODE MADE BY: CODINGMADEEASY
// ALLEGRO VERSION: 4

// Preprocessor Directives
// (Enums Probably would be better or more appropriate but this is fine as well)
#define Down 0 
#define Left 32 
#define Right 64
#define Up 96

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
	BITMAP *WalkingImage = load_bitmap("SpritesheetImageName.bmp", NULL);
	
	// Creating and Declaring Variables
	bool done = false; 
	int x = 10, y = 10, speed = 5;
	int sourceX = 32, sourceY = 0;
	
	// Game Loop
	while(!done)
	{
		if(key[KEY_ESC])
			done = true; 
		if(key[KEY_UP])
		{
			y -= speed;
			sourceY = Up;
		}
		else if(key[KEY_DOWN])
		{
			y += speed; 
			sourceY = Down;
		}
		else if(key[KEY_RIGHT])
		{
			x += speed; 
			sourceY = Right;
		}
		else if(key[KEY_LEFT])
		{
			x -= speed;
			sourceY = Left;
		}
		
		if(!key[KEY_RIGHT] && !key[KEY_LEFT] && !key[KEY_UP] && !key[KEY_DOWN])
			sourceX = 32; 
		else 
			sourceX += 32; 
		
		if(sourceX > 64) 
			sourceX = 0;
		
		// Drawing Images to the Buffer then to the Screen
		blit(BackgroundImage, Buffer, 0, 0, 0, 0, 640, 480);
		masked_blit(WalkingImage, Buffer, sourceX, sourceY, x, y, 32, 32);
		rectfill(Buffer, x, y, x + 10, y + 10, makecol(255, 0, 0));
		blit(Buffer, screen, 0, 0, 0, 0, 640, 480);
		rest(100); 
		clear_bitmap(Buffer);
	}

	return 0;
}
END_OF_MAIN()