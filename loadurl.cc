/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include <sys/socket.h>
#include <unistd.h>

#include "util.hh"
#include "url_loader.hh"
#include "exception.hh"
#include "event_loop.hh"

using namespace std;

int main( int argc, char *argv[] )
{
    try {
        /* clear environment */
        environ = nullptr;

        check_requirements( argc, argv );

        if ( argc != 2 ) {
            throw Exception( "Usage", string( argv[ 0 ] ) + " url" );
        }

        EventLoop pageload_loop;

        pageload_loop.add_child_process( "url", [&] () {
                URLLoader load_page;
                load_page.get_all_resources( string( argv[1] ) );
                return EXIT_SUCCESS;
            } );

        return pageload_loop.loop();
    } catch ( const Exception & e ) {
        e.perror();
        return EXIT_FAILURE;
    }
}