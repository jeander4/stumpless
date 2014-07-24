#include <stdlib.h>

#include "private/container/dictionary.h"
#include "private/formatter.h"
#include "private/formatter/csv.h"
#include "private/formatter/initializer.h"
#include "private/formatter/text.h"
#include "private/status.h"

#define FORMATTER_INITIALIZER_FUNCTION( formatter_name, function_name )        \
Formatter *                                                                    \
Initialize##function_name##Formatter                                           \
( void )                                                                       \
{                                                                              \
  Formatter * formatter = malloc( sizeof( Formatter ) );                       \
  if( formatter == NULL )                                                      \
    return NULL;                                                               \
                                                                               \
  formatter->name = formatter_name;                                            \
  formatter->format = EntryTo##function_name;                                  \
  formatter->filters = NULL;                                                   \
  formatter->options = NULL;                                                   \
                                                                               \
  return formatter;                                                            \
}

#define ADD_FORMATTER( name, function )                                        \
SetDictionaryValue( initializers, name, Initialize##function##Formatter );

static Dictionary * initializers = NULL;

FORMATTER_INITIALIZER_FUNCTION( "csv", CSV )

Status *
InitializeFormatterByName
( const char * name )
{
  if( initializers == NULL ){

    initializers = NewDictionary();
    if( initializers == NULL )
      return RaiseStatus( "constructor failure" );

    ADD_FORMATTER( "csv", CSV )
    ADD_FORMATTER( "text", Text )
  }

  Formatter * ( *initializer )();
  initializer = GetDictionaryValue( initializers, name );
  if( initializer == NULL )
    return NULL;
  else
    return AddFormatter( initializer() );
}

FORMATTER_INITIALIZER_FUNCTION( "text", Text )
