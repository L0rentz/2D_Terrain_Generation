#include "my.h"

cell_node_t *create_cell_node(all_t *s_all, int offset)
{
    cell_node_t *node = malloc(sizeof(cell_node_t));
    node->s_cells = malloc(sizeof(cell_t) * s_all->s_cell_head->height);
    float noise = perlin2d(s_all->s_perlin.index - offset, 0, s_all->s_perlin.freq, s_all->s_perlin.depth, s_all);
    for (int y = 0; y < s_all->s_cell_head->height; y++) {
        if (noise * s_all->s_cell_head->height <= y)
            node->s_cells[y].alive = 1;
        else
            node->s_cells[y].alive = 0;
        node->s_cells[y].position = (sfVector2f){(s_all->s_perlin.index - offset - 1) * s_all->s_cell_head->cell_size.x, y * s_all->s_cell_head->cell_size.y};
        node->s_cells[y].rectangle = sfRectangleShape_create();
        sfRectangleShape_setPosition(node->s_cells[y].rectangle, node->s_cells[y].position);
        sfRectangleShape_setSize(node->s_cells[y].rectangle, s_all->s_cell_head->cell_size);
        sfRectangleShape_setFillColor(node->s_cells[y].rectangle, sfWhite);
    }
    node->back = NULL;
    node->next = NULL;
    return (node);
}

void cell_push_back(all_t *s_all)
{
    cell_node_t *node = create_cell_node(s_all, 0);
    if (s_all->s_cell_head->length == 0) {
        s_all->s_cell_head->head = node;
        s_all->s_cell_head->tail = node;
    }
    else {
        s_all->s_cell_head->tail->next = node;
        node->back = s_all->s_cell_head->tail;
        s_all->s_cell_head->tail = node;
    }
    s_all->s_cell_head->length++;
}

void cell_push_front(all_t *s_all)
{
    cell_node_t *node = create_cell_node(s_all, s_all->s_cell_head->width);
    if (s_all->s_cell_head->length == 0) {
        s_all->s_cell_head->head = node;
        s_all->s_cell_head->tail = node;
    }
    else {
        s_all->s_cell_head->head->back = node;
        node->next = s_all->s_cell_head->head;
        s_all->s_cell_head->head = node;
    }
    s_all->s_cell_head->length++;
}

void cell_pop_back(all_t *s_all)
{
    if (s_all->s_cell_head->length == 0)
        return;
    for (int y = 0; y != s_all->s_cell_head->height; y++) {
        sfRectangleShape_destroy(s_all->s_cell_head->tail->s_cells[y].rectangle);
        s_all->s_cell_head->tail->s_cells[y].rectangle = NULL;
    }
    free(s_all->s_cell_head->tail->s_cells);
    if (s_all->s_cell_head->length == 1) {
        free(s_all->s_cell_head->tail);
        s_all->s_cell_head->head = NULL;
        s_all->s_cell_head->tail = NULL;
    }
    else {
        s_all->s_cell_head->tail = s_all->s_cell_head->tail->back;
        free(s_all->s_cell_head->tail->next);
        s_all->s_cell_head->tail->next = NULL;
    }
    s_all->s_cell_head->length--;
}

void cell_pop_front(all_t *s_all)
{
    if (s_all->s_cell_head->length == 0)
        return;
    for (int y = 0; y != s_all->s_cell_head->height; y++) {
        sfRectangleShape_destroy(s_all->s_cell_head->head->s_cells[y].rectangle);
        s_all->s_cell_head->head->s_cells[y].rectangle = NULL;
    }
    free(s_all->s_cell_head->head->s_cells);
    if (s_all->s_cell_head->length == 1) {
        free(s_all->s_cell_head->head);
        s_all->s_cell_head->head = NULL;
        s_all->s_cell_head->tail = NULL;
    }
    else {
        s_all->s_cell_head->head = s_all->s_cell_head->head->next;
        free(s_all->s_cell_head->head->back);
        s_all->s_cell_head->head->back = NULL;
    }
    s_all->s_cell_head->length--;
}