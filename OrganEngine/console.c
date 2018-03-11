#include "p_def.h"

int Con_CreateConsole(void)
{
	int success = 0;
	success = AllocConsole();

	conIn = GetStdHandle(STD_INPUT_HANDLE);
	conOut = GetStdHandle(STD_OUTPUT_HANDLE);
	conErr = GetStdHandle(STD_ERROR_HANDLE);

	//p_string_t conString = {"Console Initialized!", P_Length("Console Initialized!")};

	if (success) {
		Con_WriteConsole("Console Initialized!");
		//Con_PWriteConsole(&conString);
	}

	Con_ReadConsole();

	return success;
}

void Con_WriteConsole(const char * s)
{
	WriteConsole(conOut, s, P_Length(s), NULL, NULL);
	WriteConsole(conOut, "\n", 1, NULL, NULL);
}

void Con_PWriteConsole(p_string_t * s)
{
	WriteConsole(conOut, s->c, s->length, NULL, NULL);
	WriteConsole(conOut, "\n", 1, NULL, NULL);
}

int Con_Shutdown(void)
{
	return FreeConsole();
}

//Needs multithreading for this to work
const char * Con_ReadConsole(void)
{
	return NULL;
}
