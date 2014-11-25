#include <stumpless/target.h>

#include "private/formatter.h"
#include "private/handler.h"
#include "private/type.h"
#include "private/status.h"

Target *
CopyTarget
( const Target *target )
{
  return NULL;
}

void
DestroyTarget
( Target *target )
{
  return;
}

Status *
LogToTarget
( const Target *target, Record *record )
{
  if( !target || !target->formatter || !target->handler || !record )
    return RaiseStatus( "empty argument" );

  return HandleOutput( target->handler, FormatRecord( target->formatter, record ) );
}
