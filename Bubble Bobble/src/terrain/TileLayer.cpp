#include <TileLayer.h>
#include "MemoryManage.h"
#include <fstream>

	/*public*/
	TileLayer::TileLayer(){
		layer = al_create_bitmap(MAX_WIDTH, MAX_HEIGHT );
		DNEWPTR(Rect, viewWindow);
		viewWindow = DNEWCLASS(Rect, (0, 0, VIEW_WINDOW_WIDTH, VIEW_WINDOW_HEIGHT) );

		DASSERT(viewWindow);
		DASSERT(layer);
	}

	TileLayer::~TileLayer(){
		DDELETE(layer);
//		DDELARR(map);
	}

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
		if (openfile.is_open()){
			for (unsigned int i=0; i<MAX_HEIGHT; ++i){
				for (unsigned int j=0; j<MAX_WIDTH; ++j){
					openfile >> map[i][j];
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
		DASSERT(GetFileAttributesA(aPath.c_str()) != INVALID_FILE_ATTRIBUTES );

		std::ofstream openfile(aPath);
		if (openfile.is_open()){
			for (unsigned int i=0; i<MAX_HEIGHT; ++i){
				for (unsigned int j=0; j<MAX_WIDTH; ++j){
					openfile << map[i][j];
				}
			}
			openfile.close();
		}
	}

	void TileLayer::Display (Display_t at, const Rect& displayArea){
		DASSERT(at );

		al_set_target_bitmap(al_get_backbuffer(at));
		al_draw_bitmap_region(layer, displayArea.GetX(), displayArea.GetY(),
									 displayArea.GetWidth(), displayArea.GetHeigth(),
									 0, 0, NULL);
		al_flip_display();		
	}

	void TileLayer::SetTile (Dim col, Dim row, Index indx){
		DASSERT(indx>=0 && indx<256 );
		DASSERT((row>=0 && row<MAX_HEIGHT ) && (col>=0 && col<MAX_WIDTH ) );

		map[row][col] = indx;
	}

	Index TileLayer::GetTile (Dim col, Dim row){
		DASSERT((row>=0 && row<MAX_HEIGHT ) && (col>=0 && col<MAX_WIDTH ) );

		return map[row][col];
	}

	const Coordinates TileLayer::GetTileCoordinates (Dim mx, Dim my) const{
		DASSERT((my>=0 && my<MAX_HEIGHT ) && (mx>=0 && mx<MAX_WIDTH ) );

		return std::make_pair(DIV_TILE_SIZE(mx), DIV_TILE_SIZE(my) );
	}

	void TileLayer::Scroll (HorizScroll h, VertScroll v){
		viewWindow.SetX(viewWindow.GetX() + (int)h );
		viewWindow.SetY(viewWindow.GetY() + (int)v );
	}

	void TileLayer::SetViewWindow (const Rect& aRect){
		viewWindow = aRect;
	}

	const Rect TileLayer::GetViewWindow (void) const{
		return viewWindow;
	}

	bool TileLayer::CanScroll (HorizScroll h) const{	
		return	viewWindow.GetX() >= -(int) h &&
				viewWindow.GetX() + ((int) h) + viewWindow.GetWidth() <= VIEW_WINDOW_WIDTH;	
		return false;
	}

	bool TileLayer::CanScroll (VertScroll v) const{
		return	viewWindow.GetY() >= -(int) v &&
				viewWindow.GetY() + ((int) v) + viewWindow.GetHeigth() <= VIEW_WINDOW_HEIGHT;
		return false;
	}


