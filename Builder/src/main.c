#include "module.h"

int main( void )
{
    module_t m = module_load( str_of( "src/main.c" ) );

    module_free( &m );

    return 0;
}
