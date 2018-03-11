//=================================================================================
//p_math.c - custom math operations using c
//
//
//
//Author: Kenny Stepney
//=================================================================================


#include "p_def.h"


//Takes a ptr to a vector and normalizes it
/*
	vec3* vector - vector to normalize
*/
void Mth_Normalize(vec3 * vector)
{
	float unitMagnitude = 1.0 / Mth_Magnitude(vector);
	Mth_Scale(vector, unitMagnitude);
}


//Takes a ptr to a vector and scales it
/*
	vec3* vector - vector to scale
	float scale - number to scale it by
*/
void Mth_Scale(vec3 * vector, float scale)
{
	vector->x *= scale;
	vector->y *= scale;
	vector->z *= scale;
}

//Multiplies two vector otgether by their components
/*
	vec3 dest - the destination vector to store the vector multiplication
	vec3 dest - the src vector to multiplied the dest vector by
*/
void Mth_Mult(vec3 * dest, vec3* src)
{
	dest->x *= src->x;
	dest->y *= src->y;
	dest->z *= src->z;
}

//Add the to the vectors components directly
/*
	vec3* vector - the vector to add it's componnets to 
	int32 velX - the operand to add the vector's x coord by
	int32 velY - the operand to add the vector's y coord by
	int32 velZ - the operand to add the vector's z coord by
*/
void Mth_Move(vec3* vector, int32 velX, int32 velY, int32 velZ)
{
	vector->x += velX;
	vector->y += velY;
	vector->z += velZ;
}

//Custom modulo operation, since th ec library's version techincal isn't modulo
/*
	int32 operand1 - operand to (operand1) mod (operand2)
	int32 operand2 - operand to (operand1) mod (operand2)
*/
inline int Mth_Modulo(int32 operand1, int32 operand2)
{
	int m = (operand1 % operand2);
	return m < 0 ? (m + operand2) : m;
}

//Convert Degress to Radians
/*
	float angle - the angle to convert to rads
*/
inline float Mth_AngleToRads(float angle)
{
	return angle * (float)(PI / 180);
}

//Compute the magnitude of a vector
/*
	vec* vector - vector to compute the magnitude of
*/
inline float Mth_Magnitude(vec3* vector)
{
	return sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
}

//Take the srqt of a number
/*
	float num - number to take the square of
*/
float Mth_Sqrt(float num)
{
	return sqrt(num);
}

//Take the absolute value of a number
/*
	float num - number to take the absolute value of.
*/
float Mth_Abs(float num)
{
	return (num < 0 ? -num : num);
}





