#include <TileLayer.h>
#include "MemoryManage.h"
#include <fstream>

	/*constructors and destructor*/
	TileLayer::TileLayer(){}

	TileLayer::TileLayer(TileBitmap* aTileBitmap){
		tiles = aTileBitmap;
		DNEWPTR(Rect, viewWindow);
		viewWindow = DNEWCLASS(Rect, (0, 0, VIEW_WINDOW_WIDTH, VIEW_WINDOW_HEIGHT) );

		DASSERT(viewWindow);
	}

	TileLayer::~TileLayer(){

		for (Dim i=0; i<TILE_LAYER_HEIGHT; ++i){
			for (Dim j=0; j<TILE_LAYER_WIDTH; ++j){		
				map[i][j] = 0;
				tilesSolidity[i][j] = false;
			}
		}
		tiles->~TileBitmap();
		//DDELETE(viewWindow);
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

		std::string nextIndex = "";
		std::ifstream openfile(aPath);
		if (openfile.is_open()){
			for (Dim i=0; i<TILE_LAYER_HEIGHT; ++i){
				for (Dim j=0; j<TILE_LAYER_WIDTH; ++j){
	
					std::getline (openfile, nextIndex, ' ' );
					map[i][j]= (Index)std::atoi((char*)nextIndex.c_str() );
					if (map[i][j] == 0 || map[i][j] > 92){
						tilesSolidity[i][j] = false;
					}
					else{
						tilesSolidity[i][j] = true;
					}
					DASSERT( map[i][j] >= 0 && map[i][j] < 256  );
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
					openfile << (int)map[i][j];
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
			    viewWindow.GetX() <= (DIV_TILE_SIZE(TILE_LAYER_WIDTH) - viewWindow.GetWidth()) );
		DASSERT(viewWindow.GetY() >= 0 &&
			    viewWindow.GetY() <= (DIV_TILE_SIZE(TILE_LAYER_HEIGHT) - viewWindow.GetHeigth()) );

		Bitmap prevTargetBitmap = al_get_target_bitmap();
		Coordinates tileCoordinates;
		al_set_target_bitmap(at);
		
		for(Dim i=0; i<VIEW_WINDOW_TILE_WIDTH; ++i){
			for(Dim j=0; j<VIEW_WINDOW_TILE_HEIGHT; ++j){
				tileCoordinates = GetTileCoordinates (i,j);

				//DASSERT(tileCoordinates.first >= 0 && tileCoordinates.first <= (TILE_LAYER_WIDTH - TILE_SIZE) );
				//DASSERT(tileCoordinates.second >= 0 && tileCoordinates.second <= (TILE_LAYER_HEIGHT - TILE_SIZE) );

				tiles->PutTile(at, tileCoordinates.first, tileCoordinates.second, GetTile (j, i) );
			}
		}

		al_set_target_bitmap(prevTargetBitmap);
	}

	void TileLayer::SetTile (Dim col, Dim row, Index indx){
		DASSERT(indx>=0 && indx<256 );
		DASSERT((row>=0 && row<TILE_LAYER_HEIGHT ) &&
				(col>=0 && col<TILE_LAYER_WIDTH ) );

		map[row][col] = indx;
	}

	Index TileLayer::GetTile (Dim col, Dim row){
		DASSERT((row>=0 && row<TILE_LAYER_HEIGHT ) &&
				(col>=0 && col<TILE_LAYER_WIDTH ) );

		return map[row][col];
	}

	const Coordinates TileLayer::GetTileCoordinates (Dim mx, Dim my) const{
		DASSERT((my>=0 && my<TILE_LAYER_HEIGHT ) &&
				(mx>=0 && mx<TILE_LAYER_WIDTH ) );

		return std::make_pair(MUL_TILE_SIZE(mx), MUL_TILE_SIZE(my) );
	}

	const bool TileLayer::isSolid(Dim x, Dim y) const{
		return tilesSolidity[DIV_TILE_SIZE(x)][DIV_TILE_SIZE(y)];
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


