#include "InterfaceManager.h"

#include <stdio.h>

void StartInterface()
{
	int move = 0;
	int from = A2; int to = H7;
	int cap = wR; int prom = bK;

	move = ((from)|(to<<7)|(cap<<14)|(prom<<20));

	printf("Algebraic from: %s \n", PrintSquare(from));
	printf("Algebraic to: %s \n", PrintSquare(to));
	printf("Algebraic from: %s \n", PrintMove(move));

}
