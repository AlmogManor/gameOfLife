#include <stdio.h>
#include <malloc.h>

#define BOARD_SIZE (11)

/* 
    generates the next generation in Conway's Game Of Life.
Args:
    previousGen - reference to a square array contating the previous generation.
    nextGen - reference to a square array (of the same size) inside of which the new generation will be born.
    size - the length of the array (because the arrays are squares). e.g: for an array of size 100, 10 will be passed.
*/
void nextGeneration(int *previousGen, int *nextGen, int size);
/*
    prints a two dimensional array.
Args:
    array - reference to the array to print
    width - array width
    height - array height
*/
void print2DArray(int *array, int width, int height);

int main(int argc, int** argv)
{
    int start[BOARD_SIZE][BOARD_SIZE] = {{1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                         {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    int *board = &start[0][0];

    int *nextBoard = (int *)malloc(BOARD_SIZE * BOARD_SIZE * sizeof(int));

    char userInput = 0x0A;

    while (userInput == 0x0A)
    {
        print2DArray(board, BOARD_SIZE, BOARD_SIZE);
        nextGeneration(board, nextBoard, BOARD_SIZE);

        int *temp = board;
        board = nextBoard;
        nextBoard = temp;

        scanf("%c", &userInput);
    }

    return 0;
}

void nextGeneration(int *previousGen, int *nextGen, int size)
{
    for (int y = 0; y < size; ++y)
    {
        for (int x = 0; x < size; ++x)
        {
            int aliveCells = 0;

            for (int i = 0; i < 9; i++)
            {
                int surroundingX = (i % 3) - 1;
                int surroundingY = (i / 3) - 1;

                int relativeX = x + surroundingX;
                int relativeY = y + surroundingY;

                /* make sure we dont go out of bounds and not counting the cell itself, only surrounding */
                if (i != 4 && relativeX >= 0 && relativeX < size && relativeY >= 0 && relativeY < size)
                    aliveCells += *(previousGen + relativeX + (size * relativeY));
            }

            /*
            if less than 2 or more than 3 -> die
            if exactly 3 -> born
            if exactly 2 -> stay the same
            */

            if (aliveCells < 2 || aliveCells > 3)
                *nextGen = 0;
            else if (aliveCells == 2)
                *nextGen = *(previousGen + x + (size * y));
            else if (aliveCells == 3)
                *nextGen = 1;

            nextGen++;
        }
    }
}

void print2DArray(int *array, int width, int height)
{
    for (int y = 0; y < width; ++y)
    {
        for (int x = 0; x < height; ++x)
        {
            if (*(array + x + (width * y)))
                printf("*"); /*alive*/
            else
                printf("#"); /*dead*/
        }
        printf("\n");
    }

    for (int i = 0; i < width; ++i)
    {
        printf("-");
    }

    printf("-----\n");
}