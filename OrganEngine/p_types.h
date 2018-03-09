#ifndef POTATO_TYPES_H
#define POTATO_TYPES_H

#include<stdint.h>

#define OBJ_COLLECT 0x01
#define OBJ_SHOW    0x02

typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
//natural number
typedef uint32_t nat;


//3D Vector type, currently only the x and y components 
typedef struct vector3D vec3;

struct vector3D 
{
	float x;
	float y;
	float z;
};

typedef struct player_s player_t;

struct player_s 
{
	//Position, Direction, and the Camera Plane of the player
	vec3 pos;
	vec3 plane;
	vec3 dir;

	//Height of the player, currently unused
	int32 height;
	//Player's score
	int32 score;
	//Angle of the player view, currently unused
	float angle;
};

//Struct to define objects in the game
typedef struct object_s object_t;

struct object_s
{
	//Define flags for the struct
	int32 attrib;
	//The position of the object on the map
	vec3 pos;
	//Points to the next object struct
	object_t* next;
};

#endif