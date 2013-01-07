The picture contains 2 rows of 6 tiles per stage that are needed
to build a tile based terrain of the bubble bobble game.

each tile has width = 8, height = 8

first row:
0,0: (0,0) - (8,8) -> top left part of big brick
0,1: (8,0) - (16,8) -> top right part of big brick
0,2: (16,0) - (24,8) -> small brick
0,3: (24,0) - (32,8) -> shadow bottom of break
0,4: (32,0) - (40,8) -> last shadow bottom of break (only for brick rows from right to left)
0,5: (40,0) - (48,8) -> last shadow right of break (only for brick rows from left to right)

second row:
1,0: (0,8) - (8,16) -> bot left part of big brick
1,1: (8,8) - (16,16) -> bot right part of big brick
1,2: (16,8) - (24,16) -> shadow right of break
1,3: (24,8) - (32,16) -> first shadow bottom of break (only for brick rows from left to right)
1,4: (32,8) - (40,16) -> last shadow bottom of break (only for brick rows from left to right)
1,5: (40,8) - (48,16) -> empty tile
