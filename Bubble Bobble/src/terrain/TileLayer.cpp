#include <TileLayer.h>
#include "MemoryManage.h"
#include "PathNames.h"
#include <fstream>

	/*constructors and destructor*/
	TileLayer::TileLayer(){}

	TileLayer::TileLayer(TileBitmap* aTileBitmap){
		tilesBitmap = aTileBitmap;
		viewWindow.SetX(VIEW_WINDOW_START_X);
		viewWindow.SetY(VIEW_WINDOW_START_Y);
		viewWindow.SetWidth(VIEW_WINDOW_TILE_WIDTH);
		viewWindow.SetHeigth(VIEW_WINDOW_TILE_HEIGHT);
	}

	TileLayer::~TileLayer(){

		for (Dim i=0; i<TILE_LAYER_HEIGHT; ++i){
			for (Dim j=0; j<TILE_LAYER_WIDTH; ++j){		
				map[i][j] = 0;
				tilesSolidity[i][j][BBLeft] = false;
				tilesSolidity[i][j][BBUp] = false;
				tilesSolidity[i][j][BBRight] = false;
				tilesSolidity[i][j][BBDown] = false;
			}
		}
		DDELETE( tilesBitmap);
	}

	/*layer info*/
	bool TileLayer::ReadMap (std::string aPath){
		DASSERT(GetFileAttributesA(aPath.c_str()) != INVALID_FILE_ATTRIBUTES );
		std::ifstream actionLayerInfo(aPath);

		unsigned int maxStages = 0;
		unsigned int nextStage = 0;
		if (actionLayerInfo.is_open()){
			
			actionLayerInfo >> maxStages;
			for (unsigned int i=0; i<maxStages; ++i){
				actionLayerInfo >> nextStage;
				ReadStage ( nextStage, i );
			}

			actionLayerInfo.close();
			return true;
		}
		else{
			return false;
		}
	}

	bool TileLayer::ReadStage (unsigned int stageNum, unsigned int ithStage){
		std::cout << "Reading stage: " << stageNum << "\n";
		std::string indexPath;
		indexPath.assign(PathNames::GetStageIndexInfo(stageNum) );
		std::string	sldtyPath;
		sldtyPath.assign(PathNames::GetStageSldtyInfo(stageNum) );

		DASSERT(GetFileAttributesA(indexPath.c_str()) != INVALID_FILE_ATTRIBUTES );
		DASSERT(GetFileAttributesA(sldtyPath.c_str()) != INVALID_FILE_ATTRIBUTES );

		std::ifstream indexStage(indexPath);
		std::ifstream sldtyStage(sldtyPath);
		unsigned int nextInteger = 0;
		if (indexStage.is_open() && sldtyStage.is_open() ){

			unsigned int lastI = ithStage * TILE_LAYER_STAGE_HEIGHT;
			for (unsigned int i=lastI; i<lastI+TILE_LAYER_STAGE_HEIGHT; ++i){
				for (unsigned int j=0; j<TILE_LAYER_STAGE_WIDTH; ++j){
					indexStage >> nextInteger;
					map[i][j] = nextInteger;

					sldtyStage >> nextInteger;
					tilesSolidity[i][j][BBUp] = nextInteger;
					sldtyStage >> nextInteger;
					tilesSolidity[i][j][BBLeft] = nextInteger;
					sldtyStage >> nextInteger;
					tilesSolidity[i][j][BBDown] = nextInteger;
					sldtyStage >> nextInteger;
					tilesSolidity[i][j][BBRight] = nextInteger;
				}
			}
			indexStage.close();
			sldtyStage.close();
			return true;
		}
		else{
			return false;
		}
	}

	void TileLayer::WriteMap (std::string testIndexPath, std::string testSldtyPath){
		std::ofstream MapIndex (testIndexPath);
		std::ofstream MapSldty (testSldtyPath);
		if (MapIndex.is_open() && MapSldty.is_open() ){
			for (Dim i=0; i<TILE_LAYER_HEIGHT; ++i){
				for (Dim j=0; j<TILE_LAYER_WIDTH; ++j){
					MapIndex << (int)map[i][j] ;
					MapIndex << "\t";

					MapSldty << (int)tilesSolidity[i][j][BBUp] << " ";
					MapSldty << (int)tilesSolidity[i][j][BBLeft] << " ";
					MapSldty << (int)tilesSolidity[i][j][BBDown] << " ";
					MapSldty << (int)tilesSolidity[i][j][BBRight] << " ";
					MapSldty << "\t";
				}
				MapIndex << "\n";
				MapSldty << "\n";
			}
			MapIndex.close();
			MapSldty.close();
		}
	}

	/*layer index map*/
	void TileLayer::Display (Bitmap at){
		DASSERT(at );
		DASSERT(viewWindow.GetX() >= 0 &&
			    viewWindow.GetX() <= (TILE_LAYER_WIDTH - VIEW_WINDOW_TILE_WIDTH) );
		DASSERT(viewWindow.GetY() >= 0 &&
			    viewWindow.GetY() <= (TILE_LAYER_HEIGHT - VIEW_WINDOW_TILE_HEIGHT) );

		al_set_target_bitmap(at);
		al_clear_to_color(al_map_rgb(0,0,0));

		Coordinates XYCoordinates;
		for(Dim i = 0; i < VIEW_WINDOW_TILE_HEIGHT; ++i){
			for(Dim j = 0; j < VIEW_WINDOW_TILE_WIDTH; ++j){
				XYCoordinates = GetXYCoordinates(j, i);

				tilesBitmap->PutTile(at, XYCoordinates.first, XYCoordinates.second, GetTileIndex(i, j) );
			}
		}
	}

	void TileLayer::SetTile (Dim row, Dim col, Index indx){
		DASSERT(indx>=0 && indx<256 );
		DASSERT((row>=0 && row<TILE_LAYER_HEIGHT ) &&
				(col>=0 && col<TILE_LAYER_WIDTH ) );

		map[row][col] = indx;
	}

	Index TileLayer::GetTileIndex (Dim row, Dim col){
//		DASSERT((row>=0 && row<TILE_LAYER_HEIGHT ) &&
//				(col>=0 && col<TILE_LAYER_WIDTH ) );

		return map[row + viewWindow.GetY()][col + viewWindow.GetX()];
	}

	const bool TileLayer::GetTileSolidity (int row, int col, BBMovement move) const{
//		DASSERT((row>=0 && row<TILE_LAYER_HEIGHT ) &&
//				(col>=0 && col<TILE_LAYER_WIDTH ) );

		return tilesSolidity[row + viewWindow.GetY()][col + viewWindow.GetX()][move];
	}

	const Coordinates TileLayer::GetTileCoordinates (int x, int y) const{
//		DASSERT((x>=0 && x<VIEW_WINDOW_WIDTH ) &&
//				(y>=0 && y<VIEW_WINDOW_HEIGHT ) );

		return std::make_pair(DIV_TILE_SIZE(y), DIV_TILE_SIZE(x) );
	}

	const Coordinates TileLayer::GetXYCoordinates (Dim row, Dim col) const{
//		DASSERT((row>=0 && row<TILE_LAYER_WIDTH ) &&
//				(col>=0 && col<TILE_LAYER_HEIGHT ) );

		return std::make_pair(MUL_TILE_SIZE(row), MUL_TILE_SIZE(col) );
	}

	const bool TileLayer::isSolid(int x, int y, BBMovement move) const{

		Coordinates tileCoordinates = GetTileCoordinates(x,y);

		return GetTileSolidity(tileCoordinates.first, tileCoordinates.second, move);
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
		if ( CanScroll(h) )
			viewWindow.SetX(viewWindow.GetX() + (Dim)h );
		if ( CanScroll(v) )
 			viewWindow.SetY(viewWindow.GetY() + (Dim)v );
	}

	bool TileLayer::CanScroll (HorizScroll h) const{	
		return	((int)viewWindow.GetX()) >= -((int)h) &&
				((int)viewWindow.GetX()) + ((int) h) + ((int)viewWindow.GetWidth()) <= TILE_LAYER_WIDTH;	
		return false;
	}

	bool TileLayer::CanScroll (VertScroll v) const{
		return	((int)viewWindow.GetY()) >= -((int)v) &&
				((int)viewWindow.GetY()) + ((int) v) + ((int)viewWindow.GetHeigth()) <= TILE_LAYER_HEIGHT;
		return false;
	}


