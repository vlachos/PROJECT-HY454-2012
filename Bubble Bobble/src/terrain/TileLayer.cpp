#include <TileLayer.h>

	/*public*/
	TileLayer::TileLayer(){
	}

	TileLayer::~TileLayer(){
	}

	/*private*/
	void TileLayer::SetTile (Dim col, Dim row, Index index){
	}
	Index TileLayer::GetTile (Dim col, Dim row){
		return 0;
	}
	const Coordinates TileLayer::GetTileCoordinates (Dim mx, Dim my) const{
		Coordinates a_pair;
		a_pair = std::make_pair(0,0);
		return a_pair;
	}

	void Display (Bitmap at, const Rect& displayArea){
	}

	void Scroll (HorizScroll h, VertScroll v){
//		viewWin.x += (int) h; viewWin.y += (int) v;
	}
	bool CanScroll (HorizScroll h) {	
//		return	viewWin.x >= -(int) h &&
//				viewWin.x + ((int) h) + viewWin.w <= MAX_WIDTH;	
		return false;
	}
	bool CanScroll (VertScroll v) {
//		return	viewWin.y >= -(int) v &&
//				viewWin.y + ((int) v) + viewWin.h <= MAX_HEIGHT;
		return false;
	}

	/*public*/
	void TileLayer::WriteMap (FILE* fp){
	}
	bool TileLayer::ReadMap (FILE* fp){
		return false;
	}
