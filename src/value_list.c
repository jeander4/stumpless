#include <stdio.h>
#include <string.h>

#include <configuration.h>
#include <value.h>
#include <value_list.h>
#include <types.h>


static
StumplessStatusCode
AppendValueListNodeToValueList ( StumplessValueList * list,
                                 StumplessValueListNode * node )
{
  if( list == NULL || node == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  node->next = NULL;
  
  if( list->first == NULL ){
    list->first = list->last = node;
  } else {
    list->last->next = node;
    list->last = node;
  }
  
  return STUMPLESS_SUCCESS;
}

static
void
DestroyValueListNode( StumplessValueListNode * node )
{
  if( node == NULL )
    return;
  
  StumplessDestroyValue( node->value );
  
  free( node );
}

StumplessStatusCode
StumplessAppendStringToValueList( StumplessValueList * list, char * str )
{
  if( list == NULL || str == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  StumplessValue * value = StumplessValueFromString( str );
  if( value == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  return StumplessAppendValueToValueList( list, value );
}

StumplessStatusCode
StumplessAppendUnsignedIntToValueList( StumplessValueList * list, unsigned num )
{
  if( list == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  StumplessValue * value = StumplessValueFromUnsignedInt( num );
  if( value == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  else
    return StumplessAppendValueToValueList( list, value );
}

StumplessStatusCode
StumplessAppendValueLists( StumplessValueList * beginning,                                                 StumplessValueList * end )
{
  if( beginning == NULL || end == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  StumplessValueList * copy = StumplessCopyValueList( end );
  if( copy == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  if( beginning->first == NULL )
    beginning->first = copy->first;
  else
    beginning->last->next = copy->first;
  beginning->last = copy->last;
  
  free( copy );
  
  return STUMPLESS_SUCCESS;
}

StumplessStatusCode
StumplessAppendValueToValueList( StumplessValueList * list,
                                 StumplessValue * value )
{
  if( list == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  if( value == NULL )
    return STUMPLESS_SUCCESS;
  
  StumplessValueListNode * node = malloc( sizeof( StumplessValueListNode ) );
  if( node == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  node->value = value;
  
  return AppendValueListNodeToValueList( list, node );
}

StumplessValueList *
StumplessCopyValueList( StumplessValueList * list )
{
  if( list == NULL )
    return NULL;
  
  StumplessValueList * copy = malloc( sizeof( StumplessValueList ) );
  if( copy == NULL )
    return NULL;
  
  copy->first = copy->last =  NULL;
  
  StumplessValueListNode * node = list->first;
  StumplessValueListNode * copied_node;
  StumplessStatusCode status;
  while( node != NULL ){
    copied_node = malloc( sizeof( StumplessValueListNode ) );
    if( copied_node == NULL )
      return NULL;
    
    status = AppendValueListNodeToValueList( copy, copied_node );
    if( status != STUMPLESS_SUCCESS )
      return NULL;
    
    copied_node->value = node->value; 
    
    node = node->next;
  }
  
  return copy;
}

void
StumplessDestroyValueList( StumplessValueList * list )
{
  StumplessValueListNode * prev = NULL;
  StumplessValueListNode * node = list->first;
  
  while( node != NULL ){
    if( prev != NULL ){
      StumplessDestroyValue( prev->value );
      free( prev );
    }
    
    prev = node;
    node = node->next;
  }
  
  free( list );
  
  return;
}

StumplessValueList *
StumplessNewValueList( void )
{
  StumplessValueList * list = malloc( sizeof( StumplessValueList ) );
  if( list == NULL )
    return NULL;
  
  list->first = NULL;
  list->last = NULL;
  
  return list;
}

StumplessStatusCode
StumplessValueListIntoString( char * str, StumplessValueList * list )
{
  if( str == NULL || list == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  StumplessStatusCode status;
  str[0] = '\0';
  
  if( stumpless_configuration == NULL ){
    status = StumplessInitializeConfiguration();
    if( status != STUMPLESS_SUCCESS )
      return status;
  }
  
  size_t buffer_size = stumpless_configuration->string->buffer_size;
  char * buffer = malloc( sizeof( char ) * buffer_size + 1 );
  if( buffer == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  StumplessValueListNode * node = list->first;
  char * value_str;
  while( node != NULL ){
    value_str = StumplessValueToString( node->value );
    if( value_str != NULL )
      strncat( str, value_str, buffer_size );
    node = node->next;
  }
  
  return STUMPLESS_SUCCESS;
}

short
StumplessValueListIsEmpty( StumplessValueList * list )
{
  if( list == NULL )
    return 1;
  else
    return list->first == NULL;
}

char *
StumplessValueListToString( StumplessValueList * list )
{
  StumplessStatusCode status;
  if( stumpless_configuration == NULL ){
    status = StumplessInitializeConfiguration();
    if( status != STUMPLESS_SUCCESS )
      return NULL;
  }
  
  size_t buffer_size = stumpless_configuration->string->buffer_size;
  char * list_str = malloc( sizeof( char ) * buffer_size + 1 );
  
  status = StumplessValueListIntoString( list_str, list );
  
  if( status == STUMPLESS_SUCCESS )
    return list_str;
  else
    return NULL;
}

StumplessStatusCode
StumplessWriteAndDestroyValueList( FILE * stream, StumplessValueList * list )
{
  if( stream == NULL || list == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  StumplessStatusCode status;
  StumplessValueListNode * previous = NULL;
  StumplessValueListNode * current = list->first;
  
  while( current != NULL ){
    status = StumplessWriteValueToStream( stream, current->value );
    if( status != STUMPLESS_SUCCESS )
      return status;
    
    previous = current;
    current = current->next;
    DestroyValueListNode( previous );
  }
  
  free( list );
  return STUMPLESS_SUCCESS;
}

StumplessStatusCode
StumplessWriteValueListToStream( FILE * stream, StumplessValueList * list )
{
  if( stream == NULL || list == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  StumplessStatusCode status;
  StumplessValueListNode * current = list->first;
  
  while( current != NULL ){
    status = StumplessWriteValueToStream( stream, current->value );
    if( status != STUMPLESS_SUCCESS )
      return status;
    
    current = current->next;
  }
  
  return STUMPLESS_SUCCESS;
}
