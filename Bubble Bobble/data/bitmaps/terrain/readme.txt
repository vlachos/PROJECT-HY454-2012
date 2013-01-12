
- REGARDING TILE BITMAP


The tile bitmap contains 1 row of 11 tiles per stage that are needed
to build a tile based terrain of the bubble bobble game.

each tile has width = 16, height = 16

starting pixel:
(0,0) -> small brick
(16,0) -> top left part of big brick
(32,0) -> bot left part of big brick
(48,0) -> top right part of big brick
(64,0) -> bot right part of big brick
(80,0) -> main horizontal shadow
(96,0) -> main vertical shadow
(112,0) -> first horizontal shadow (right) \_
(128,0) -> last vertical shadow(right) \
(144,0) -> last horizontal shadow (left) -
(160,0) -> corner shadow |-
 

- TRANSPARENCY

1)All shadows are transparent
2)all parts of big brick are not transparent
3)small brick is only transparent from bottom


- REGARDING TEXTS


Vocabulary of each tile number in the stage texts.


a: empty
b: small brick
c: top left part of big brick
d: bot left part of big brick
e: top right part of big brick
f: bot right part of big brick 
g: main horizontal shadow _
h: main vertical shadow |
i: first horizontal shadow (right) \_
j: last vertical shadow(right) \						    |
k: last horizontal shadow (left) -
l: corner shadow |-