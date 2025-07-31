#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define P_SIZE 3
#define WIN_POINTS 21
#define BALL_SIZE 1

void CleanScreen() { printf("\033[2J\033[H"); }
unsigned int xorshift32(unsigned int state) {
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

int rand_xorshift(unsigned int state) {
    return (state & 1) ? 1 : -1;  // -1 или 1
}
char input() {
    char c;

    do {
        c = getchar();
        while (getchar() != '\n');
    } while (!(c == 'a' || c == 'z' || c == 'k' || c == 'm' || c == ' '));

    return c;
}
void Drawbraket(int ball_x, int ball_y, int player1_y, int player2_y, int score1, int score2) {
    CleanScreen();
    printf("Player 1: %d | Player 2: %d\n", score2, score1);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1) {
                printf("-");
            } else if (j == 2 && i >= player1_y && i < player1_y + P_SIZE) {
                printf("|");
            } else if (j == WIDTH - 3 && i >= player2_y && i < player2_y + P_SIZE) {
                printf("|");
            } else if (j == ball_x && i == ball_y) {
                printf("o");
            } else if (j == 0 || j == WIDTH - 1) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main() {
    int flag = 3;
    int paddleLeft = HEIGHT / 2 - P_SIZE / 2;
    int paddleRight = HEIGHT / 2 - P_SIZE / 2;
    int ball_x = WIDTH / 2;
    int ball_y = HEIGHT / 2;
    int ball_dx = 1;
    int ball_dy = 1;
    int Score1 = 0;
    int Score2 = 0;
    unsigned int state = 42;
    state = xorshift32(state);
    ball_dx = 1;
    ball_dy = 1;
    while ((Score1 < 21) && (Score2 < 21)) {
        Drawbraket(ball_x, ball_y, paddleLeft, paddleRight, Score1, Score2);
        if (ball_x <= 1) {
            Score1++;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            ball_dx = rand_xorshift(state);
            ball_dy = rand_xorshift(state);
        }
        if (ball_x >= WIDTH - 1) {
            Score2++;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            ball_dx = rand_xorshift(state);
            ball_dy = rand_xorshift(state);
        }
        if (flag == 1)
            ball_dy *= -1;
        else if (flag == 0)
            ball_dy *= 1;
        ball_x += ball_dx;
        ball_y += ball_dy;
        if (ball_y <= 0 || ball_y > HEIGHT - 1) {  // Wall
            ball_dy *= -1;
        }
        if (ball_x == 3 && ball_y >= paddleLeft && ball_y < paddleLeft + P_SIZE) {
            ball_dx = 1;  // Angle
        }
        if (ball_x >= WIDTH - 3 && ball_y >= paddleRight && ball_y < paddleRight + P_SIZE) {
            ball_dx = -1;  // Angle
        }
        switch (getchar()) {
            case 'a':
                if (paddleLeft > 1) paddleLeft = paddleLeft - 2;
                break;
            case 'z':
                if (paddleLeft < HEIGHT - P_SIZE) paddleLeft = paddleLeft + 2;
                break;
            case 'k':
                if (paddleRight > 1) paddleRight = paddleRight - 2;
                break;
            case 'm':
                if (paddleRight < HEIGHT - P_SIZE) paddleRight = paddleRight + 2;
                break;
        }
    }
    if (Score1 > Score2) {
        printf("Player two win!");
    } else
        printf("Player one win!");
}
