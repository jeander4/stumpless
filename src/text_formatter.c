#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <text_formatter.h>
#include <value_list.h>

static
StumplessFormattedOutput *
GetTextFormattedOutput( void ){
  StumplessFormattedOutput * output;
  StumplessFormattedPayload * payload;

  output = malloc( sizeof( StumplessFormattedOutput ) );
  if( output == NULL )
    return NULL;
  
  payload = malloc( sizeof( StumplessFormattedPayload ) );
  if( payload == NULL )
    return NULL;
  
  payload->values = StumplessNewValueList();
  if( payload->values == NULL )
    return NULL;
  
  output->format = STUMPLESS_TEXT;
  output->payload = payload;
  
  return output;
}

StumplessFormattedOutput *
StumplessEntryAsText( StumplessEntry * entry )
{
  if( entry == NULL )
    return NULL;
  
  // todo need to make this method encompass more possible cases
  return NULL;
}

StumplessFormattedOutput *
StumplessEventAsText( StumplessEvent * event )
{
  if( event == NULL )
    return NULL;
  
  StumplessFormattedOutput * output = GetTextFormattedOutput();
  if( output == NULL )
    return NULL;
   
  char * str;
  
  // todo use the eventwithoutattributes method to build this one
  
  if( event->name == NULL ){
    if( event->level == NULL ){
      if( event->attribute_count == 0 ){
        str = "";
      } else {
        // todo
      }
    } else {

    }
  } else {
    if( event->level == NULL ){
      if( event->attribute_count == 0 ){

      } else {

      }
    } else {

    }
    
  }
  
  //output->payload->str = str;
  
  return output;
}

StumplessFormattedOutput *
StumplessEventAsTextWithoutAttributes( StumplessEvent * event )
{
  if( event == NULL )
    return NULL;
  
  StumplessFormattedOutput * output = GetTextFormattedOutput();
  if( output == NULL )
    return NULL;
  
  char * str;
  
  if( event->name == NULL ){
    if( event->level == NULL ){
      str = "";
    } else {
      StumplessFormattedOutput * level = StumplessLevelAsText( event->level );
      if( level == NULL )
        return NULL;
      //char * level_string = level->payload->str;
      char * level_string = "testing";
      
      size_t level_length = strlen( level_string );
      size_t str_length = level_length + 7;
      str = malloc( sizeof( char ) * str_length );
      if( str == NULL )
        return NULL;
      
      sprintf( str, "%s event", level_string );
    }
  } else {
    size_t name_length = strlen( event->name );
    
    if( event->level == NULL ){
      size_t str_length = name_length + 1;
      str = malloc( sizeof( char ) * str_length );
      if( str == NULL )
        return NULL;
      
      sprintf( str, "%s", event->name );
    } else {
      StumplessFormattedOutput * level = StumplessLevelAsText( event->level );
      if( level == NULL )
        return NULL;
      //char * level_string = level->payload->str;
      char * level_string = "testing";
      
      size_t level_length = strlen( level_string );
      size_t str_length = name_length + level_length + 4;
      str = malloc( sizeof( char ) * str_length );
      if( str == NULL )
        return NULL;
      
      sprintf( str, "%s (%s)", event->name, level_string );
    }
  }
  
  //output->payload->str = str;
  
  return output;
}

StumplessFormattedOutput *
StumplessEventAttributeAsText( StumplessEventAttribute * attribute )
{
  // todo need to implement
  return NULL;
}

StumplessFormattedOutput *
StumplessEventAttributeAsTextShortened( StumplessEventAttribute * attribute )
{
  if( attribute == NULL )
    return NULL;
  
  // todo will need eventattributevalue as text method
  
  return NULL;
}

StumplessFormattedOutput *
StumplessEventAttributeListAsText( StumplessEvent * event )
{
  if( event == NULL )
    return NULL;
  
  
  return NULL;
}

StumplessFormattedOutput *
StumplessLevelAsText( StumplessLevel * level )
{
  if( level == NULL )
    return NULL;
 
  StumplessFormattedOutput * output = GetTextFormattedOutput();
  if( output == NULL )
    return NULL;
  
  /*if( level->name == NULL ){
    size_t str_length = number_length + 7;
    str = malloc( sizeof( char ) * str_length );
    if( str == NULL )
      return NULL;

    sprintf( str, "level %d", level->value);
  } else {
    size_t name_length = strlen( level->name );
    size_t str_length = number_length + name_length + 9;
    str = malloc( sizeof( char ) * str_length );
    if( str == NULL )
      return NULL;

    sprintf( str, "%s: level %d", level->name, level->value );
  }*/
  
  return output;
}

StumplessFormattedOutput *
StumplessValueAsText( StumplessValue * value )
{
  if( value == NULL )
    return NULL;
  
  StumplessFormattedOutput * output = GetTextFormattedOutput();
  if( output == NULL )
    return NULL;
  
  StumplessValueList * list = output->payload->values;
  StumplessStatusCode status = StumplessAppendToValueList( list, value );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  // todo finish implementing
  
  return output;
}
