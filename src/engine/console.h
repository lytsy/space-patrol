#include "config.h"
void _hide_win32_console();

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
void _hide_win32_console()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}
#endif

void hide_console()
{
#if (defined(_WIN32) || defined(WIN32)) && !DEVELOPMENT_MODE
    _hide_win32_console();
#endif
}