all: snake.c
    gcc -o snake snake.c main.c
clean:
    rm snake
