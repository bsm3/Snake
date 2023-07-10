#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>
#include <fcntl.h>


extern char arr[22][68], ch, cpy;
extern int tailx[560], taily[560];
extern int a, b, c, d, e, count, x, k, n, y, speed, obstx[5], obsty[5];


void gotoxy(int x, int y)
{
	printf("%c[%d;%df", 0x1B, y, x);
}


int kbhit(void)
{
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

void keys(int *x, int *y)
{
	if(kbhit())
	{
		ch = getchar();
		if(ch == '\033')
		{
			getchar();
			ch = getchar();

		    switch(ch)
		    {
				case 'A':
					c  = -1;
					d = 0;

					if(cpy == 'D' || cpy == 'C')
					{
						if(speed == 375000)
							speed -= 45000;
						else
							speed -= 50000;
					}
				break;

				case 'B':
					c = 1;
					d = 0;

					if(cpy == 'D' || cpy == 'C')
					{
						if(speed == 375000)
							speed -= 45000;
						else
							speed -= 50000;
					}
				break;

				case 'D':
					c = 0;
					d = -1;

					if(cpy != 'D' && speed < 350000)
					{
						if(speed == 330000)
							speed += 45000;
						else
							speed += 50000;
					}
				break;

				case 'C':
					c = 0;
					d = 1;
					if(cpy != 'C' && speed < 350000)
					{
						if(speed == 330000)
							speed += 45000;
						else
							speed += 50000;
					}
				break;

				default:
					ch = cpy;
				break;
			}

		}
		if(ch == 'e')
			e = 2;

		if(cpy == 'C' && ch == 'D')
			e = 0;

		else if(cpy == 'D' && ch == 'C')
			e = 0;

		else if(cpy == 'A' && ch == 'B')
			e = 0;

		else if(cpy == 'B' && ch == 'A')
			e = 0;

		cpy = ch;
	}

	*x += d;
	*y += c;
}


void border(int x, int k, int n, int val)
{
	for(int i = x; i <= n; i++)
	{
		arr[i][x] = val;
		arr[i][k] = val;
	}

	for(int i = x; i <= k; i++)
	{
		arr[x][i] = val;
		arr[n][i] = val;
	}
}


void _print()
{

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < k; j++)
		{
			gotoxy(j, i);
			if(arr[i][j] == 1)
			{
				printf("*");
			}
		}
	}
	printf("\n");
}

void head(int x, int y)
{
	gotoxy(x, y);
	printf("@");
	usleep(400000 - speed);

	for(int i = 0; i < 5; i++)
	{
		if(x == obstx[i] && y == obsty[i])
		{
			e = 0;
			break;
		}
	}
}


void food()
{
	srand(time(NULL));
	a = rand() % 54 + 3;
	b = rand() % 14 + 4;

	for(int i = 0; i < 5; i++)
	{
		if(b == obsty[i] && a == obstx[i])
		{
			a = rand() % 54 + 3;
			i = 0;
		}
	}
}

void eat(int x, int y, int count)
{
	for(int i = 1; i <= count; i++)
	{
		gotoxy(tailx[i], taily[i]);
		printf("*");
	}

	for(int i = count; i > 0; i--)
	{
		tailx[i] = tailx[i-1];
		taily[i] = taily[i-1];
	}
}

void tail(int x, int y)
{
	for(int i = 0; i < count; i++)
	{
		if(tailx[i] == x && taily[i] == y)
		{
			e = 0;
			break;
		}
	}
}

void e_exit()
{
	gotoxy(29, 2);
	if(e == 2)
		printf("Exit");
}

void obstacles()
{
	if((count+1) % 10 == 0)
	{
		srand(time(NULL));
		for(int i = 0; i < 5; i++)
		{
			obsty[i] = rand() % 19 + 3;
			obstx[i] = rand() % 62 + 3;
		}
	}
	for(int i = 0; i < 5; i++)
	{
		gotoxy(obstx[i], obsty[i]);
		printf("|");
	}
}
