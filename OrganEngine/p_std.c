#include "p_std.h"

int P_Length(const char * c)
{
	int count = 0;

	while (*c)
	{
		count++;
		c++;
	}
	return count;
}

const char * P_LenString(const char * c)
{
	return P_ToString(P_Length(c));
}

const char * P_ToString(int32 num)
{
	char* c[MAX_DIGITS];

	sprintf(c, "%d", num);

	return c;
}
