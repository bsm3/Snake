/* 
* By: (bsm) Beysim Mustafov
*	
* Linux: 
* Tested under Fedora
*
* Keys to steer the snake:
*      		 up = 🡅
*		
*	left = 🡄       right = 🡆
*
*		 down = 🡇
*	
*	exit = 'e'
*/

#include <stdio.h>
#include <stdlib.h>
#include "snake.h"

char arr[22][68] = {{0}}, ch, cpy;
int tailx[40], taily[40];
int a, b, c = 0, d = 0, e = 1, count = 0, n = 22, k = 68, speed, x = 20, y = 10, obstx[] = {10, 40, 4, 24, 50}, obsty[] = {4, 7, 11, 16, 17};

int main(void)
{
	system("clear");

	do
	{
		printf("Select The game speed between 1 and 3: ");
		scanf("%d", &speed);
	}while(speed > 3 || speed < 1);
	 speed *= 100000;

	printf("\033[2J");
	system("clear");
	printf("\e[?25l");
	border(0, k-1, n-1, 1);
	food();

	do
	{
		keys(&x, &y);
		_print();
		head(x, y);
		gotoxy(a, b);
		printf("*");
		obstacles();
		
		if(y > n-2)
			y = 3;
		if(y < 3)
			y = n-2;
		if(x > k-2)
			x = 2;
		if(x < 2)
			x = k-2;

		tail(x, y);

		tailx[0] = x;
		taily[0] = y;

		if(a == x && b == y)
		{
			food();
			count++;
		}
		
		gotoxy(2, 2);
		printf("[* : %d]", count);
		eat(x, y, count);
		system("clear");

	}while(e != 0 && e != 2);
	e_exit();
	printf("\e[?25h");
	gotoxy(29, 10);
	if(e == 0)
		printf("Game Over");
	_print();
	
	return 0;
}
