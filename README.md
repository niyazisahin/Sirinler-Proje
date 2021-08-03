# Sirinler Game Project
### C++  | SFML Library

SFML graphic library is used in this project.
In order for the project to work, the .dll files included in the source codes must be in the same location and introduced to the compiler.

This is a Smurfs Game.
There are three smurfs (smart smurf, lazy smurf and smurfette) and two enemies (gargamel and his cat).
The player can use just two smurfs (smart smurf and lazy smurf). Smurfs has a differenr feature. Speed. Smart smurfs faster than lazy smurf.
The player must save smurfette for win the game. Smurfette at right of map. If enemies touch the player, player score decreases. If player score less then or equal to zero, Lose this game.

There are mushrooms and golds at random place of map. If the player take them, earn score.

To start the game, the player chooses a character. The selection character start the game at middle of map. The character can move arroe button of the keyboard.
As the player moves, gargamel and his cat begin to follow the player.  This is most important issue. We used algorithm for following. 

## Dijikstra Algorithm.

The algorithm find the shortest path with graph. The algorithm looks at all nodes step by step. Finally, find a shoertest path and paints the road green. Enemies moves to this path.

