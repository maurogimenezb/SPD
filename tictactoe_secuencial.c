#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BOARD_SIZE 9
#define EMPTY '-'

char board[BOARD_SIZE];
char currentPlayer = 'X';
int gameOver = 0;
int movesX = 0; 
int movesO = 0; 

void printBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%c ", board[i]);
        if ((i + 1) % 3 == 0) {
            printf("\n");
        }
    }
}

int checkWinner(char player) {
    if ((board[0] == player && board[1] == player && board[2] == player) ||
        (board[3] == player && board[4] == player && board[5] == player) ||
        (board[6] == player && board[7] == player && board[8] == player)) {
        return 1;
    }
    if ((board[0] == player && board[3] == player && board[6] == player) ||
        (board[1] == player && board[4] == player && board[7] == player) ||
        (board[2] == player && board[5] == player && board[8] == player)) {
        return 1;
    }
    if ((board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player)) {
        return 1;
    }
    return 0;
}

int checkTie() {
    if (movesX + movesO == BOARD_SIZE) {
        return 1; 
    }
    return 0;
}

void makeMove(char player) {
    int i = rand() % BOARD_SIZE;
    while (board[i] != EMPTY) {
        i = rand() % BOARD_SIZE;
    }
    board[i] = player;

    if (player == 'X') {
        movesX++;
    } else {
        movesO++;
    }
}

void playGame() {
    clock_t start_time, end_time;
    double execution_time;

    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = EMPTY;
    }
    srand(time(NULL));
    start_time = clock(); 
    while (!gameOver) {
        makeMove(currentPlayer);

        if (checkWinner(currentPlayer)) {
            if (currentPlayer == 'X') {
                printf("Jugador 1 (X) gana.\n");
            } else {
                printf("Jugador 2 (O) gana.\n");
            }
            printBoard();
            gameOver = 1;
        } else if (checkTie()) {
            printf("Empate. No hay ganador.\n");
            printBoard();
            gameOver = 1;
        }
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    end_time = clock(); 
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion: %f segundos\n", execution_time);
}

int main() {
    playGame();
    return 0;
}
