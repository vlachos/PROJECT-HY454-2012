// ALLEGRO TUTORIAL 27 - SCREEN SCROLLING(SOURCE CODE)
// CODE MADE BY: CODINGMADEEASY
// ALLEGRO VERSION: 4


// Preprocessor Directives
#define ScreenWidth 640
#define ScreenHeight 480

#define VirtualWidth 1000
#define VirtualHeight 1000

#include<allegro.h>
#include<sstream>
using namespace std;

void ScreenScrolling(int x, int y, int &cameraX, int &cameraY)
{
	cameraX = x - ScreenWidth / 2;
	cameraY = y - ScreenHeight / 2;

	if(cameraX < 0)
		cameraX = 0;
	if(cameraY < 0)
		cameraY = 0;
}

void ScreenScrolling(int &x, int &y, int virtualX, int virtualY, int &drawPositionX, int &drawPositionY)
{
	if(virtualX > ScreenWidth / 2)
	{
	    // Will end up being a negative number
		drawPositionX = (ScreenWidth / 2 - virtualX);
		x = ScreenWidth / 2;
	}
	if(virtualY > ScreenHeight / 2)
	{
		drawPositionY = -(virtualY - ScreenHeight / 2); // Either Way Of Calculation Works out to be the same.
		y = ScreenHeight / 2;
	}
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
	BITMAP *Buffer = create_bitmap(VirtualWidth, VirtualHeight);
	BITMAP *BackgroundImage = load_bitmap("background.bmp", NULL);

	// Creating and Declaring Variables
	bool done = false;
	int x = 0, y = 0, moveSpeed = 5;
	int drawPositionX = 0, drawPositionY = 0;
	int cameraX = 0, cameraY = 0;
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

		ScreenScrolling(x, y, cameraX, cameraY);
		//ScreenScrolling(x, y, virtualX, virtualY, drawPositionX, drawPositionY, BackgroundImage, Buffer);
		stringstream str;
		str << "X: " << virtualX << "  Y: " << virtualY;
		draw_sprite(Buffer, BackgroundImage, drawPositionX, drawPositionY);
		textout_ex(Buffer, font, str.str().c_str(), 10 + cameraX, 10 + cameraY, makecol(255, 0, 0), -1);
		// Draw Everything to the Buffer then to the Screen
		rectfill(Buffer, x , y , x + 10, y + 10, makecol(255, 0, 0));
		blit(Buffer, screen, cameraX, cameraY, 0, 0, 640, 480);
		rest(60);
		clear_bitmap(Buffer);
	}
	return 0;
}
END_OF_MAIN()
