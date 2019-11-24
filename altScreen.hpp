#include <stdio.h>

namespace AltSc
{

void enter()
{
    printf("\033[?1049h");
}

void exit()
{
    printf("\033[?1049l");
}

} // namespace AltSc
