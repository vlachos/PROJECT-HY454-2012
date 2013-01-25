#include <TileLayer.h>
#include "MemoryManage.h"
#include <fstream>

	/*constructors and destructor*/
	TileLayer::TileLayer(){}

	TileLayer::TileLayer(TileBitmap* aTileBitmap){
		tilesBitmap = aTileBitmap;
		viewWindow.SetX(0);
		viewWindow.SetY(0);
		viewWindow.SetWidth(VIEW_WINDOW_WIDTH);
		viewWindow.SetHeigth(VIEW_WINDOW_HEIGHT);
	}

	TileLayer::~TileLayer(){

		for (Dim i=0; i<TILE_LAYER_HEIGHT; ++i){
			for (Dim j=0; j<TILE_LAYER_WIDTH; ++j){		
				map[i][j] = 0;
				tilesSolidity[i][j][Left] = false;
				tilesSolidity[i][j][Up] = false;
				tilesSolidity[i][j][Right] = false;
			}
		}
		delete tilesBitmap;
	}

	/*layer info*/
	bool TileLayer::ReadMap (std::string aPath){
		DASSERT(GetFileAttributesA(aPath.c_str()) != INVALID_FILE_ATTRIBUTES );

		std::ifstream openfile(aPath);
		if (openfile.is_open()){

			openfile.close();
			return true;
		}
		else{
			return false;
		}
	}

	bool TileLayer::ReadStage (std::string aPath){
		DASSERT(GetFileAttributesA(aPath.c_str()) != INVALID_FILE_ATTRIBUTES );

		std::ifstream openfile(aPath);
		unsigned int nextIndex = 0;
		if (openfile.is_open()){
			for (Dim i=0; i<TILE_LAYER_HEIGHT; ++i){
				for (Dim j=0; j<TILE_LAYER_WIDTH; ++j){
					openfile >> nextIndex;
					map[i][j] = nextIndex;
					/*empty or shadow*/
					if (map[i][j] == 0 || map[i][j] >= BIG_BRICK_THRESHOLD){
						tilesSolidity[i][j][BBLeft] = false;
						tilesSolidity[i][j][BBUp] = false;
						tilesSolidity[i][j][BBRight] = false;
					}/*small brick*/
					else if (map[i][j] < SMALL_BRICK_THRESHOLD){
						tilesSolidity[i][j][BBLeft] = true;
						tilesSolidity[i][j][BBUp] = false;
						tilesSolidity[i][j][BBRight] = true;
					}/*big brick*/
					else if (map[i][j] >= SMALL_BRICK_THRESHOLD && map[i][j] <= BIG_BRICK_THRESHOLD){
						tilesSolidity[i][j][BBLeft] = true;
						tilesSolidity[i][j][BBUp] = true;
						tilesSolidity[i][j][BBRight] = true;
					}
					DASSERT( map[i][j] >= 0 && map[i][j] < TILES_BITMAP_SIZE*TILES_BITMAP_SIZE  );
				}
			}
			openfile.close();
			return true;
		}
		else{
			return false;
		}
	}

	void TileLayer::WriteMap (std::string aPath){
		std::ofstream openfile(aPath);
		if (openfile.is_open()){
			for (Dim i=0; i<TILE_LAYER_HEIGHT; ++i){
				for (Dim j=0; j<TILE_LAYER_WIDTH; ++j){
					openfile << (int)map[i][j] << " ";
					openfile << (int)tilesSolidity[i][j][Left] << " ";
					openfile << (int)tilesSolidity[i][j][Up] << " ";
					openfile << (int)tilesSolidity[i][j][Right] << " ";
					openfile << "\t";
				}
				openfile << "\n";
			}
			openfile.close();
		}
	}

	/*layer index map*/
	void TileLayer::Display (Bitmap at){
		DASSERT(at );
		DASSERT(viewWindow.GetX() >= 0 &&
			    viewWindow.GetX() <= (TILE_LAYER_WIDTH - viewWindow.GetWidth()) );
		DASSERT(viewWindow.GetY() >= 0 &&
			    viewWindow.GetY() <= (TILE_LAYER_HEIGHT - viewWindow.GetHeigth()) );

		al_set_target_bitmap(at);
		al_clear_to_color(al_map_rgb(0,0,0));

		Coordinates XYCoordinates;
		for(Dim i=0; i<VIEW_WINDOW_TILE_HEIGHT; ++i){
			for(Dim j=0; j<VIEW_WINDOW_TILE_WIDTH; ++j){
				XYCoordinates = GetXYCoordinates(j, i);

				DASSERT(XYCoordinates.first >= 0 && XYCoordinates.first <= (VIEW_WINDOW_WIDTH - TILE_SIZE) );
				DASSERT(XYCoordinates.second >= 0 && XYCoordinates.second <= (VIEW_WINDOW_HEIGHT - TILE_SIZE) );

				tilesBitmap->PutTile(at, XYCoordinates.first, XYCoordinates.second, GetTile(i, j) );
			}
		}
	}

	void TileLayer::SetTile (Dim row, Dim col, Index indx){
		DASSERT(indx>=0 && indx<256 );
		DASSERT((row>=0 && row<TILE_LAYER_HEIGHT ) &&
				(col>=0 && col<TILE_LAYER_WIDTH ) );

		map[row][col] = indx;
	}

	Index TileLayer::GetTile (Dim row, Dim col){
		DASSERT((row>=0 && row<TILE_LAYER_HEIGHT ) &&
				(col>=0 && col<TILE_LAYER_WIDTH ) );

		return map[row][col];
	}

	const Coordinates TileLayer::GetTileCoordinates (Dim x, Dim y) const{
		DASSERT((x>=0 && x<VIEW_WINDOW_WIDTH ) &&
				(y>=0 && y<VIEW_WINDOW_HEIGHT ) );

		return std::make_pair(DIV_TILE_SIZE(y), DIV_TILE_SIZE(x) );
	}

	const Coordinates TileLayer::GetXYCoordinates (Dim row, Dim col) const{
		DASSERT((row>=0 && row<TILE_LAYER_WIDTH ) &&
				(col>=0 && col<TILE_LAYER_HEIGHT ) );

		return std::make_pair(MUL_TILE_SIZE(row), MUL_TILE_SIZE(col) );
	}

	const bool TileLayer::isSolid(Dim x, Dim y, BBMovement move) const{

		Coordinates tileCoordinates = GetTileCoordinates(x,y);

		return tilesSolidity[tileCoordinates.first]
							[tileCoordinates.second]
							[move];
	}

	/*view window*/
	void TileLayer::SetViewWindow (const Rect& aRect){
		viewWindow = aRect;
	}

	const Rect TileLayer::GetViewWindow (void) const{
		return viewWindow;
	}

	/*scrolling*/
	void TileLayer::Scroll (HorizScroll h, VertScroll v){
		viewWindow.SetX(viewWindow.GetX() + (Dim)h );
		viewWindow.SetY(viewWindow.GetY() + (Dim)v );
	}

	bool TileLayer::CanScroll (HorizScroll h) const{	
		return	viewWindow.GetX() >= -(Dim) h &&
				viewWindow.GetX() + ((Dim) h) + viewWindow.GetWidth() <= VIEW_WINDOW_WIDTH;	
		return false;
	}

	bool TileLayer::CanScroll (VertScroll v) const{
		return	viewWindow.GetY() >= -(Dim) v &&
				viewWindow.GetY() + ((Dim) v) + viewWindow.GetHeigth() <= VIEW_WINDOW_HEIGHT;
		return false;
	}


