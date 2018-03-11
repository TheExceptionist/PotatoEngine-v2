#ifndef MATH_H
#define MATH_H

#include <stdint.h>
#include <math.h>

#define PI 3.141592

void Mth_Normalize(vec3* vector);
void Mth_Scale(vec3* vector1, float scale);
void Mth_Mult(vec3* vector1, vec3* vector2);
void  Mth_Move(vec3* vector, int32 velX, int32 velY, int32 velZ);

int Mth_Modulo(int32 operand1, int32 operand2);

inline float   Mth_AngleToRads(float angle);
inline float Mth_Magnitude(vec3* vector);

float Mth_Sqrt(float num);
float Mth_Abs(float num);



#endif
