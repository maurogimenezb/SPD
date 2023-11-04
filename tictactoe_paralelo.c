#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#define BOARD_SIZE 9
#define EMPTY '-' 

char board[BOARD_SIZE];
char currentPlayer = 'X';
int gameOver = 0;
int movesX = 0; 
int movesO = 0; 

void initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = EMPTY;
    }
}

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
        (board[6] == player && board[7] == player && board[8] == player) ||
        (board[0] == player && board[3] == player && board[6] == player) ||
        (board[1] == player && board[4] == player && board[7] == player) ||
        (board[2] == player && board[5] == player && board[8] == player) ||
        (board[0] == player && board[4] == player && board[8] == player) ||
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

void playGame(char player) {
    while (!gameOver) {
        if (currentPlayer == player) {
            int i = rand() % BOARD_SIZE;
            if (board[i] == EMPTY) {
                #pragma omp critical
                {
                    board[i] = player;
                    if (player == 'X') {
                        movesX++;
                    } else {
                        movesO++;
                    }
                }
                if (checkWinner(player)) {
                    #pragma omp critical
                    {
                        printf("Jugador %c gana.\n", player);
                        printBoard();
                        gameOver = 1;
                    }
                } else if (checkTie()) {
                    #pragma omp critical
                    {
                        printf("Empate. No hay ganador.\n");
                        printBoard();
                        gameOver = 1;
                    }
                }
                currentPlayer = (player == 'X') ? 'O' : 'X';
            }
        }
    }
}

int main() {
    double start_time, end_time, execution_time;
    initializeBoard();
    srand(time(NULL));
    start_time = omp_get_wtime();
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            playGame('X');
        }
        #pragma omp section
        {
            playGame('O');
        }
    }
    end_time = omp_get_wtime();
    execution_time = end_time - start_time;
    printf("Tiempo de ejecucion: %f segundos\n", execution_time);
    return 0;
}
