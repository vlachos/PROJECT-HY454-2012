// ALLEGRO TUTORIAL 17 - GRAVITY (SOURCE CODE) 
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
	set_color_depth(32); 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, ScreenWidth, ScreenHeight, 0, 0); 

	// Creating the Buffer
	BITMAP *Buffer = create_bitmap(ScreenWidth, ScreenHeight);

	// Creating and Declaring Variables
	int x = 10, y = 10, moveSpeed = 5, jumpSpeed = -10;
	int velx = 0, vely = 0; 
	int groundHeight = 460;
	const int gravity = 1;
	bool done = false;

	// Game Loop 
	while(!done)
	{
		if(key[KEY_ESC])
			done = true; 
		if(key[KEY_RIGHT])
			velx = moveSpeed;
		else if(key[KEY_LEFT])
			velx = -moveSpeed;
		else 
			velx = 0;

		if(key[KEY_UP])
			vely = jumpSpeed;

		vely += gravity;
		x += velx; 
		y += vely;

		if(y > groundHeight)
			y = groundHeight;

		rectfill(Buffer, x, y, x + 10, y + 10, makecol(255, 0, 0));
		blit(Buffer, screen, 0, 0, 0, 0, 640, 480); 
		rest(60); 
		clear_bitmap(Buffer);
	}
	return 0;
}
END_OF_MAIN()