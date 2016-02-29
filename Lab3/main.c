#include "k.h"
#include "hof.h"

int main(){
    GAME game = {
        .board = {
            {'A', ' ', 'A', ' '},
            {'A', ' ', 'A', ' '},
            {'A', ' ', 'A', ' '},
            {'A', ' ', 'A', ' '}
        },
        .score = 0
    };
    add_random_tile(&game);

    PLAYER hof[10];
    load(hof);
}
