/*
 * base.h
 * 
 * Description:
 *  This files defines the foundational types and macros used across
 *  the Rift Builder project. It includes basic type definitions, utility
 *  functions, and common data structures.
 * 
 */

#ifndef RIFT_BUILDER_BASE_H
#define RIFT_BUILDER_BASE_H

#include <stdint.h>

/*
 * string_list_t
 * 
 * Description:
 *  Represents a dynamic list of strings.
 */
typedef struct string_list_t {
    char**      items;
    uint32_t    count;
} string_list_t;

/* Function to create a new string list */
string_list_t* create_string_list();

/* Function to free the memory used by a string list */
void free_string_list( string_list_t* list );

/* Function to add a string to the string list */
void add_string_to_list( string_list_t* list, const char* str );

#endif // RIFT_BUILDER_BASE_H
