#include "config.h"

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

void hide_console()
{
#if (defined(_WIN32) || defined(WIN32)) && !DEVELOPMENT_MODE
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
#endif
}