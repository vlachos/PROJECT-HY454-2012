The picture contains 2 rows of 6 tiles per stage that are needed
to build a tile based terrain of the bubble bobble game.

each tile has width = 8, height = 8

first row:
0,0: (0,0) - (8,8) -> empty tile
0,1: (8,0) - (16,8) -> top left part of big brick
0,2: (16,0) - (24,8) -> top right part of big brick
0,3: (24,0) - (32,8) -> main horizontal shadow
0,4: (32,0) - (40,8) -> last horizontal shadow (left)
0,5: (40,0) - (48,8) -> last horizontal shadow (right)

second row:
1,0: (0,8) - (8,16) -> small brick
1,1: (8,8) - (16,16) -> bot left part of big brick
1,2: (16,8) - (24,16) -> bot right part of big brick
1,3: (24,8) - (32,16) -> main vertical shadow
1,4: (32,8) - (40,16) -> last vertical shadow(left)
1,5: (40,8) - (48,16) -> first horizontal shadow (left) [corner]
