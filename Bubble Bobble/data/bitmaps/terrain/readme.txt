
- REGARDING TILE BITMAP


The tile bitmap contains 2 rows of 6 tiles per stage that are needed
to build a tile based terrain of the bubble bobble game.

each tile has width = 8, height = 8

first row:
0,0: (0,0) - start pixel size(8,8) -> empty tile
0,1: (8,0) - start pixel size(16,8) -> top left part of big brick
0,2: (16,0) - start pixel size(24,8) -> top right part of big brick
0,3: (24,0) - start pixel size(32,8) -> main horizontal shadow
0,4: (32,0) - start pixel size(40,8) -> last horizontal shadow (left)
0,5: (40,0) - start pixel size(48,8) -> last horizontal shadow (right)

second row:
1,0: (0,8) - start pixel size(8,16) -> small brick
1,1: (8,8) - start pixel size(16,16) -> bot left part of big brick
1,2: (16,8) - start pixel size(24,16) -> bot right part of big brick
1,3: (24,8) - start pixel size(32,16) -> main vertical shadow
1,4: (32,8) - start pixel size(40,16) -> last vertical shadow(left)
1,5: (40,8) - start pixel size(48,16) -> first horizontal shadow (left) [corner]


- TRANSPARENCY

1)All shadows are transparent
2)all parts of big brick are not transparent
3)small brick is only transparent from bottom


- REGARDING TEXTS


Vocabulary of each tile number in the stage texts.


a0: empty
b1: small brick
c2: top left part of big brick
d3: bot left part of big brick
e4: top right part of big brick
f5: bot right part of big brick 
g6: main horizontal shadow _
h7: main vertical shadow |
i8: first horizontal shadow (right) \_
j9: last vertical shadow(right) \
							    |
k10: last horizontal shadow (left) -
l11: corner shadow |-