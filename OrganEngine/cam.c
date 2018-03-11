//=================================================================================
//cam.c - displays the viewpoint of the player
//
//Author: Kenny Stepney
//=================================================================================

#include <math.h>

#include "p_def.h"

//Clear the visited array, currentl unused
void Cam_ClearVisited(void)
{
	for (int x = 0; x < mapWidth; x++)
	{
		for (int y = 0; y < mapHeight; y++)
		{
			visitedMap[x][y] = 0;
		}
	}
}

//Casts Rays and draw columns to the screen based on what the rays hit
void Cam_CastRays(int32* dblBuffer)
{
	vec3 rayDir = {0};
	for (int x = 0; x < BUFFER_WIDTH; x++)
	{
		//camera value ranges from -1 to 1, used to determine the ray direction
		//base off of the player direction, the camera plane and the x
		//position the loop is currently at
		double camera = 2 * x / (double)(BUFFER_WIDTH) - 1;

		//plane determines FOV
		rayDir.x = GPlayer->dir.x + GPlayer->plane.x * camera;
		rayDir.y = GPlayer->dir.y + GPlayer->plane.y * camera;

		//Get the map position that the ray will originate from
		int mapX = (int)GPlayer->pos.x;
		int mapY = (int)GPlayer->pos.y;

		//Declare side distance and change in side distance variables
		double sideDistX, sideDistY;
		double deltaDistX = Mth_Sqrt((1 + (rayDir.y*rayDir.y) / (rayDir.x*rayDir.x)));
		double deltaDistY = Mth_Sqrt((1 + (rayDir.x*rayDir.x) / (rayDir.y*rayDir.y)));

		//declare more variables
		double wallDist;

		int stepX, stepY;
		int side = NS;

		uint8 hitWall = 0;
		O_color color = {0};

		//Check if the rayDvoid GFX_drawColumn(int32_t* dblBuffer, int x, int startY, int endY, O_color* color)
		//if rayDir.x is negative or not
		if (rayDir.x < 0)
		{
			stepX = -1;
			sideDistX = (GPlayer->pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - GPlayer->pos.x) * deltaDistX;
		}

		if (rayDir.y < 0)
		{
			stepY = -1;
			sideDistY = (GPlayer->pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - GPlayer->pos.y) * deltaDistY;
		}

		//Keep incrementing the ray until it hits a wall
		while (!hitWall)
		{
			visitedMap[mapX][mapY] = 1;
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = NS;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = EW;
			}
			if (worldMap[mapX][mapY] > 0) hitWall = 1;
		}

		//Set a draw color based on what the ray hit
		switch (worldMap[mapX][mapY])
		{
		case 1: color.r = 255; break;
		case 2: color.g = 255; break;
		case 5: color.g = 125; color.b = 125; color.r = 125; break;
		default: color.b = 255; break;
		}

		//give side depth by changing it's hsading
		if (side == 1)
		{
			color.r = color.r / 2;
			color.g = color.g / 2;
			color.b = color.b / 2;
		}

		//Compute wall distance based on the side of the wall hit
		if (!side)
			wallDist = Mth_Abs((mapX - GPlayer->pos.x + (1 - stepX)/2) / rayDir.x);
		else
			wallDist = Mth_Abs((mapY - GPlayer->pos.y + (1 - stepY)/2) / rayDir.y);//Mth_Abs((mapY - GPlayer->pos.y + (1 - stepY)) / (float) rayDir.y);

		int height;
		//Compute the height, used by the drawStart and drawEnd variables
		if(wallDist > 0) height = Mth_Abs((int)(BUFFER_HEIGHT / wallDist));
		else height = BUFFER_HEIGHT;

		//drawStart and drawEnd determine the length of the column to be drawn onto the screen
		int drawStart = -height / 2 + BUFFER_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;

		int drawEnd = height / 2 + BUFFER_HEIGHT / 2;
		if (drawEnd >= BUFFER_HEIGHT)
			drawEnd = BUFFER_HEIGHT - 1;

		//Draw the column to the buffer
		GFX_drawColumn(dblBuffer, x, drawStart, drawEnd, &color);
	}
}
