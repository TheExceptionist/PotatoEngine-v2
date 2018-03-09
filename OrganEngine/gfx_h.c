//=================================================================================
//gfx_h.c - high-level graphics implementation
//
//
//Author: Kenny Stepney
//=================================================================================


#include "p_def.h"
#include "p_win.h"

//Store info of the bitmap to be drawn to the screen buffer
BITMAPINFO BitMapInfo = { 0 };

//Cleanup and Shutdown teh graphics system
void GFX_Shutdown(void)
{
	free(dblBuffer);
	dblBuffer = NULL;
}

//Draw to the window buffer (on not being displayed)
void GFX_Update(void)
{
	int32 *bufferIterator = (int32*)dblBuffer;

	if (!bufferIterator) return;


	GFX_DrawFloor(bufferIterator, DARK_GREY);
	GFX_DrawCeil(bufferIterator, DARK_BLUE);
	GFX_DrawWalls(bufferIterator);
	GFX_DrawHUD(bufferIterator);
	//Get the device context of the draw space only
	HDC dc = GetDC(hwndMainWindow);

	//Push the back buffer into the window buffer
	StretchDIBits(
		dc,
		0,
		0,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		0,
		0,
		BUFFER_WIDTH,
		BUFFER_HEIGHT,
		dblBuffer,
		(BITMAPINFO*)&BitMapInfo,
		DIB_RGB_COLORS,
		SRCCOPY
	);

	ReleaseDC(hwndMainWindow, dc);
}

//Initialize the double buffer
void GFX_InitBuffer(void)
{
	//define bitmap info
	BitMapInfo.bmiHeader.biSize = sizeof(BitMapInfo.bmiHeader);
	BitMapInfo.bmiHeader.biWidth = BUFFER_WIDTH;
	//put (0,0) at the top
	BitMapInfo.bmiHeader.biHeight = -BUFFER_HEIGHT;
	BitMapInfo.bmiHeader.biPlanes = 1;
	BitMapInfo.bmiHeader.biBitCount = 8 * BYTES_PER_PIXEL;
	BitMapInfo.bmiHeader.biCompression = BI_RGB;

	//WIDTH * HEIGHT * numPixels
	dblBuffer = malloc(BUFFER_WIDTH * BUFFER_HEIGHT * BYTES_PER_PIXEL);
}

//Initialize the graphics sysytems
void GFX_Init(void)
{
	GFX_InitBuffer();
	GFX_InitColors();
}
