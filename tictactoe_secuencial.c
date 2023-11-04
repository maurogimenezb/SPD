#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 9
#define EMPTY '-'

char board[BOARD_SIZE];
char currentPlayer = 'X';
int gameOver = 0;
int movesX = 0; // Número de movimientos de X
int movesO = 0; // Número de movimientos de O

// Función para imprimir el tablero
void printBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%c ", board[i]);
        if ((i + 1) % 3 == 0) {
            printf("\n");
        }
    }
}

// Función para verificar si hay un ganador
int checkWinner(char player) {
    // Verificar filas
    if ((board[0] == player && board[1] == player && board[2] == player) ||
        (board[3] == player && board[4] == player && board[5] == player) ||
        (board[6] == player && board[7] == player && board[8] == player)) {
        return 1;
    }
    // Verificar columnas
    if ((board[0] == player && board[3] == player && board[6] == player) ||
        (board[1] == player && board[4] == player && board[7] == player) ||
        (board[2] == player && board[5] == player && board[8] == player)) {
        return 1;
    }
    // Verificar diagonales
    if ((board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player)) {
        return 1;
    }
    return 0;
}

// Función para verificar si hay un empate
int checkTie() {
    if (movesX + movesO == BOARD_SIZE) {
        return 1; // Todas las celdas están ocupadas, hay un empate.
    }
    return 0;
}

// Función para realizar un movimiento
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

    start_time = clock(); // Iniciar el reloj

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

    end_time = clock(); // Detener el reloj
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Tiempo de ejecucion: %f segundos\n", execution_time);
}

int main() {
    playGame();
    return 0;
}
