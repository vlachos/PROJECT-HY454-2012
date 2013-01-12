// ALLEGRO TUTORIAL 27 - SCREEN SCROLLING (SOURCE CODE) 
// CODE MADE BY: CODINGMADEEASY
// ALLEGRO VERSION: 4
// THIS CODE IS OPTIMIZED SO THAT YOU DON'T HAVE TO SPECIFY THE WIDTH AND THE HEIGHT IN THE TEXT FILE(VERY CONVENIENT - ESPECIALLY FOR LARGER MAPS)
// NOTE: ALL THE ROWS IN THE TEXT FILE MUST BE THE SAME LENGTH. IF NOT THEN YOU'LL GET AN ERROR.

// Preprocessor Directives 
#define ScreenWidth 640 
#define ScreenHeight 480

#include<allegro.h> 
#include<sstream>
using namespace std;

void ScreenScrolling(int &x, int &y, int virtualX, int virtualY, int &drawPositionX, int &drawPositionY, BITMAP *backgroundImage, BITMAP *Buffer)
{
	if(virtualX > ScreenWidth / 2)
	{
		drawPositionX = (ScreenWidth / 2 - virtualX);
		x = ScreenWidth / 2;
	}
	if(virtualY > ScreenHeight / 2)
	{
		drawPositionY = -(virtualY - ScreenHeight / 2); // Either Way Of Calculation Works out to be the same.
		y = ScreenHeight / 2;
	}
	draw_sprite(Buffer, backgroundImage, drawPositionX, drawPositionY); 
}

void ScreenScrolling();

int main()
{
	// Initializing Allegro
	allegro_init(); 
	install_keyboard();
	install_timer();
	set_color_depth(32); 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, ScreenWidth, ScreenHeight, 0, 0); 

	// Creating and Loading Bitmaps
	BITMAP *Buffer = create_bitmap(ScreenWidth, ScreenHeight);
	BITMAP *BackgroundImage = load_bitmap("background.bmp", NULL);

	// Creating and Declaring Variables 
	bool done = false;
	int x = 0, y = 0, moveSpeed = 5;
	int drawPositionX = 0, drawPositionY = 0;
	int virtualX = 0, virtualY = 0;

	// Game Loop 
	while(!done)
	{
		if(key[KEY_ESC])
			done = true;
		if(key[KEY_RIGHT])
		{
			x += moveSpeed;
			virtualX += moveSpeed;
		}
		else if(key[KEY_LEFT])
		{
			x -= moveSpeed;
			virtualX -= moveSpeed;
		}
		else if(key[KEY_UP])
		{
			y -= moveSpeed;
			virtualY -= moveSpeed;
		}
		else if(key[KEY_DOWN])
		{
			y += moveSpeed;
			virtualY += moveSpeed;
		}
		ScreenScrolling(x, y, virtualX, virtualY, drawPositionX, drawPositionY, BackgroundImage, Buffer);
		stringstream str; 
		str << "X: " << virtualX << "  Y: " << virtualY;
		textout_ex(Buffer, font, str.str().c_str(), 10, 10, makecol(255, 0, 0), -1);
		// Draw Everything to the Buffer then to the Screen
		rectfill(Buffer, x , y , x + 10, y + 10, makecol(255, 0, 0));
		blit(Buffer, screen, 0, 0, 0, 0, 640, 480); 
		rest(60); 
		clear_bitmap(Buffer);
	}
	return 0;
}
END_OF_MAIN()