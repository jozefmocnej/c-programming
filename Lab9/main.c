#define _POSIX_C_SOURCE  200201L
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <stdbool.h>

enum GameResult {
	WON,
	LOST,
	QUIT
};

void init_world(int *world, int world_size) {
	srand(time(NULL));
	for(int x = 0; x < world_size; x++) {
		world[x] = rand() % LINES / 2 + 1;
	}
}

void draw_world(int *world, int world_size) {
	struct timespec ts = {
		.tv_sec = 0,                    // nr of secs
		.tv_nsec = 0.001 * 1000000000L  // nr of nanosecs
	};


	for(int x = 0; x < world_size; x++) {
		for(int y = 0; y < world[x]; y++) {
			mvprintw(LINES - y - 1, x + 5, "#");
			refresh();
			nanosleep(&ts, NULL);
		}
	}
}

enum GameResult game_loop(int *world, int world_size) {
	struct timespec ts = {
		.tv_sec = 0,                    // nr of secs
		.tv_nsec = 0.1 * 1000000000L  // nr of nanosecs
	};
	
	// helpers
	int cols_padding = 5;
	int world_starting_x = cols_padding;
	int world_ending_x = COLS - cols_padding - 1;
	int bomber_size = 5;
	
	// bomb initialization
	bool is_bomb_dropped = false;
	int bomb_x;
	int bomb_y;
	int destroyed_floors;

	int score = 0;
	int gun_bullets = 50;
	for(int y = 1; y < LINES; y++) {
		int max_col = (y == LINES-1) ? COLS - 4 : COLS;
		for(int x = 0; x < max_col; x++){
			// check the game status
			if(x > cols_padding - bomber_size && x <= COLS - cols_padding - bomber_size && y == LINES - world[x-1]) {
				mvprintw(y, x, " ****");
				refresh();
				return LOST;
			}
			
			mvprintw(0,0, "Score: %d | Gun bullets: %d", score, gun_bullets);
			mvprintw(y, x, " ^==-");	

			// handle user input
			int input = getch();
			switch(input){
				case 'q':
					return QUIT;
				case KEY_DOWN:
					if(!is_bomb_dropped){
						is_bomb_dropped = true;
						bomb_x = x + 1;
						bomb_y = y;
						destroyed_floors = 0;
					}
					break;
				case ' ': {
					if(gun_bullets > 4) {
						gun_bullets -= 5;
						int gun_starting_x = x + bomber_size;
						mvprintw(y, gun_starting_x, "-----");
						refresh();
						nanosleep(&ts, NULL);
						mvprintw(y, gun_starting_x, "     ");
						for(int gun_x = gun_starting_x; gun_x < gun_starting_x + 5; gun_x++) {
							if(gun_x >= world_starting_x && gun_x <= world_ending_x &&
							 y == LINES - world[gun_x - world_starting_x]) {
							 	world[gun_x - world_starting_x]--;
							 	score += 15;
							 }
						}
					}
					break;
				}
			}

			// update bomb
			if(is_bomb_dropped){
				mvprintw(bomb_y, bomb_x, " ");
				bomb_y++;				
				if(bomb_y < LINES && destroyed_floors < 4) {
					if(bomb_x >= world_starting_x && bomb_x <= world_ending_x &&
					 bomb_y == LINES - world[bomb_x - world_starting_x]) {
						world[bomb_x - world_starting_x]--;
						destroyed_floors++;
						score += 5;
						mvprintw(bomb_y, bomb_x, "x");
					} else {
						mvprintw(bomb_y, bomb_x, "v");
					}				
				} else {
					is_bomb_dropped = false;
				}
			}
			
			mvprintw(0,0, "Score: %d | Gun bullets: %d", score, gun_bullets);		
			refresh();
			nanosleep(&ts, NULL);
		}
	}

	return WON;
}

void game_end(enum GameResult result) {
	switch(result) {
		case WON:
		 	mvprintw(LINES / 2, COLS / 2 - 5,"Well Done!");
			break;
		case LOST:
		 	mvprintw(LINES / 2, COLS / 2 - 5,"Game Over!");
			break;
		case QUIT:
			mvprintw(LINES / 2, COLS / 2 - 5,"Quit Game!");
			break;
	}
   
    refresh();
}


int main(){

    //initialize the library
    initscr();
    //set implicit modes
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    // invisible cursor, visibility of cursor (0,1,2)
    curs_set(FALSE);
    // getch() will be non-blocking
    nodelay(stdscr, TRUE);

    // your code goes here
    
    // initialize the world
    int world_size = COLS - 10;
    int world[world_size];
    init_world(world, world_size);
    
    // draw the world
    draw_world(world, world_size);
    
    // loop the game
    enum GameResult result = game_loop(world, world_size);
    
    // print the game result
    game_end(result);

    
    getchar();

    // end curses
    endwin();
}
