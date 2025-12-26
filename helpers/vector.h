#ifndef OXYGEN_VECTOR_H
#define OXYGEN_VECTOR_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "./Token.h"

static constexpr size_t VECTOR_INITIAL_CAPACITY = 4;

struct vector
{
    Token **data;
    size_t size;
    size_t capacity;
    void (*elem_free)(Token *);
};

typedef struct vector vector;

inline void vector_init(vector *v)
{
    if (!v) return;
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    v->elem_free = NULL;
}

inline void vector_init_with_dtor(vector *v, void (*elem_free)(Token *))
{
    if (!v) return;
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    v->elem_free = elem_free;
}

inline int vector_reserve(vector *v, size_t min_capacity)
{
    if (!v) return -1;
    if (v->capacity >= min_capacity) return 0;

    size_t new_capacity = v->capacity ? v->capacity : VECTOR_INITIAL_CAPACITY;
    while (new_capacity < min_capacity) {
        if (new_capacity > SIZE_MAX / 2) { /* overflow check */
            new_capacity = min_capacity;
            break;
        }
        new_capacity *= 2;
    }

    Token **tmp = realloc(v->data, new_capacity * sizeof(struct Token *));
    if (!tmp) return -1;
    v->data = tmp;
    v->capacity = new_capacity;
    return 0;
}

inline int vector_push(vector *v, Token *elem)
{
    if (!v || !elem) return -1;
    if (v->size >= v->capacity) {
        int r = vector_reserve(v, v->capacity ? v->capacity * 2 : VECTOR_INITIAL_CAPACITY);
        if (r != 0) return -1;
    }
    v->data[v->size++] = elem;
    return 0;
}

inline Token *vector_pop(vector *v)
{
    if (!v || v->size == 0) return NULL;
    return v->data[--v->size];
}

inline Token *vector_get(const vector *v, size_t index)
{
    if (!v || index >= v->size) return NULL;
    return v->data[index];
}

inline int vector_set(vector *v, size_t index, Token *elem)
{
    if (!v || index >= v->size || !elem) return -1;
    if (v->elem_free) v->elem_free(v->data[index]);
    v->data[index] = elem;
    return 0;
}

inline int vector_erase(vector *v, size_t index)
{
    if (!v || index >= v->size) return -1;
    if (v->elem_free) v->elem_free(v->data[index]);
    /* shift left */
    for (size_t i = index + 1; i < v->size; ++i) {
        v->data[i - 1] = v->data[i];
    }
    v->size--;
    return 0;
}

inline void vector_clear(vector *v)
{
    if (!v) return;
    if (v->elem_free) {
        for (size_t i = 0; i < v->size; ++i) {
            v->elem_free(v->data[i]);
        }
    }
    v->size = 0;
}

inline void vector_free(vector *v)
{
    if (!v) return;
    if (v->elem_free) {
        for (size_t i = 0; i < v->size; ++i) {
            v->elem_free(v->data[i]);
        }
    }
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    v->elem_free = NULL;
}

inline size_t vector_size(const vector *v)
{
    if (!v) return 0;
    return v->size;
}

inline size_t vector_capacity(const vector *v)
{
    if (!v) return 0;
    return v->capacity;
}
#endif //OXYGEN_VECTOR_H