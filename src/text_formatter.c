#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "private/output.h"
#include "private/output_profile.h"
#include "private/status_checker.h"
#include "private/text_formatter.h"
#include "private/text_formatter_static.h"
#include "private/type.h"
#include "private/value.h"
#include "private/value_constructor.h"
#include "private/value_list.h"

Output *
ArrayValueToText
( Value * value )
{
  ValueList * output = ArrayValueToValueList( value );
  return TextOutputFromValueList( output );
}

Output *
EntryToText
( Entry * entry )
{
  return TextOutputFromValueList( EntryToValueList( entry ) );
}

Output *
EntryAttributeToText
( EntryAttribute * attribute )
{
  ValueList * output = EntryAttributeToValueList( attribute );
  return TextOutputFromValueList( output );
}

Output *
EntryAttributeListToText
( Entry * entry )
{
  ValueList * output = EntryAttributeListToValueList( entry );
  return TextOutputFromValueList( output );
}

Output *
EntrySummaryToText
( Entry * entry )
{
  return TextOutputFromValueList( EntrySummaryToValueList( entry ) );
}

Output *
EventToText
( Event * event )
{
  return TextOutputFromValueList( EventToValueList( event ) );
}

Output *
EventAttributeToText
( EventAttribute * attribute )
{
  ValueList * output = EventAttributeToValueList( attribute );
  return TextOutputFromValueList( output );
}

Output *
EventAttributeListToText
( Event * event )
{
  ValueList * output = EventAttributeListToValueList( event );
  return TextOutputFromValueList( output );
}

Output *
EventSummaryToText
( Event * event )
{
  return TextOutputFromValueList( EventSummaryToValueList( event ) );
}

Output *
LevelToText
( Level * level )
{
  return TextOutputFromValueList( LevelToValueList( level ) );
}

Output *
SingularValueToText
( Value * value )
{
  ValueList * output = SingularValueToValueList( value );
  return TextOutputFromValueList( output );
}

static
ValueList *
ArrayValueToValueList
( Value * value )
{
  if( value == NULL )
    return NULL;
  
  ValueProfile * profile = value->profile;
  if( profile == NULL )
    return NULL;
  
  ValueList * output = profile->to_value_list( value );
  if( output == NULL )
    return NULL;
  
  Value * separator = ValueFromString( ", " );
  NULL_ON_FAILURE( AddSeparatorToValueList( output, separator ) )

  NULL_ON_FAILURE( PrependStringToValueList( output, "[" ) )
  NULL_ON_FAILURE( AppendStringToValueList( output, "] (" ) )
  
  NULL_ON_FAILURE( AppendStringToValueList( output, profile->name ) )
  
  NULL_ON_FAILURE( AppendStringToValueList( output, ")" ) )
  
  return output;
}

static
ValueList *
EntryToValueList
( Entry * entry )
{
  if( entry == NULL )
    return NULL;
  
  ValueList * output = EntrySummaryToValueList( entry );
  if( output == NULL )
    return NULL;
  
  if( entry->attributes != NULL && entry->attribute_count > 0 ){
    NULL_ON_FAILURE( AppendStringToValueList( output, ": " ) )
    
    ValueList * attributes = EntryAttributeListToValueList( entry );
    if( attributes == NULL )
      return NULL;
    
    NULL_ON_FAILURE( AppendValueLists( output, attributes ) )
  }
  
  return output;
}

static
ValueList *
EntryAttributeToValueList
( EntryAttribute * attribute )
{
  if( attribute == NULL )
    return NULL;
  
  ValueList * output = NewValueList();
  if( output == NULL )
    return NULL;
  
  EventAttribute * event_attribute = attribute->event_attribute;
  
  const char * attribute_name;
  if( event_attribute == NULL || event_attribute->name == NULL )
    attribute_name = "attribute";
  else
    attribute_name = event_attribute->name;
  
  Status * status;
  NULL_ON_FAILURE( AppendStringToValueList( output, attribute_name ) )
  
  NULL_ON_FAILURE( AppendStringToValueList( output, ": " ) );
  
  Value * attribute_value;
  if( attribute->value != NULL )
    attribute_value = attribute->value;
  else if( event_attribute != NULL && event_attribute->default_value != NULL )
    attribute_value = event_attribute->default_value;
  else
    return NULL;
  
  if( attribute_value->profile == NULL )
    return NULL;
  
  Output * value_as_text;
  value_as_text = attribute_value->profile->to_text( attribute_value );
  if( value_as_text == NULL )
    return NULL;
  
  ValueList * values = ( ValueList * ) value_as_text->data->v_p;
  NULL_ON_FAILURE( AppendValueLists( output, values ) )
  
  return output;
}

static
ValueList *
EntryAttributeListToValueList
( Entry * entry )
{
  if( entry == NULL || entry->attributes == NULL )
    return NULL;
  
  ValueList * output = NewValueList();
  if( output == NULL )
    return NULL;
  
  ValueList * attribute;
  unsigned i;
  for( i = 0; i < entry->attribute_count; i++ ){
    attribute = EntryAttributeToValueList( entry->attributes[i] );
    if( attribute == NULL )
      continue;
    
    if( !ValueListIsEmpty( output ) )
      NULL_ON_FAILURE( AppendStringToValueList( output, ", " ) )
    
    NULL_ON_FAILURE ( AppendValueLists( output, attribute ) )
  }
  
  return output;
}

static
ValueList *
EntrySummaryToValueList
( Entry * entry )
{
  if( entry == NULL )
    return NULL;
  
  ValueList * output = NewValueList();
  if( output == NULL )
    return NULL;
  
  const char * description;
  if( entry->description == NULL )
    description = "entry";
  else
    description = entry->description;
  
  Status * status;
  status = AppendStringToValueList( output, description );
  NULL_ON_FAILURE( status )
  
  ValueList * event;
  if( entry->event != NULL ){
    NULL_ON_FAILURE( AppendStringToValueList( output, " [" ) )
      
    event = EventSummaryToValueList( entry->event );
    if( event == NULL )
      return NULL;
    
    NULL_ON_FAILURE( AppendValueLists( output, event ) )
    
    NULL_ON_FAILURE( AppendStringToValueList( output, "]" ) )
  }
  
  return output;
}

static
ValueList *
EventToValueList
( Event * event )
{
  if( event == NULL )
    return NULL;
  
  ValueList * output = EventSummaryToValueList( event );
  if( output == NULL )
    return NULL;
  
  if( event->attributes != NULL && event->attribute_count > 0 ){
    NULL_ON_FAILURE( AppendStringToValueList( output, ": " ) )
    
    ValueList * attributes = EventAttributeListToValueList( event );
    if( attributes == NULL )
      return NULL;
    
    NULL_ON_FAILURE( AppendValueLists( output, attributes ) )
  }
  
  return output;
}

static
ValueList *
EventAttributeToValueList
( EventAttribute * attribute )
{
  if( attribute == NULL )
    return NULL;
  
  ValueList * output = NewValueList();
  if( output == NULL )
    return NULL;
  
  const char * name;
  if( attribute->name == NULL )
    name = "attribute";
  else
    name = attribute->name;
  NULL_ON_FAILURE( AppendStringToValueList( output, name ) )
  
  Value * default_value = attribute->default_value;
  if( default_value != NULL ){
    NULL_ON_FAILURE( AppendStringToValueList( output, ": " ) )
    
    if( default_value->profile == NULL )
      return NULL;
    
    Output * default_value_output;
    default_value_output = default_value->profile->to_text( default_value );
    
    ValueList * default_value_list;
    default_value_list = ( ValueList * ) default_value_output->data->v_p;
    
    NULL_ON_FAILURE( AppendValueLists( output, default_value_list ) )
  }
  
  return output; 
}

static
ValueList *
EventAttributeListToValueList
( Event * event )
{
  if( event == NULL || event->attributes == NULL )
    return NULL;
  
  ValueList * output = NewValueList();
  if( output == NULL )
    return NULL;
  
  unsigned i;
  ValueList * attribute;
  for( i = 0; i < event->attribute_count; i++ ){
    attribute = EventAttributeToValueList( event->attributes[i] );
    if( attribute == NULL )
      continue;
    
    if( !ValueListIsEmpty( output ) )
      NULL_ON_FAILURE( AppendStringToValueList( output, ", " ) )
    
    NULL_ON_FAILURE( AppendValueLists( output, attribute ) )
  }
  
  return output;
}

static
ValueList *
EventSummaryToValueList
( Event * event )
{
  if( event == NULL )
    return NULL;
  
  ValueList * output = NewValueList();
  if( output == NULL )
    return NULL;
  
  const char * event_name = event->name == NULL ? "event" : event->name;
  Status * status;
  status = AppendStringToValueList( output, event_name );
  NULL_ON_FAILURE( status );
  
  if( event->level != NULL ){
    NULL_ON_FAILURE( AppendStringToValueList( output, " (" ) )
    
    ValueList * level = LevelToValueList( event->level );
    if( level == NULL )
      return NULL;
    
    NULL_ON_FAILURE( AppendValueLists( output, level ) )
    
    NULL_ON_FAILURE( AppendStringToValueList( output, ")" ) )
  }
  
  return output;
}

static
ValueList *
LevelToValueList
( Level * level )
{
  if( level == NULL )
    return NULL;
  
  ValueList * output = NewValueList();
  if( output == NULL )
    return NULL;
  
  Status * status;
  
  if( level->name != NULL ){
    status = AppendStringToValueList( output, level->name );
    NULL_ON_FAILURE( status )
    
    status = AppendStringToValueList( output, ": " );
    NULL_ON_FAILURE( status )
  }
  
  status = AppendStringToValueList( output, "level " );
  NULL_ON_FAILURE( status )
  status = AppendUnsignedIntToValueList( output, level->value );
  NULL_ON_FAILURE( status )
  
  return output;
}

static
ValueList *
SingularValueToValueList
( Value * value )
{
  if( value == NULL )
    return NULL;
  
  ValueProfile * profile;
  profile = value->profile;
  if( profile == NULL )
    return NULL;
  
  ValueList * output = NewValueList();
  if( output == NULL )
    return NULL;
  
  NULL_ON_FAILURE( AppendValueToValueList( output, value ) )
  
  NULL_ON_FAILURE( AppendStringToValueList( output, " (" ) )

  NULL_ON_FAILURE( AppendStringToValueList( output, profile->name ) )
  
  NULL_ON_FAILURE( AppendStringToValueList( output, ")" ) )
  
  return output;
}

static
Output *
TextOutputFromValueList
( ValueList * list )
{
  if( list == NULL )
    return NULL;
  
  Output * output = malloc( sizeof( Output ) );
  if( output == NULL )
    return NULL;
  
  output->data = malloc( sizeof( Type ) );
  if( output->data == NULL )
    return NULL;
  
  output->profile = FindOutputProfileByName( "text" );
  if( output->profile == NULL )
    return NULL;
  
  output->data->v_p = ( void * ) ValueListToStrings( list );
  
  return output;
}
