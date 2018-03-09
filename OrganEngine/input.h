#ifndef INPUT_H
#define INPUT_H

enum keys
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NUM_KEYS
};


extern uint8 keys[NUM_KEYS];

void Inp_HandleKeys(void);

#endif