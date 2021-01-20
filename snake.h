#ifndef SNAKE_H
#define SNAKE_H

void gotoxy(int ,int );
int kbhit(void);
void border(int, int, int, int);
void _print();
void food();
void head(int, int);
void eat(int, int, int);
void keys(int *, int *);
void tail(int, int);
void e_exit();
void obstacles();

#endif
