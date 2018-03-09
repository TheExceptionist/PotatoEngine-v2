#ifndef CAM_H
#define CAM_H

#include <stdint.h>

#define TILE_SIZE 64
#define TILE_HEIGHT 64

#define NS 0
#define EW 1

void Cam_ClearVisited(void);
void Cam_CastRays(int32* dblBuffer);
#endif
