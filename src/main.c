#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE     3
#define AREA     SIZE*SIZE
#define GAMEOVER ((1 << AREA) - 1)

typedef struct Board {
	unsigned int x;
	unsigned int o;
	unsigned int turn;
	unsigned int history[AREA];
} Board;

const int WIN_STATES_COUNT = 2*SIZE + 2;
const int WIN_STATES[] = {7,56,448,73,146,273,292,84};

bool is_winner(const int board) {
	int i;
	for (i = 0; i < WIN_STATES_COUNT; i++) {
		if ((WIN_STATES[i] & board) == WIN_STATES[i]) {
			return true;
		}
	}
	return false;
}

Board *new_board() {
	int i;
	Board *board;

	board = malloc(sizeof(Board));
	if (board == NULL) {
		fprintf(stderr, "Out of Mmeory!");
	}
	board->turn = 1;
	board->x = 0;
	board->o = 0;
	for (i = 0; i < AREA; i++) {
		board->history[i] = 0;
	}
	return board;
}

bool valid_move(Board *board, const int move) {
	if ((move > AREA-1) || (move < 0))            return false;
	if ((board->x | board->o) & (1 << move)) return false;
	return true;
}

unsigned int read_move(Board *board) {
	unsigned int move;
	do { 
		printf("Enter Move (1-%d): ", AREA);
		scanf("%u", &move);
		--move;
	} while(!valid_move(board, move));
	return move;
}


void make_move(Board *board, const int move) {
	unsigned int *player = board->turn?&board->x:&board->o;
	*player = *player | (1 << move);
}

int game_over(Board *board) {
	return (is_winner(board->x) || is_winner(board->o) || ((board->x | board->o) == GAMEOVER));
}

void display_board(Board *board) {
	int cell;
	putchar('\n');
	for (cell = 0; cell < AREA; cell++) {
		if      ((board->x >> cell) & 1) putchar('X');
		else if ((board->o >> cell) & 1) putchar('O');
		else                             putchar('-');
		if (cell % SIZE == SIZE-1) putchar('\n');
	}
	putchar('\n');
	printf("TURN: %c\n\n", board->turn?'X':'O');
}

void tests() {
	int i;
	Board *board;
	board = malloc(sizeof(Board));
	/* WIN STATES */
	for (i = 0; i < WIN_STATES_COUNT; i++) {
		board->x = WIN_STATES[i];
		display_board(board);
		board->x = 0;
		board->o = WIN_STATES[i];
		display_board(board);
		board->o = 0;
	}

	/* Valid */
	board->x = 0;
	board->o = 84;
	display_board(board);
	for (i = 0; i < AREA; i++) {
		if (valid_move(board, i)) {
			fprintf(stdout, "Move %u is valid\n", i);
		}
	}

	/* Make */
	board->x = 0;
	board->o = 0;
	display_board(board);
	make_move(board, 0);
	board->turn ^= 1;
	display_board(board);
	make_move(board, 1);
	board->turn ^= 1;
	display_board(board);
	make_move(board, 2);
	board->turn ^= 1;
	display_board(board);
	make_move(board, 3);
	board->turn ^= 1;
	display_board(board);
	make_move(board, 4);
	board->turn ^= 1;
	display_board(board);
	make_move(board, 5);
	board->turn ^= 1;
	display_board(board);
	make_move(board, 6);
	board->turn ^= 1;
	display_board(board);
	make_move(board, 7);
	board->turn ^= 1;
	display_board(board);
	make_move(board, 8);
	board->turn ^= 1;
	display_board(board);
	
	free(board);
}


int score(Board *board, const int turn) {
	/* if x is winner  */
	return 100;
}


int minimax(Board *board) {
	/* Returnt the best move */
	return 1;
}


int main(int argc, char **argv) {
	unsigned int move;
	int ctr;
	Board *board;

	(void) argc;
	(void) argv;

	move = 10;
	ctr = 0;

	board = new_board();
	display_board(board);
	while (!game_over(board) && ctr < AREA) {
		move = read_move(board);
		make_move(board, move);
		board->history[ctr++] = move;
		board->turn ^= 1;
		display_board(board);
		if (is_winner(board->o)) {
			fprintf(stdout, "O is the winner. X is garbage.\n");
			break;
		}
		if (is_winner(board->x)) {
			fprintf(stdout, "X is the winner. O is garbage.\n");
			break;
		}
	}
	printf("Moves Played:\n");
	for (ctr = 0; ctr < AREA; ctr++) {
		printf("%d\n", board->history[ctr]+1);
	}
	return 0;
}
