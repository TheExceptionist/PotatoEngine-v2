//=================================================================================
//gfx_l.c - low-level graphics implementation
//
//
//Author: Kenny Stepney
//=================================================================================


#include "p_def.h"

//Array of O_color structs that contain all preset colors created by InitColors
O_color o_colors[TOTAL_COLORS];

//Draw the bottom of the screen with a certain color of pixels
/**
	buffer - the memory to write the rgb data to
	type - enum color type
**/
void GFX_DrawFloor(int32* buffer, int32 type)
{
	O_color color = o_colors[type];
	//Cache width first height second
	for (int height = 0; height < BUFFER_HEIGHT/2; height++)
	{
		for (int width = 0; width < BUFFER_WIDTH; width++)
		{
			*buffer++ = (color.r << 16) | (color.g << 8) | (color.b);
		}
	}
}

//Draw the top of the screen with a certain color of pixels
/**
buffer - the memory to write the rgb data to
type - enum color type
**/
void GFX_DrawCeil(int32* buffer, int32 type)
{
	O_color color = o_colors[type];

	int32 start = ( 5 * BUFFER_HEIGHT / 8);
	buffer += (start * BUFFER_HEIGHT) + BUFFER_WIDTH;

	for (int32 height = start; height < start + BUFFER_HEIGHT/2; height++)
	{
		for (int32 width = 0; width < BUFFER_WIDTH; width++)
		{
			*buffer++ = (color.r << 16) | (color.g << 8) | (color.b);
		}
	}
}

void GFX_drawColumn(int32* dblBuffer, int32 x, int32 startY, int32 endY, O_color* color)
{
	int32* iter = dblBuffer;

	iter += (BUFFER_WIDTH * startY) + x;

	for (int y = startY; y < endY; y++) {
		*iter = (color->r << 16) | (color->g << 8) | color->b;
		iter += BUFFER_WIDTH;
	}
}

void GFX_DrawHUD(int32 * buffer)
{
	O_color hudColor = {255, 255, 255};
	O_color textColor = { 0, 0, 0 };

	for (int i = 0; i < BUFFER_WIDTH; i++)
	{
		GFX_drawColumn(buffer, i, BUFFER_HEIGHT - 50, BUFFER_HEIGHT, &hudColor);
	}

	for (int i = 0; i < GPlayer->score; i++)
	{
		GFX_drawColumn(buffer, i * 5, BUFFER_HEIGHT - 40, BUFFER_HEIGHT - 20, &textColor);
		GFX_drawColumn(buffer, (i * 5) + 1, BUFFER_HEIGHT - 40, BUFFER_HEIGHT - 20, &textColor);
		GFX_drawColumn(buffer, (i * 5) + 2, BUFFER_HEIGHT - 40, BUFFER_HEIGHT - 20, &textColor);
	}
}

//GFX_DrawWalls
//Cast rays to detect the walls in the map
/**
	int32 buffer - buffer to the pixel data (the one currently not being displayed)
**/
void GFX_DrawWalls(int32 * buffer)
{
	Cam_CastRays(buffer);
}

//Init the array of O_colors
void GFX_InitColors(void)
{
	o_colors[RED].r = 255;
	o_colors[RED].g = 0;
	o_colors[RED].b = 0;

	o_colors[GREEN].r = 0;
	o_colors[GREEN].g = 255;
	o_colors[GREEN].b = 0;

	o_colors[BLUE].r = 0;
	o_colors[BLUE].g = 0;
	o_colors[BLUE].b = 255;

	o_colors[DARK_BLUE].r = 25;
	o_colors[DARK_BLUE].g = 25;
	o_colors[DARK_BLUE].b = 112;

	o_colors[DARK_GREY].r = 79;
	o_colors[DARK_GREY].g = 79;
	o_colors[DARK_GREY].b = 79;
}
