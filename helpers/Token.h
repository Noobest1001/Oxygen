#ifndef OXYGEN_TOKEN_H
#define OXYGEN_TOKEN_H

#include "optional_string.h"

enum TokenType
{
    None,
    _return,
    _int,
    _address,
    _semi,
    _open_paren,
    _close_paren,
    _declare,
    _eq,
    plus,
    star,
    minus,
    fslash,
    exclamation,
    _method_name,
    _if,
    _elif,
    _else,
    _grtn,
    _lstn,
    _address_ind,
};

struct Token
{
    enum TokenType type;
    int line;
    OptionalString value;
};

typedef struct Token Token;

#endif