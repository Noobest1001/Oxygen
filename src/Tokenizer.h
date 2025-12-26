#pragma once

#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#include "../helpers/optional_int.h"
#include "../helpers/optional_string.h"
#include "../helpers/optional_char.h"
#include "../helpers/vector.h"
#include "../helpers/Token.h"

[[nodiscard]] inline OptionalChar peek(char * src , unsigned long offset);
inline OptionalInt bin_prec(enum TokenType type);
inline char consume(const char * src, unsigned long offset);
inline void Tokenizer(char src[]);


inline char * To_string(const enum TokenType type)
{
    switch (type)
    {
        case _return: return "return";
        case _int: return "int";
        case _address: return "address";
        case _semi: return ";";
        case _open_paren: return "(";
        case _close_paren: return ")";
        case _declare: return "declare";
        case _eq: return "=";
        case plus: return "+";
        case star: return "*";
        case minus: return "-";
        case fslash: return "/";
        case exclamation: return "!";
        case _method_name: return "method_name";
        case _if: return "if";
        case _elif: return "elif";
        case _else: return "else";
        case _grtn: return ">";
        case _lstn: return "<";
        case _address_ind: return "&";
        default: return "Error";
    }
    assert(false);
}

inline OptionalInt bin_prec(const enum TokenType type)
{
    OptionalInt o = OpInt_Init();
    switch (type)
    {
        case plus:
        case minus:
            o = OpInt_set(&o, 1);
            return o;
        case star:
        case fslash:
            o = OpInt_set(&o, 2);
            return o;
        default:
            o = OpInt_set(&o, 0);
            return o;
    }
}

static unsigned long place = 0;

inline void Tokenizer(char src[])
{
    if(src == NULL)
        return;
    place = 1;
    vector tokens;
    char* buffer = "";
    while (peek(src,place).has_value && isalpha(peek(src,place).value))
    {
        if(isalnum(peek(src,place).value))
        {
            consume(strcat(buffer,src),place);
            while (peek(src,place).has_value && isalnum(peek(src,place).value))
            {
                consume(strcat(buffer,src),place);
            }
            if (strcmp(buffer,"return") == 0)
            {
                //create return token
            }
            else if (strcmp(buffer,"int") == 0)
            {
                //create int token
            }
            else if (strcmp(buffer,"address") == 0)
            {
                //create address token
            }
            else if (strcmp(buffer,"declare") == 0)
            {
                //create declare token
            }
            else if (strcmp(buffer,"if") == 0)
            {
                //create if token
            }
            else if (strcmp(buffer,"elif") == 0)
            {
                //create elif token
            }
            else if (strcmp(buffer,"else") == 0)
            {
                //create else token
            }
            else
            {
                //create method_name token
            }
        }
    }
    
}

[[nodiscard]] inline OptionalChar peek(char * src , unsigned long offset)
{
    if(!src)
    {
        printf("[Error] source is NULL in peek function\n");
        exit(EXIT_FAILURE);
    }
    struct OptionalChar o = OpChar_Init();
    if (offset == ULONG_MAX)
    {
        offset = 0;
    }
    if(place + offset >=  strlen(src))
    {
        return o;
    }
    return OpChar_set(&o, src[place + offset]);
}

inline char consume(const char * src, const unsigned long offset )
{
    if (offset == ULONG_MAX)
    {
        return src[place];
    }
    return src[place + offset];
}