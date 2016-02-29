#include <stdlib.h>
#include "k.h"

void add_random_tile(GAME *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % 4;
        col = rand() % 4;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    int tile = 'A' + (rand() % 2);
    game->board[row][col] = tile;
}
