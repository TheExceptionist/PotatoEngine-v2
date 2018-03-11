#ifndef HOST_H
#define HOST_H

#define moveSpeed 1
#define rotSpeed 0.05
#define mapWidth 24
#define mapHeight 24

extern uint8 worldMap[mapWidth][mapHeight];
extern uint8 visitedMap[mapWidth][mapHeight];

void Host_Init(void);
void Host_Frame(float timestep);
void Host_Shutdown(void);
void Host_Move(float x, float y);
void Host_Rot(float speed);

#endif