#include <stdlib.h>
#include <time.h>

namespace Rand
{

const double chanceOf4 = .1;
const int N = 4;

double frand()
{
    return (double)rand() / RAND_MAX;
}

int getRandomNewNumber()
{
    if (rand() < chanceOf4)
        return 2; // 2^2 == 4
    return 1;     // 2^1 == 2
}

bool getRandomPosition(int board[N][N], int &x, int &y)
{
    int totalEmpty = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (!board[i][j])
                ++totalEmpty;
    int pos = frand() * totalEmpty;
    // printf("totalEmpty=%d pos=%d\n", totalEmpty, pos);
    for (x = 0; x < N; ++x)
        for (y = 0; y < N; ++y)
            if (!board[x][y])
            {
                if (pos)
                    --pos;
                else
                    return true;
            }
    return false;
}

bool generate(int board[N][N])
{
    int x, y;
    if (!getRandomPosition(board, x, y))
        return false;
    // printf("x=%d y=%d\n", x, y);
    board[x][y] = getRandomNewNumber();
    return true;
}

} // namespace Rand
