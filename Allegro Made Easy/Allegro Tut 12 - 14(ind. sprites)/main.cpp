// ALLEGRO TUTORIAL 12 - 14 ~ INDIVIDUAL SPRITES(SOURCE CODE) 
// CODE MADE BY: CODINGMADEEASY
// ALLEGRO VERSION: 4

#include<allegro.h> 
#include<sstream> 
#include<string> 
#include<cstring>

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
	BITMAP *Walk[12];
	
	// Creating and Declaring Variables
	int walkCounter = 0;
	bool done = false; 
	int x = 10, y = 10, speed = 5;
	
	// Loading the bitmap images
	for(int i = 0; i < 12; i++)
	{
		std::stringstream walk; 
		walk << "FilePath\\FileName" << i + 1 << ".bmp";
		Walk[i] = load_bitmap(walk.str().c_str(), NULL);
		if(!Walk[i])
			allegro_message("Error Could not open %s", walk.str().c_str());
	}
	
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
		
		// Drawing To the Buffer then drawing everything to the screen
		blit(BackgroundImage, Buffer, 0, 0, 0, 0, 640, 480);
		if(walkCounter > 5) 
			walkCounter = 0;
		draw_sprite(Buffer, Walk[walkCounter], x, y);
		walkCounter++;
		blit(Buffer, screen, 0, 0, 0, 0, 640, 480);
		rest(100); 
		clear_bitmap(Buffer);
	}

	return 0;
}
END_OF_MAIN()