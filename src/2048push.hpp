#include <stdio.h>
#include <string.h>

namespace Push
{

const int N = 4;

int b2[N][N];

void print(int board[N][N])
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
            printf("%d ", board[i][j]);
        printf("\r\n");
    }
    printf("\r\n");
}

inline int nextK(int board[N][N], int i, int k)
{
    for (k = k + 1; k < N && !board[i][k]; ++k)
        ;
    return k;
}

int m_push(int board[N][N])
{
    // printf("push\r\n");
    int nk, pk, l, tmp, dscore = 0;
    for (int i = 0; i < N; ++i)
    {
        pk = nextK(board, i, -1);
        nk = nextK(board, i, pk);
        l = 0;
        while (pk < N)
        {
            // printf("i=%d pk=%d nk=%d l=%d\r\n", i, pk, nk, l);
            if (nk < N && board[i][pk] == board[i][nk])
            {
                tmp = board[i][pk] + 1;
                board[i][pk] = board[i][nk] = 0;
                board[i][l++] = tmp;
                pk = nextK(board, i, nk);
                nk = nextK(board, i, pk);
                // print(board);
                dscore += 1 << tmp; // Update score
            }
            else
            {
                tmp = board[i][pk];
                board[i][pk] = 0;
                board[i][l++] = tmp;
                pk = nk;
                nk = nextK(board, i, pk);
                // print(board);
            }
        }
    }
    // print(board);
    return dscore;
}

void changeAxis(int board[N][N])
{
    int tmp;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < i; ++j)
            tmp = board[i][j], board[i][j] = board[j][i], board[j][i] = tmp;
    // print(board);
}

void changeFace(int board[N][N])
{
    int tmp;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < (N >> 1); ++j)
            tmp = board[i][j], board[i][j] = board[i][N - j - 1], board[i][N - j - 1] = tmp;
    // print(board);
}

int pushLeft(int board[N][N])
{
    // printf("left\r\n");
    int d = m_push(board);
    return d;
}

int pushRight(int board[N][N])
{
    // printf("right\r\n");
    changeFace(board);
    int d = m_push(board);
    changeFace(board);
    return d;
}

int pushUp(int board[N][N])
{
    // printf("up\r\n");
    changeAxis(board);
    int d = m_push(board);
    changeAxis(board);
    return d;
}

int pushDown(int board[N][N])
{
    // printf("down\r\n");
    changeAxis(board);
    changeFace(board);
    int d = m_push(board);
    changeFace(board);
    changeAxis(board);
    return d;
}

bool same(int b1[N][N], int b2[N][N])
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (b1[i][j] != b2[i][j])
                return false;
    return true;
}

bool leftable(int b1[N][N])
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            b2[i][j] = b1[i][j];
    pushLeft(b2);
    if (!same(b1, b2))
        return true;
    return false;
}
bool rightable(int b1[N][N])
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            b2[i][j] = b1[i][j];
    pushRight(b2);
    if (!same(b1, b2))
        return true;
    return false;
}
bool upable(int b1[N][N])
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            b2[i][j] = b1[i][j];
    pushUp(b2);
    if (!same(b1, b2))
        return true;
    return false;
}
bool downable(int b1[N][N])
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            b2[i][j] = b1[i][j];
    pushDown(b2);
    if (!same(b1, b2))
        return true;
    return false;
}

bool pushable(int b1[N][N])
{
    return leftable(b1) || rightable(b1) || upable(b1) || downable(b1);
}

} // namespace Push
