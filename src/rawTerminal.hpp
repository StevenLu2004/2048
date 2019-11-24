#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void die(const char *s)
{
    perror(s);
    exit(1);
}

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

void testRead()
{
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
        die("read");
}

bool mygetch(char &c)
{
    c = '\0';
    long ret = read(STDIN_FILENO, &c, 1);
    if (ret == -1 && errno != EAGAIN)
        die("read");
    return ret && ret != -1;
}

long getCmd(char *cmd)
{
    char *c;
    *(c = cmd) = '\0';
    while (mygetch(*c))
        *(++c) = '\0';
    return strlen(cmd);
}

int rawTermTest()
{
    enableRawMode();

    while (1)
    {
        char c = '\0';
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
            die("read");
        if (iscntrl(c))
        {
            printf("%d\r\n", c);
        }
        else
        {
            printf("%d ('%c')\r\n", c, c);
        }
        if (c == 'q')
            break;
    }

    return 0;
}

void rawTermTest2(char *cmd)
{
    char *c;
    while (true)
    {
        *(c = cmd) = '\0';

        while (mygetch(*c))
            *(++c) = '\0';
        for (int i = 0; i < strlen(cmd); ++i)
            printf("%d ", cmd[i]);
        strlen(cmd) && printf("\r\n");
        if (cmd[0] == 'q')
            return;
    }
}
