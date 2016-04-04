#define _POSIX_C_SOURCE  200201L
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

void init_world(int *world, int world_size) {
	srand(time(NULL));
	for(int x = 0; x < world_size; x++) {
		world[x] = rand() % LINES/2 + 1;
	}
}

void draw_world(int *world, int world_size) {

	// time delay 0.001s for drawing city
	struct timespec ts = {
		.tv_sec = 0,                    // nr of secs
		.tv_nsec = 0.001 * 1000000000L  // nr of nanosecs
	};

	for(int x = 0; x < world_size; x++) {
		for(int y = 0; y < world[x]; y++) {
			mvprintw(LINES - y - 1, x + 5, "#");
			refresh();
			nanosleep(&ts, NULL); // provides simple effect
		}
	}
}

void game_loop() {
	struct timespec ts = {
		.tv_sec = 0,                  // nr of secs
		.tv_nsec = 0.1 * 1000000000L  // nr of nanosecs
	};
	
	for(int y = 0; y < LINES; y++) {
		int max_col = (y == LINES - 1) ? COLS - 4 : COLS;
		for(int x = 0; x < max_col; x++) {
			mvprintw(y, x, " ^==-");
			refresh();
			nanosleep(&ts, NULL);
		}
	}
}

int main(){
    // initialize the library
    initscr();
    // set implicit modes
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    // invisible cursor, visibility of cursor (0,1,2)
    curs_set(FALSE);
    // getch() will be non-blocking
    nodelay(stdscr, TRUE);

    // your code goes here
    
    //initialize the world
    int world_size = COLS - 10;
    int world[world_size];
    init_world(world, world_size);
    
    // draw the world
    //draw_world(world, world_size);
    
    // loop the game
    game_loop();
    
    // Well Done!
    mvprintw(LINES/2,COLS/2 - 5,"Well Done!");
    refresh();
    
    
    getchar();

    // end curses
    endwin();
}
