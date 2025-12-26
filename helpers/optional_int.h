#ifndef OXYGEN_OPTIONAL_INT_H
#define OXYGEN_OPTIONAL_INT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct OptionalInt {
    bool has_value;
    int value;
};

typedef struct OptionalInt OptionalInt;

/* Constructors */
static OptionalInt OpInt_Init(void)
{
    const OptionalInt o = { false, 0 };
    return o;
}

inline OptionalInt OpInt_set(struct OptionalInt *o, int o_value)
{
    if(o == NULL)
    {
        printf("[Error] OptionalInt pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    if(!isdigit(o_value))
    {
        o->value = -1;
        o->has_value = false;
    }
    else
    {
        o->value = o_value;
        o->has_value = true;
    }
    return *o;
}

inline bool OpInt_has_value(const OptionalInt *o)
{
    if(o == NULL)
    {
        printf("[Error] OptionalInt pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    return o->has_value;
}

inline int OpInt_get_value(const OptionalInt *o)
{
    if(o == NULL)
    {
        printf("[Error] OptionalInt pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    if(!o->has_value)
    {
        printf("[Warning] OptionalInt pointer has no value\n");
        return -10;
    }
    return o->value;
}
#endif /* OXYGEN_OPTIONAL_INT_H */