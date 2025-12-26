#ifndef OXYGEN_OPTIONAL_CHAR_H
#define OXYGEN_OPTIONAL_CHAR_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct OptionalChar {
    bool has_value;
    char value;
};

typedef struct OptionalChar OptionalChar;

static OptionalChar OpChar_Init(void)
{
    const OptionalChar o = { false, ' ' };
    return o;
}

inline OptionalChar OpChar_set(OptionalChar *o, char o_value)
{
    if(o == NULL)
    {
        printf("[Error] OptionalChar pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    o->value = o_value;
    o->has_value = true;
    return *o;
}

inline bool OpChar_has_value(const OptionalChar *o)
{
    if(o == NULL)
    {
        printf("[Error] OptionalChar pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    return o->has_value;
}

inline char OpChar_get_value(const OptionalChar *o)
{
    if(o == NULL)
    {
        printf("[Error] OptionalChar pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    if(!o->has_value)
    {
        printf("[Warning] OptionalChar pointer has no value\n");
        return '\0';
    }
    return o->value;
}
#endif /* OXYGEN_OPTIONAL_CHAR_H */