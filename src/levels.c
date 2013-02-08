#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <levels.h>
#include <types.h>

StumplessLevel *
StumplessGetDebugLevel( void )
{
  StumplessLevel * debug = malloc( sizeof( StumplessLevel ) );
  
  if( debug == NULL )
    return NULL;
  
  debug->level = 30;
  debug->name = "debug";
  
  return debug;
}

StumplessLevel *
StumplessGetErrorLevel( void )
{
  StumplessLevel * error = malloc( sizeof( StumplessLevel ) );
  
  if( error == NULL )
    return NULL;
  
  error->level = 10;
  error->name = "error";
  
  return error;
}

StumplessLevel *
StumplessGetFatalLevel( void )
{
  StumplessLevel * fatal = malloc( sizeof( StumplessLevel ) );
  
  if( fatal == NULL )
    return NULL;
  
  fatal->level = 0;
  fatal->name = "fatal";
  
  return fatal;
}

StumplessLevel *
StumplessGetInfoLevel( void )
{
  StumplessLevel * info = malloc( sizeof( StumplessLevel ) );
  
  if( info == NULL )
    return NULL;
  
  info->level = 40;
  info->name = "info";
  
  return info;
}

StumplessLevel *
StumplessGetWarningLevel( void )
{
  StumplessLevel * warning = malloc( sizeof( StumplessLevel ) );
  
  if( warning == NULL )
    return NULL;
  
  warning->level = 20;
  warning->name = "warning";
  
  return warning;
}

char *
StumplessLevelToString( StumplessLevel * level )
{
  if( level == NULL )
    return NULL;
  
  // todo may be able to save memory by calculating a
  //      more exact size of this string
  size_t string_length = strlen( level->name ) + 10 + 9;
  char * description = malloc( sizeof( char ) * string_length );
  if( description == NULL )
    return NULL;
  
  sprintf( description, "%s: level %d", level->name, level->level );
  
  return description;
}
