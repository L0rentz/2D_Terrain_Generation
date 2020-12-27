#include "my.h"

void allocate_map_cells(all_t *s_all)
{
    s_all->s_map.s_cells = malloc(sizeof(cell_t) * s_all->s_map.height);
    for (int y = 0; y < s_all->s_map.height; y++) {
        s_all->s_map.s_cells[y] = malloc(sizeof(cell_t) * s_all->s_map.width);
        for (int x = 0; x < s_all->s_map.width; x++) {
            if (s_all->s_map.perlin_noise[x] * s_all->s_map.height <= y)
                s_all->s_map.s_cells[y][x].alive = 1;
            else
                s_all->s_map.s_cells[y][x].alive = 0;
            s_all->s_map.s_cells[y][x].position = (sfVector2f){x * s_all->s_map.cell_size.x, y * s_all->s_map.cell_size.y};
            s_all->s_map.s_cells[y][x].rectangle = sfRectangleShape_create();
            sfRectangleShape_setPosition(s_all->s_map.s_cells[y][x].rectangle, s_all->s_map.s_cells[y][x].position);
            sfRectangleShape_setSize(s_all->s_map.s_cells[y][x].rectangle, s_all->s_map.cell_size);
            sfRectangleShape_setFillColor(s_all->s_map.s_cells[y][x].rectangle, sfWhite);
        }
    }
}

void free_cells_array(all_t *s_all)
{
    for (int i = 0; i < s_all->s_map.height; i++) {
        for (int j = 0; j < s_all->s_map.width; j++) {
            sfRectangleShape_destroy(s_all->s_map.s_cells[i][j].rectangle);
            s_all->s_map.s_cells[i][j].rectangle = NULL;
        }
        free(s_all->s_map.s_cells[i]);
        s_all->s_map.s_cells[i] = NULL;
    }
    free(s_all->s_map.s_cells);
    s_all->s_map.s_cells = NULL;
    free(s_all->s_map.perlin_noise);
    s_all->s_map.perlin_noise = NULL;
}

void init_map(all_t *s_all)
{
    s_all->s_map.cell_size = (sfVector2f){8, 8};
    s_all->s_map.width = 1920 / s_all->s_map.cell_size.x;
    s_all->s_map.height = 1080 / s_all->s_map.cell_size.y;
    s_all->s_map.perlin_noise = malloc(sizeof(float) * s_all->s_map.width);
    s_all->seed = rand();
    s_all->s_map.perlin_index = 0;
    s_all->s_map.perlin_depth = 5;
    s_all->s_map.perlin_freq = 0.010;
    for (int x = 0; x < s_all->s_map.width; x++, s_all->s_map.perlin_index++)
        s_all->s_map.perlin_noise[x] = perlin2d(s_all->s_map.perlin_index, 0, s_all->s_map.perlin_freq, s_all->s_map.perlin_depth, s_all);
    allocate_map_cells(s_all);
}