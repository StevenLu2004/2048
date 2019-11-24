#include <stdio.h>
#include <string.h>

namespace Render
{

const int BLOCK_WIDTH = 7, BLOCK_HEIGHT = 3;
const int N = 4;
const char COLORS[20][40] = {
    "\033[0m",
    "\033[31m",
    "\033[33m",
    "\033[32m",
    "\033[36m",
    "\033[34m",
    "\033[35m",
    "\033[31;1m",
    "\033[33;1m",
    "\033[32;1m",
    "\033[36;1m",
    "\033[34;1m",
    "\033[35;1m",
    "\033[31;1;3m",
    "\033[33;1;3m",
    "\033[32;1;3m",
    "\033[36;1;3m",
    "\033[34;1;3m",
    "\033[35;1;3m",
};
const char COLOR_RESET[40] = "\033[0m";

void border()
{
    printf("+");
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < BLOCK_WIDTH; ++j)
            printf("-");
        printf("+");
    }
}

void pad(int board[N][N], int i, int j)
{
    printf("%s", COLORS[board[i][j]]);
    for (int i = 0; i < BLOCK_WIDTH; ++i)
        printf(" ");
    printf("%s", COLOR_RESET);
}

void print(int board[N][N], int i, int j)
{
    char s[40];
    sprintf(s, "%d", 1 << board[i][j]);
    int lm = strlen(s);
    int ll = (BLOCK_WIDTH - lm) >> 1;
    int lr = BLOCK_WIDTH - ll - lm;
    printf("%s", COLORS[board[i][j]]);
    for (int i = 0; i < ll; ++i)
        printf(" ");
    printf("%s", s);
    for (int i = 0; i < lr; ++i)
        printf(" ");
    printf("%s", COLOR_RESET);
}

void render(int board[N][N])
{
    int lu = BLOCK_HEIGHT >> 1;
    int ld = BLOCK_HEIGHT - lu - 1;
    border();
    printf("\r\n");
    for (int i = 0; i < N; ++i)
    {
        for (int k = 0; k < lu; ++k)
        {
            printf("|");
            for (int j = 0; j < N; ++j)
            {
                pad(board, i, j);
                printf("|");
            }
            printf("\r\n");
        }
        printf("|");
        for (int j = 0; j < N; ++j)
        {
            board[i][j] ? print(board, i, j) : pad(board, i, j);
            printf("|");
        }
        printf("\r\n");
        for (int k = 0; k < ld; ++k)
        {
            printf("|");
            for (int j = 0; j < N; ++j)
            {
                pad(board, i, j);
                printf("|");
            }
            printf("\r\n");
        }
        border();
        printf("\r\n");
    }
}

} // namespace Render
