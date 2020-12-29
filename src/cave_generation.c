#include "my.h"

sfVector2f getDirection(float radians)
{
    float cosY = (float)cos(radians);
    float sinY = (float)sin(radians);
    return (sfVector2f){cosY, sinY};
}

void dig(int x, int y, all_t *s_all)
{
    cell_node_t *tmp = s_all->s_cell_head->head;
    for (int width = 0; tmp != NULL && width != x; tmp = tmp->next, width++);
    if (tmp == NULL)
        return;
    if (y > 0)
        tmp->s_cells[y - 1].alive = 0;
    tmp->s_cells[y].alive = 0;
    if (y < s_all->s_cell_head->height - 1)
        tmp->s_cells[y + 1].alive = 0;
    if (tmp->next != NULL)
        tmp->next->s_cells[y].alive = 0;
    if (tmp->back != NULL)
        tmp->back->s_cells[y].alive = 0;
}

float noise_to_radians(double noise)
{
    return (noise * 6.28319);
}

void direction_selector(float addX, float addY, float *x, float *y)
{
    int random = rand() % 2;
    if (random == 0)
        *x += addX;
    else
        *x -= addX;
    random = rand() % 2;
    if (random == 0)
        *y -= addY;
    else
        *y += addY;
}

void gen_one_cave(int x0, int y0, all_t *s_all)
{
    int xx = rand() % 1000;
    int zz = rand() % 1000;
    
    float x = x0;
    float y = y0;
    for (int i = 0, size = 0; i < s_all->s_cell_head->height / 5; i++) {
        double noise = perlin2d_octave(xx, zz, 0.01, 10, s_all);
        size = rand() % 50 + 1;
        xx += size;
         
        float addX = getDirection(noise_to_radians(noise)).x;
        float addY = getDirection(noise_to_radians(noise)).y;

        for (int h = 0; h < size; h++) {
            direction_selector(addX, addY, &x, &y);
            if (y < 0 || y >= s_all->s_cell_head->height || x >= s_all->s_cell_head->width || x < 0)
                continue;
            dig((int)x, (int)y, s_all);
        }
    }
}

void gen_caves(all_t *s_all, int caves_nb)
{
    for (int i = 0; i < caves_nb; i++) {
        int x = rand() % s_all->s_cell_head->width;
        int y = 0;
        cell_node_t *tmp = s_all->s_cell_head->head;
        for (int i = 0; tmp != NULL && i != x; tmp = tmp->next, i++);
        for (; y < s_all->s_cell_head->height && tmp->s_cells[y].alive == 0; y++);
        y = s_all->s_cell_head->height - y;
        if (y == 0)
            y = 1;
        y = s_all->s_cell_head->height - rand() % y;
        gen_one_cave(x, y, s_all);
    }
}