// ALLEGRO TUTORIAL 15 - BULLETS (SOURCE CODE) 
// CODE MADE BY: CODINGMADEEASY
// ALLEGRO VERSION: 4

#include<allegro.h> 

int main()
{
	// Initializing Allegro
	allegro_init(); 
	install_keyboard(); 
	set_color_depth(32); 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0); 
	set_window_title("Game Window Title");
	
	// Creating the Buffer
	BITMAP *Buffer = create_bitmap(640, 480); 
	
	// Creating and Declaring variables
	bool done = false; 
	int bX[1000], bY[1000];
	int counter = 0; 
	
	// Setting the Default Bullet Position
	for(int i= 0; i <= 999; i++)
	{
		bX[i] = 10; 
		bY[i] = 10;
	}
	
	// Game Loop 
	while(!done)
	{
		if(key[KEY_ESC])
			done = true;
		if(key[KEY_Z])
			counter++;
		for(int i = 1; i <= Counter; i++)
		{
			bX[i] += 5; // You should also create a variable called moveSpeed
			circle(Buffer, bX[i], bY[i], 5, makecol(255, 0, 0));
			//     Buffer, XPosition, YPosition, Radius, Color
		}
		// Drawing the Bullets to the Screen
		blit(Buffer, screen, 0, 0, 0, 0, 640, 480);
		rest(60); 
		clear_bitmap(Buffer);
	}
}
END_OF_MAIN()