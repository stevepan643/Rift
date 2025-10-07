/*
 * module.c - Rift Builder module parser
 */

#include "module.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

static char* trim ( char* s ) {
    while ( *s == ' ' || *s == '\t' ) s++;
    char* e = s + strlen ( s );
    while ( e > s && ( e[-1] == ' ' || e[-1] == '\t'
            || e[-1] == '\n' || e[-1] == '\r' ) ) *--e = '\0';
    return s;
}

static void parse_block (
    FILE* f, string_list_t* list, const char* end_key
) {
    char line[256];
    while ( fgets ( line, sizeof line, f ) ) {
        char* s = trim ( line );
        if ( strcmp ( s, "}" ) == 0
            || strncmp ( s, end_key, strlen ( end_key ) ) == 0 )
            break;
        if ( *s == '\0' ) continue;
        if ( *s == '"' ) s++;
        char* q = strchr ( s, '"' );
        if ( q ) *q = '\0';
        add_string_to_list ( list, s );
    }
}

module_t* load_module_definition ( const char* path ) {
    FILE* f = fopen ( path, "r" );
    if ( !f ) return NULL;

    module_t* m = malloc ( sizeof *m );
    if ( !m ) { fclose ( f ); return NULL; }

    m->name = strdup ( "No Name" );
    m->type = MODULE_TYPE_SHAREDLIB;
    m->version = VER ( 1, 0, 0 );
    m->source_files = create_string_list ();
    m->public_include_paths = create_string_list ();
    m->dependencies = create_string_list ();
    m->defines = create_string_list ();
    m->export_flag = true;

    char line[256]; int n = 0;
    while ( fgets ( line, sizeof line, f ) ) {
        n++;
        char* c = strchr ( line, '#' );
        if ( c ) *c = '\0';
        char* s = trim ( line );
        if ( *s == '\0' || strcmp ( s, "{" ) == 0
             || strcmp ( s, "}" ) == 0 ) continue;

        if ( strncmp ( s, "module(", 7 ) == 0 ) {
            char* a = strchr ( s, '(' ), *b = strchr ( s, ')' );
            if ( a && b && b > a ) {
                *b = '\0'; a++;
                if ( *a == '"' ) a++;
                char* q = strchr ( a, '"' );
                if ( q ) *q = '\0';
                free ( m->name ); m->name = strdup ( a );
            }
        }
        else if ( strncmp ( s, "type", 4 ) == 0 ) {
            char* t = trim ( strchr ( s, ' ' ) );
            if ( strcmp ( t, "SharedLib" ) == 0 )
                m->type = MODULE_TYPE_SHAREDLIB;
            else if ( strcmp ( t, "StaticLib" ) == 0 )
                m->type = MODULE_TYPE_STATICLIB;
            else if ( strcmp ( t, "Executable" ) == 0 )
                m->type = MODULE_TYPE_EXECUTABLE;
        }
        else if ( strncmp ( s, "version", 7 ) == 0 ) {
            char* v = trim ( strchr ( s, ' ' ) );
            int a = 0, b = 0, c2 = 0;
            sscanf ( v, "%d.%d.%d", &a, &b, &c2 );
            m->version = VER ( a, b, c2 );
        }
        else if ( strncmp ( s, "sources {", 9 ) == 0 )
            parse_block ( f, m->source_files, "public_inc" );
        else if ( strncmp ( s, "public_inc {", 12 ) == 0 )
            parse_block ( f, m->public_include_paths, "dependencies" );
        else if ( strncmp ( s, "dependencies {", 14 ) == 0 )
            parse_block ( f, m->dependencies, "defines" );
        else if ( strncmp ( s, "defines {", 9 ) == 0 )
            parse_block ( f, m->defines, "export" );
        else if ( strncmp ( s, "export", 6 ) == 0 ) {
            char* v = trim ( strchr ( s, ' ' ) );
            m->export_flag = ( strcmp ( v, "true" ) == 0 );
        }
        else
            printf ( "Warning: %s Unknown line (%d): %s\n", path, n, s );
    }

    fclose ( f );
    return m;
}

void free_module ( module_t* m ) {
    if ( !m ) return;

    free ( m->name );
    free_string_list ( m->source_files );
    free_string_list ( m->public_include_paths );
    free_string_list ( m->dependencies );
    free_string_list ( m->defines );
    free ( m );
}
