#ifndef OXYGEN_OPTIONAL_STRING_H
#define OXYGEN_OPTIONAL_STRING_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @struct OptionalString
 * @brief A structure representing an optional string value.
 * 
 * This struct encapsulates a string value that may or may not be present,
 * similar to Optional<String> in other languages.
 * 
 * @member has A boolean flag indicating whether a value is present.
 * @member value A pointer to the string value (empty string if not set).
 */
struct OptionalString {
    bool has_value;
    char *value;
};

typedef struct OptionalString OptionalString;

/* Constructors */

/**
 * @brief Creates an OptionalString with no value.
 * 
 * @return An OptionalString instance with has set to false and value set to empty string.
 */
static OptionalString OpStr_Init(void) {
    const OptionalString o = { false, "" };
    return o;
}

/**
 * @brief Creates an OptionalString with the provided value.
 * 
 * @param o Pointer to the OptionalString to set.
 * @param v A pointer to the string value to store.
 * @return An OptionalString instance with has set to true and value set to v.
 */
static OptionalString OpStr_set(OptionalString *o, char * v) {
    if (o == NULL)
    {
        printf("[ERROR] OptionalString pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    o->value = v;
    o->has_value = true;
    return *o;
}

/**
 * @brief Checks if an OptionalString contains a value.
 * 
 * @param o Pointer to the OptionalString to check.
 * @return true if the OptionalString contains a value, false otherwise or if o is NULL.
 */
static bool OpStr_has_value(const OptionalString *o) {
    return o ? o->has_value : false;
}

/**
 * @brief Retrieves the string value or a default value.
 * 
 * @param o Pointer to the OptionalString to query.
 * @return The stored string value if present, otherwise the default value.
 */
static char * OpStr_get_value(const OptionalString *o) {
    if (o == NULL)
    {
        printf("[ERROR] OptionalString pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    if (!o->has_value)
    {
        printf("[WARNING] OptionalString has no value\n");
        return "\0";
    }
    return o->value;
}
#endif