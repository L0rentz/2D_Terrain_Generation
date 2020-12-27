#include "my.h"

void scrolling_left(all_t *s_all)
{
    for (int i = 1; i < s_all->s_map.width; i++)
        s_all->s_map.perlin_noise[i - 1] = s_all->s_map.perlin_noise[i];
    s_all->s_map.perlin_noise[s_all->s_map.width - 1] = perlin2d(s_all->s_map.perlin_index, 0, s_all->s_map.perlin_freq, s_all->s_map.perlin_depth, s_all);
    s_all->s_map.perlin_index++;
    for (int y = 0; y < s_all->s_map.height; y++) {
        for (int x = 1; x < s_all->s_map.width; x++) {
            s_all->s_map.s_cells[y][x - 1].alive = s_all->s_map.s_cells[y][x].alive;
        }
    }
    for (int y = 0; y < s_all->s_map.height; y++) {
        if (s_all->s_map.perlin_noise[s_all->s_map.width - 1] * s_all->s_map.height <= y)
            s_all->s_map.s_cells[y][s_all->s_map.width - 1].alive = 1;
        else
            s_all->s_map.s_cells[y][s_all->s_map.width - 1].alive = 0;
    }
}

void scrolling_right(all_t *s_all)
{
    for (int i = s_all->s_map.width - 2; i >= 0; i--)
        s_all->s_map.perlin_noise[i + 1] = s_all->s_map.perlin_noise[i];
    s_all->s_map.perlin_noise[0] = perlin2d(s_all->s_map.perlin_index - s_all->s_map.width, 0, s_all->s_map.perlin_freq, s_all->s_map.perlin_depth, s_all);
    s_all->s_map.perlin_index--;
    for (int y = 0; y < s_all->s_map.height; y++) {
        for (int x = s_all->s_map.width - 2; x >= 0; x--) {
            s_all->s_map.s_cells[y][x + 1].alive = s_all->s_map.s_cells[y][x].alive;
        }
    }
    for (int y = 0; y < s_all->s_map.height; y++) {
        if (s_all->s_map.perlin_noise[0] * s_all->s_map.height <= y)
            s_all->s_map.s_cells[y][0].alive = 1;
        else
            s_all->s_map.s_cells[y][0].alive = 0;
    }
}

void map_scrolling(all_t *s_all)
{
    if (s_all->s_keys.left == 1 && s_all->s_keys.right == 0)
        scrolling_left(s_all);
    if (s_all->s_keys.left == 0 && s_all->s_keys.right == 1)
        scrolling_right(s_all);
}