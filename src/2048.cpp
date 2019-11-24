#include "2048rand.hpp"
#include "2048render.hpp"
#include "2048push.hpp"
#include "altScreen.hpp"
#include "rawTerminal.hpp"

const int N = 4;

int board[N][N];

char cmd[40];
// char cm;
unsigned long inputClock;

int score;

void newGame()
{
    srand(time(0));
    score = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            board[i][j] = 0;
    Rand::generate(board);
    Rand::generate(board);
}

void draw()
{
    AltSc::enter();
    printf("Score: %d\r\n", score);
    printf("\r\n");
    Render::render(board);
}

int main(int argc, char const *argv[])
{
    enableRawMode();
    // rawTermTest2(cmd);
    newGame();
    draw();
    while (true)
    {
        bool updated = false;
        // scanf("%s", cmd);
        int cmdlen = getCmd(cmd), dscore = 0;
        bool moved;
        if (!strcmp(cmd, "q") || !strcmp(cmd, "\033"))
        {
            AltSc::exit();
            printf("User quitted the program.\r\n");
            break;
        }
        if (!strcmp(cmd, "w") || !strcmp(cmd, "\033[A"))
        {
            moved = Push::upable(board);
            dscore = Push::pushUp(board);
            updated = true;
        }
        if (!strcmp(cmd, "s") || !strcmp(cmd, "\033[B"))
        {
            moved = Push::downable(board);
            dscore = Push::pushDown(board);
            updated = true;
        }
        if (!strcmp(cmd, "a") || !strcmp(cmd, "\033[D"))
        {
            moved = Push::leftable(board);
            dscore = Push::pushLeft(board);
            updated = true;
        }
        if (!strcmp(cmd, "d") || !strcmp(cmd, "\033[C"))
        {
            moved = Push::rightable(board);
            dscore = Push::pushRight(board);
            updated = true;
        }
        if (updated)
        {
            moved &&Rand::generate(board);
            score += dscore;
            AltSc::exit();
            draw();
            if (!Push::pushable(board))
            {
                printf("Game over.\r\n");
                break;
            }
            // printf("final\n");
            // Push::print(board);
        }
    }
    AltSc::exit();
    disableRawMode();
    return 0;
}
