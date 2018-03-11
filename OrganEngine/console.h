#ifndef CONSOLE_H
#define CONSOLE_H

#include "p_win.h"

#define MAX_CHARS 100

HANDLE conIn;
HANDLE conOut;
HANDLE conErr;

int Con_CreateConsole(void);

void Con_WriteConsole(const char* s);
void Con_PWriteConsole(p_string_t* s);
int Con_Shutdown(void);

const char* Con_ReadConsole();

#endif