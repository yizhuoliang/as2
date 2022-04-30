#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function prototype */
int cell_generation(int matrix[5][5], int row, int column);

int main(int argc, char **argv)
{

    // when user input number of generation and input file
    if (argc >= 3)
    {
        // get number of generations
        int number_of_generation = atoi(argv[1]);

        // read in initial matrix from input file
        FILE *filePointer;
        filePointer = fopen(argv[2], "r");
        int matrix[5][5];
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                fscanf(filePointer, "%d", &matrix[i][j]);
            }
        }
        fclose(filePointer);

        // for each generation, calculate the new state
        // using a new array, to store new state
        // so that cells can not see the new state of the neighbors
        int new_state[5][5];
        for (int k = 0; k < number_of_generation; k++)
        {
            // for each cell, decide the state of cell
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    new_state[i][j] = cell_generation(matrix, i, j);
                }
            }

            // for each cell, update the cell's state
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    matrix[i][j] = new_state[i][j];
                }
            }
        }


        // output final to file
        FILE *f = fopen(strcat(argv[2], ".out"), "w");
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                fprintf(f, "%d ", matrix[i][j]);
            }
            fprintf(f, "%s\n", "");
        }
        fclose(f);
    }
    return 0;
}

// calculate next generation state for a cell according to the rule
int cell_generation(int matrix[5][5], int row, int column)
{
    // current cell state
    int s = matrix[row][column];
    // neighbor's live count
    int live_count = 0;

    // iterate cell's neighbor, count live cells
    for (int i = row - 1; i <= row + 1; i++)
    {
        for (int j = column - 1; j <= column + 1; j++)
        {
            if (i >= 0 && i < 5 && j >= 0 && j < 5)
            {
                if (i != row || j != column)
                {
                    if (matrix[i][j] == 1)
                    {
                        live_count++;
                    }
                }
            }
        }
    }

    // calculate new cell state according to current state and
    // neighbor's live count
    if (s == 1)
    {
        if (live_count != 2 && live_count != 3)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if (live_count == 3)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}