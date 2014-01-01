#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/list_iterator.h"
#include "private/static/list.h"
#include "private/static/list_iterator.h"
#include "private/type.h"

#include "helper.h"

const char * test_constructor( void );
const char * test_copy( void );
const char * test_destructor( void );
const char * test_has_next( void );
const char * test_next( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( constructor )
  RUN_TEST( copy )
  RUN_TEST( destructor )
  RUN_TEST( has_next )
  RUN_TEST( next )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_constructor
( void )
{
  List * list = NULL;
  ListIterator * iterator = NewListIterator( list );
  FAIL_IF_NOT_NULL( iterator, "a null list returned a non-null iterator" )
  
  list = BuildListOfStrings();
  FAIL_IF_NULL( list, "could not build the test list" )
  iterator = NewListIterator( list );
  FAIL_IF_NULL( iterator, "a non-null list returned a null iterator" )
  
  if( iterator->list != list )
    return "the iterator did not have the appropriate list";
  if( iterator->current != list->first )
    return "the iterator did not start at the beginning of the list";
  
  return NULL;
}

const char *
test_copy
( void )
{
  return NULL;
}

const char *
test_destructor( void )
{
  return NULL;
}

const char *
test_has_next( void )
{
  ListIterator * iterator = NULL;
  
  unsigned short result = ListIteratorHasNext( iterator );
  if( result )
    return "a null iterator had a next value";
  
  iterator = BuildListIterator();
  FAIL_IF_NULL( iterator, "could not build the test iterator" )
  
  while( iterator->current != NULL ){
    if( !ListIteratorHasNext( iterator ) )
      return "an iterator with a remaining value returned false";
    
    NextInListIterator( iterator );
  }
  
  if( ListIteratorHasNext( iterator ) )
    return "a finished iterator returned true";
  
  return NULL;
}

const char *
test_next
( void )
{
  ListIterator * iterator = NULL;
  
  unsigned short result = ListIteratorHasNext( iterator );
  if( result )
    return "a null iterator had a next value";
  
  iterator = BuildListIterator();
  FAIL_IF_NULL( iterator, "could not build the test iterator" )
  
  while( ListIteratorHasNext( iterator ) ){
    Node * next = iterator->current->next;
    
    if( iterator->current->value != NextInListIterator( iterator ) )
      return "next did not return the placeholder value";
    
    if( iterator->current != next )
      return "the iterator placeholder was not advanced";
  }
  
  if( NextInListIterator( iterator ) != NULL )
    return "a finished iterator returned a non-null value";
  
  return NULL;
}
