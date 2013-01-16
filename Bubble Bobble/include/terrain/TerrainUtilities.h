#ifndef TERRAINUTILITIES_H
#define TERRAINUTILITIES_H

#include <Metrics.h>
#include <utilities.h>

typedef unsigned char Index;
typedef unsigned char byte;

#define TILE_SIZE 16

#define	ROW_MASK	0x0F
#define	COL_MASK	0xF0
#define	COL_SHIFT	4

#define MUL_TILE_WIDTH(i)	((i)<<4)
#define MUL_TILE_HEIGHT(i)	((i)<<4)

Index MakeIndex (Dim x, Dim y);

byte GetCol (Index indx);
byte GetRow (Index indx);

Dim TileX (Index indx);
Dim TileY (Index indx);

#endif