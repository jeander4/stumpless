#include <stdio.h>
#include <stdlib.h>

#include <stumpless.h>

#include "helper.h"

const char * test_configuration_initializations( void );
const char * test_status_codes( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result = NULL;
  
  RUN_TEST( configuration_initializations )
  RUN_TEST( status_codes )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_configuration_initializations( void )
{
  StumplessLogDebug( "debug message\n" );
  if( StumplessGetConfiguration() == NULL )
    return "configuration was not initialized after StumplessLogDebug";
  
  StumplessLogError( "error message\n" );
  if( StumplessGetConfiguration() == NULL )
    return "configuration was not initialized after StumplessLogError";
  
  StumplessLogFatal( "fatal message\n" );
  if( StumplessGetConfiguration() == NULL )
    return "configuration was not initialized after StumplessLogFatal";
  
  StumplessLogInfo( "information message\n" );
  if( StumplessGetConfiguration() == NULL )
    return "configuration was not initialized after StumplessLogInfo";
  
  StumplessLogWarning( "warning message\n" );
  if( StumplessGetConfiguration() == NULL )
    return "configuration was not initialized after StumplessLogWarning";

  return NULL;
}

const char *
test_status_codes( void )
{
  if( StumplessLogDebug( "debug message\n" ) != STUMPLESS_SUCCESS )
    return "StumplessLogDebug returned a failure code";
  
  if( StumplessLogError( "error message\n" ) != STUMPLESS_SUCCESS )
    return "StumplessLogError returned a failure code";
  
  if( StumplessLogFatal( "fatal message\n" ) != STUMPLESS_SUCCESS )
    return "StumplessLogFatal returned a failure code";
  
  if( StumplessLogInfo( "information message\n" ) != STUMPLESS_SUCCESS )
    return "StumplessLogInfo returned a failure code";
  
  if( StumplessLogWarning( "warning message\n" ) != STUMPLESS_SUCCESS )
    return "StumplessLogWarning returned a failure code";
  
  return NULL;
}
