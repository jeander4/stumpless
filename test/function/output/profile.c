#include <stdio.h>
#include <stdlib.h>

#include "private/output/profile.h"
#include "private/type.h"
#include "test/helper.h"

const char * test_add_profile( void );
const char * test_find_profile_by_name( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result = NULL;
  
  RUN_TEST( add_profile )
  RUN_TEST( find_profile_by_name )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_add_profile
( void )
{
  OutputProfile * profile = BuildOutputProfile();
  FAIL_IF_NULL( profile, "the test profile could not be built" )
  
  Status * status = AddOutputProfile( profile );
  FAIL_IF_NOT_NULL( status, "the new profile could not be added" )
  
  OutputProfile * found = FindOutputProfileByName( profile->name );
  if( found != profile )
    return "the value was not added in such a way that it could be retrieved";
  
  return NULL;
}

const char *
test_find_profile_by_name
( void )
{
  OutputProfile * profile = FindOutputProfileByName( "text" );
  FAIL_IF_NULL( profile, "the intended profile could not be retrieved" )
  ASSERT_STRINGS_EQUAL( "text", profile->name, "the correct profile was not returned" )
  
  return NULL;
}
