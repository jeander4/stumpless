#include <stdlib.h>
#include <stdio.h>

#include <stumpless.h>

#include "helper.h"

const char * test_file_write( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( test_file_write, "File Write Test Failed: %s\n" )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_file_write( void )
{
  StumplessStatusCode status = StumplessWriteToFile( NULL, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "a null file pointer did not generate the correct error";
  
  //FILE * file = fopen( "tmp/file_write", "w" );
  FILE * file = tmpfile();
  if( file == NULL )
    return "the test file could not be opened";
  
  status = StumplessWriteToFile( file, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty output parameter did not generate the correct error";
  
  if( fclose( file ) != 0 )
    return "the test file could not be closed";
  
  //if( remove( "tmp/file_write" ) != 0 )
  //  return "the test file could not be removed";
  
  return NULL;
}
