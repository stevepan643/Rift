#include "module.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string_t str_of( char *s )
{
    string_t str = { 0 };
    if ( s ) {
        str.size = strlen(s);
        str.str = (char*)malloc( str.size + 1 );
        if ( str.str ) strcpy( str.str, s );
    }
    return str;
}

void str_free( string_t* str )
{
    free( str->str );
}

string_list_t str_list()
{}

void str_list_free( string_list_t *slist )
{}

void str_list_add( string_t str )
{}

module_t module_load( string_t path )
{
    module_t m = { 0 };

    char s[256];

    FILE* fp = fopen( path.str, "r" );
    if ( !fp ) return m;

    while ( fgets(s, 256, fp) ) {
        
    }

    fclose( fp );
    return m;
}

void module_free( module_t* module )
{
    str_free( &module->name );

    str_list_free( &module->public_include );
    str_list_free( &module->depends );
    str_list_free( &module->defines );

    free( module );
}
