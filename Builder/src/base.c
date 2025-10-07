/*
 * base.c - Rift Builder foundational types and utilities 
 */

#include "base.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* Function to create a new string list */
string_list_t* create_string_list()
{
    /* Allocate memory for the string list */
    string_list_t* p = ( string_list_t* ) malloc ( sizeof( string_list_t ) );
    if ( !p ) { return NULL; } /* Allocation failed */
    p->items = NULL;
    p->count = 0;
    return p;
}

/* Function to free the memory used by a string list */
void free_string_list( string_list_t* list )
{
    if ( !list ) { return; }
    for ( uint32_t i = 0; i < list->count; ++i ) {
        free( list->items[i] ); /* Free each string */
    }
    free( list->items ); /* Free the array of string pointers */
    free( list ); /* Free the string list structure */
}

/* Function to add a string to the string list */
void add_string_to_list(string_list_t* list, const char* str) {
    if ( !list || !str ) return;

    char** new_items = ( char** )
                realloc ( list->items, ( list->count + 1 ) * sizeof( char* ) );
    if ( !new_items ) return; /* Reallocation failed */
    list->items = new_items;

    list->items[list->count] = strdup(str);
    if ( !list->items[list->count] ) return; /* Duplication failed */

    list->count += 1;
}
