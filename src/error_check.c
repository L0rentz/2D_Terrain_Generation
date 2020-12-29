#include "my.h"

int error_check(int ac, char **av)
{
    int cell_size = 0;
    if (ac != 2) {
        printf("Usage: ./PerlinNoise cellSize\n");
        return (-1);
    }
    cell_size = atoi(av[1]);
    if (cell_size <= 0) {
        printf("cellSize is equal or less to 0 or is not an integer.\n");
        return (-1);
    }
    return (cell_size);
}