#include <stdio.h>
#include <string.h>

#include <stumpless/exception.h>
#include <stumpless/target.h>

#include "private/container/list.h"
#include "private/container/list/target.h"
#include "private/container/list/inheritance.h"
#include "private/container/list/iterator.h"
#include "private/container/list/const_iterator/target.h"
#include "private/container/list/const_reverse_iterator/target.h"
#include "private/container/list/iterator/target.h"
#include "private/container/list/reverse_iterator/target.h"
#include "private/type.h"
#include "static/container/list/target.h"

ADD_SEPARATOR_TO_LIST( Target )

APPEND_LISTS( Target )

APPEND_TO_LIST( Target )

BEGIN_LIST( Target )

CBEGIN_LIST( Target )

CEND_LIST( Target )

COPY_LIST( Target )

CRBEGIN_LIST( Target )

CREND_LIST( Target )

DESTROY_LIST( Target )

END_LIST( Target )

LIST_BACK( Target )

LIST_CONTAINS( Target )

LIST_FRONT( Target )

LIST_IS_EMPTY( Target )

LIST_SIZE( Target )

Exception *
LogToTargetList
( const TargetList *list, const Record *record )
{
  ListIterator *targets;
  Target *target;

  if( !list || !record )
    return RaiseException( "empty argument" );

  targets = BeginList( list->list );
  while( target = NextInListIterator( targets ) ){
    LogToTarget( target, record );
  }

  return NULL;
}

NEW_LIST( Target )

PREPEND_TO_LIST( Target )

RBEGIN_LIST( Target )

REND_LIST( Target )
