// ALLEGRO TUTORIAL 25 - 26 LOADING MAPS (SOURCE CODE) 
// CODE MADE BY: CODINGMADEEASY
// ALLEGRO VERSION: 4
// THIS CODE IS OPTIMIZED SO THAT YOU DON'T HAVE TO SPECIFY THE WIDTH AND THE HEIGHT IN THE TEXT FILE(VERY CONVENIENT - ESPECIALLY FOR LARGER MAPS)
// NOTE: ALL THE ROWS IN THE TEXT FILE MUST BE THE SAME LENGTH. IF NOT THEN YOU'LL GET AN ERROR.

// Preprocessor Directives 
#define ScreenWidth 640 
#define ScreenHeight 480

#include<allegro.h> 
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

// Global Variables
int mapSizeX, mapSizeY;
int loadCounterX = 0 , loadCounterY = 0;
int MapFile[100][100];


// Pre-Defined Functions 
void LoadMap(const char *filename)
{
	string line;
    ifstream openfile(filename);

    if (openfile.is_open())
    {
		getline(openfile, line);
		line.erase( remove( line.begin(), line.end(), ' ' ), line.end() ); // Removes/Trims the Spaces of that line in the text file
		mapSizeX = line.length(); // Makes mapSizeX the width of the map.
		openfile.seekg(0, ios::beg);
		mapSizeY = 0;
        while(!openfile.eof())
        {
            openfile >> MapFile[loadCounterX][loadCounterY];
            loadCounterX ++;
            if (loadCounterX >= mapSizeX)
            {
                loadCounterX = 0;
                loadCounterY ++;
				mapSizeY++;
            }
        }
        loadCounterX = loadCounterY = 0;
    }
    else
    {
        allegro_message("Could not load the specified map file");
    }
}

void DrawMap(int tileWidth, int tileHeight, BITMAP *Buffer)
{
	for(int i = 0; i < mapSizeX; i++)
	{
		for(int j = 0; j < mapSizeY; j++)
		{
			// If you input a number other than 1 or 2 then nothing will show up. Sort of like a transparent box. You could do empty spaces
			// for the sky or something of that sort.
			if(MapFile[i][j] == 1)
				rectfill(Buffer, i*tileWidth, j*tileHeight, i*tileWidth + tileWidth, j*tileHeight + tileHeight, makecol(255, 0, 0));
			else if(MapFile[i][j] == 2)
				rectfill(Buffer, i*tileWidth, j*tileHeight, i*tileWidth + tileWidth, j*tileHeight + tileHeight, makecol(0, 255, 0));
		}
	}
}

// DrawMap Overload Function - If you want to use Tile Images
void DrawMap(int tileWidth, int tileHeight, BITMAP *Buffer, BITMAP *tiles[])
{
	for(int i = 0; i < mapSizeX; i++)
	{
		for(int j = 0; j < mapSizeY; j++)
		{
			stretch_sprite(tiles[MapFile[i][j]], Buffer, i*tileWidth, j*tileHeight, tileWidth, tileHeight);
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

	// Loading the Map 
	LoadMap("map1.txt");

	// Creating the Buffer
	BITMAP *Buffer = create_bitmap(ScreenWidth, ScreenHeight);

	// Creating and Declaring Variables 
	bool done = false;

	// Game Loop 
	while(!done)
	{
		if(key[KEY_ESC])
			done = true;
		
		// Draw Everything to the Buffer then to the Screen
		DrawMap(32, 32, Buffer);
		blit(Buffer, screen, 0, 0, 0, 0, 640, 480); 
		rest(60); 
		clear_bitmap(Buffer);
	}
	return 0;
}
END_OF_MAIN()