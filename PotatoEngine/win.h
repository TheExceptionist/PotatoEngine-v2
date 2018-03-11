#ifndef WIN_H
#define WIN_H

//Implement windows related code

#define BYTES_PER_PIXEL 4

void Win_Init(void);

static const char* TITLE_NAME = "PotatoEngine32.exe";
static const char* CLASS_NAME = "PotatoEngine";

static int WINDOW_WIDTH = 640;
static int WINDOW_HEIGHT = 480;
static int BUFFER_WIDTH = 640;
static int BUFFER_HEIGHT = 480;
static void* dblBuffer;

#endif
