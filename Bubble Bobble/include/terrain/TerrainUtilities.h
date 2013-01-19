#ifndef TERRAINUTILITIES_H
#define TERRAINUTILITIES_H

#include <Metrics.h>
#include <utilities.h>

typedef unsigned char Index;

#define TILE_SIZE 16
#define TILES_BITMAP_SIZE 16

/*masks for 16 x 16 tiles bitmap*/
#define	ROW_MASK	0x0F
#define	COL_MASK	0xF0
#define	COL_SHIFT	4

#define MUL_TILE_SIZE(i)	((i)<<4)
#define DIV_TILE_SIZE(i)	((i)>>4)

Index MakeIndex (Dim x, Dim y);

Dim GetCol (Index indx);
Dim GetRow (Index indx);

Dim TileX (Index indx);
Dim TileY (Index indx);

/*index points to pixels*/
typedef unsigned short int Index2; // [MSB X][LSB Y]

#define	TILEX_MASK	0xFF00
#define	TILEX_SHIFT	8
#define	TILEY_MASK	0x00FF

Index MakeIndex2 (byte row, byte col);
Dim TileX2 (Index2 index);
Dim TileY2 (Index2 index);

#endif