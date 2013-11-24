#include <stdio.h>
#include <string.h>

#include "private/adapter_list.h"
#include "private/adapter_list_static.h"
#include "private/configuration.h"
#include "private/list.h"
#include "private/status.h"
#include "private/type.h"

Status *
AppendToAdapterList
( AdapterList * list, Adapter * adapter )
{
  if( list == NULL || adapter == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = AppendToList( list->list, adapter );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}

Adapter *
BeginAdapterList
( AdapterList * list )
{
  if( list == NULL || list->list == NULL )
    return NULL;
  
  return BeginList( list->list );
}

AdapterList *
CopyAdapterList
( AdapterList * list )
{
  if( list == NULL )
    return NULL;
  
  AdapterList * copy = malloc( sizeof( AdapterList ) );
  if( copy == NULL )
    return NULL;
  
  copy->list = CopyList( list->list );
  
  return copy;
}

void
DestroyAdapterList
( AdapterList * list )
{
  DestroyList( list->list );
  
  free( list );
  
  return;
}

unsigned short
AdapterListIsEmpty
( AdapterList * list )
{
  return list == NULL || ListIsEmpty( list->list );
}

AdapterList *
NewAdapterList
( void )
{
  AdapterList * list = malloc( sizeof( AdapterList ) );
  if( list == NULL )
    return NULL;
  
  list->list = NewList();
  if( list->list == NULL )
    return NULL;
  
  return list;
}

Adapter *
NextInAdapterList
( AdapterList * list )
{
  if( list == NULL || list->list == NULL )
    return NULL;
  
  return NextInList( list->list );
}

Status *
PrependToAdapterList
( AdapterList * list, Adapter * adapter )
{
  if( list == NULL || adapter == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = PrependToList( list->list, adapter );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}

Entry *
ValueThroughAdapterList
( AdapterList * list, Value * value )
{
  return NULL;
}
