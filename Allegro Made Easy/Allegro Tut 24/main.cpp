// ALLEGRO TUTORIAL 24 - PIXEL COLLISION (SOURCE CODE) 
// CODE MADE BY: CODINGMADEEASY
// ALLEGRO VERSION: 4

// Preprocessor Directives 
#define ScreenWidth 640 
#define ScreenHeight 480

// (Enums Probably would be better or more appropriate but it doesn't really matter)
#define Right 1 
#define Left  2 
#define Up    3
#define Down  4

#include<allegro.h> 

// Pre-Defined Functions 
void PixelCollision(int &x, int &y, int width, int height, int moveSpeed, int dir, int col, BITMAP *Buffer)
{
	for(int i = x; i < x + width; i++)
	{
		for(int j = y; j < y + height; j++)
		{
			if(getpixel(Buffer, i , j) == col)
			{
				if(dir == Right)
					x -= moveSpeed; 
				else if(dir == Left)
					x += moveSpeed; 
				else if(dir == Up)
					y += moveSpeed; 
				else 
					y -= moveSpeed;
				break; // This is important. If you remove this then you'll notice a glitch in the collision process
				// If 2 or more pixels have collided with the box and say you were moving right then it would be 
				// x -= moveSpeed * 2 because there's 2 pixels. That means the box will move 2 far back. The break statement removes that 
				// glitch and just exits the for loop
			}
		}
	}
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
	int dir = Right;
	int moveSpeed = 5;
	bool done = false;

	// Game Loop 
	while(!done)
	{
		if(key[KEY_ESC])
			done = true;
		if(key[KEY_RIGHT])
		{
			x += moveSpeed;
			dir = Right;
		}
		else if(key[KEY_LEFT])
		{
			x -= moveSpeed;
			dir = Left;
		}
		else if(key[KEY_UP])
		{
			y -= moveSpeed;
			dir = Up;
		}
		else if(key[KEY_DOWN])
		{
			y += moveSpeed;
			dir = Down;
		}

		// Draw Everything to the Buffer then to the Screen
		rectfill(Buffer, x, y, x + 10, y + 10, makecol(255, 0, 0)); 
		rectfill(Buffer, x2, y2, x2 + 10, y2 + 10, makecol(0, 0, 255));
		// Check to see if a collision has occurred(Has to be after we draw everything to the buffer[or at least draw the colliding item before
		// you put this])
		PixelCollision(x, y, 10, 10, moveSpeed, dir, makecol(0, 0, 255), Buffer);
		//rectfill(Buffer, x, y, x + 10, y + 10, makecol(255, 0, 0)); [this is the same as above. Comment out the one above then uncomment
		// this one to see the difference :)
		blit(Buffer, screen, 0, 0, 0, 0, 640, 480); 
		rest(60); 
		clear_bitmap(Buffer);
	}
	return 0;
}
END_OF_MAIN()