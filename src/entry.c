// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2020 Joel E. Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <stumpless/element.h>
#include <stumpless/entry.h>
#include <stumpless/param.h>
#include <stumpless/error.h>
#include "private/cache.h"
#include "private/config/wrapper.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/facility.h"
#include "private/formatter.h"
#include "private/severity.h"
#include "private/strbuilder.h"
#include "private/strhelper.h"
#include "private/memory.h"

static struct cache *entry_cache = NULL;

struct stumpless_entry *
stumpless_add_element( struct stumpless_entry *entry,
                       struct stumpless_element *element ) {
  size_t i;
  struct stumpless_element **new_elements;
  size_t old_elements_size;
  size_t new_elements_size;

  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return NULL;
  }

  if( !element ) {
    raise_argument_empty( "element is NULL" );
    return NULL;
  }

  for( i = 0; i < entry->element_count; i++ ) {
    if( strcmp( entry->elements[0]->name, element->name ) == 0 ) {
      raise_duplicate_element(  );
      return NULL;
    }
  }

  old_elements_size = sizeof( element ) * entry->element_count;
  new_elements_size = old_elements_size + sizeof( element );

  new_elements = realloc_mem( entry->elements, new_elements_size );
  if( !new_elements ) {
    return NULL;
  }

  new_elements[entry->element_count] = element;
  entry->elements = new_elements;
  entry->element_count++;

  clear_error(  );
  return entry;
}

struct stumpless_entry *
stumpless_add_new_element( struct stumpless_entry *entry,
                           const char *name ) {
  struct stumpless_element *new_element;

  new_element = stumpless_new_element( name );
  if( !new_element ) {
    return NULL;
  }

  return stumpless_add_element( entry, new_element );
}

struct stumpless_entry *
stumpless_add_new_param_to_entry( struct stumpless_entry *entry,
                                  const char *element_name,
                                  const char *param_name,
                                  const char *param_value ) {
  return NULL;
}

struct stumpless_entry *
stumpless_copy_entry( const struct stumpless_entry *entry ) {
  return NULL;
}

void
stumpless_destroy_entry( const struct stumpless_entry *entry ) {
  stumpless_destroy_entry_and_contents( entry );
}

void
stumpless_destroy_entry_and_contents( const struct stumpless_entry *entry ) {
  size_t i;

  if( !entry ) {
    return;
  }

  for( i = 0; i < entry->element_count; i++ ) {
    stumpless_destroy_element( entry->elements[i] );
  }

  unchecked_destroy_entry( entry );
}

void
stumpless_destroy_entry_only( const struct stumpless_entry *entry ) {
  if( !entry ) {
    return;
  }

  unchecked_destroy_entry( entry );
}

struct stumpless_element *
stumpless_get_element_by_index( struct stumpless_entry *entry,
                                size_t index ) {
  clear_error(  );

  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return NULL;
  }

  if( index >= entry->element_count ) {
    raise_index_out_of_bounds( "invalid element index", index );
    return NULL;
  }

  clear_error(  );
  return entry->elements[index];
}

struct stumpless_element *
stumpless_get_element_by_name( struct stumpless_entry *entry,
                               const char *name ) {
  size_t index;

  index = stumpless_get_element_index( entry, name );

  if( stumpless_has_error(  ) ) {
    return NULL;
  }

  return entry->elements[index];
}

size_t
stumpless_get_element_index( struct stumpless_entry *entry,
                             const char *name ) {
  size_t i;

  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return 0;
  }

  if( !name ) {
    raise_argument_empty( "name is NULL" );
    return 0;
  }

  for( i = 0; i < entry->element_count; i++ ) {
    if( strcmp( entry->elements[i]->name, name ) == 0 ) {
      clear_error(  );
      return i;
    }
  }

  raise_element_not_found(  );
  return 0;
}

const char *
stumpless_get_entry_app_name( const struct stumpless_entry *entry ) {
  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return NULL;
  }

  clear_error(  );
  return entry->app_name;
}

int
stumpless_get_entry_facility( const struct stumpless_entry *entry ) {
  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return -1;
  }

  clear_error(  );
  return get_facility( entry->prival );
}

const char *
stumpless_get_entry_msgid( const struct stumpless_entry *entry ) {
  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return NULL;
  }

  clear_error(  );
  return entry->msgid;
}

int
stumpless_get_entry_prival( const struct stumpless_entry *entry ) {
  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return -1;
  }

  clear_error(  );
  return entry->prival;
}

int
stumpless_get_entry_severity( const struct stumpless_entry *entry ) {
  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return -1;
  }

  clear_error(  );
  return get_severity( entry->prival );
}

struct stumpless_param *
stumpless_get_param_by_index_from_entry( struct stumpless_entry *entry,
                                         size_t element_index,
                                         size_t param_index ) {
  return NULL;
}

struct stumpless_param *
stumpless_get_param_by_name_from_entry( struct stumpless_entry *entry,
                                        const char *element_name,
                                        const char *param_name ) {
  return NULL;
}

const char *
stumpless_get_param_value_by_index_from_entry( struct stumpless_entry *entry,
                                               size_t element_index,
                                               size_t param_index ) {
  return NULL;
}

const char *
stumpless_get_param_value_by_name_from_entry( struct stumpless_entry *entry,
                                              const char *element_name,
                                              const char *param_name ) {
  return NULL;
}

struct stumpless_entry *
stumpless_new_entry( int facility,
                     int severity,
                     const char *app_name,
                     const char *msgid,
                     const char *message,
                     ... ) {
  va_list subs;
  struct stumpless_entry *entry;

  va_start( subs, message );
  entry = vstumpless_new_entry( facility,
                                severity,
                                app_name,
                                msgid,
                                message,
                                subs );
  va_end( subs );

  return entry;
}

struct stumpless_entry *
stumpless_set_entry_app_name( struct stumpless_entry *entry,
                              const char *app_name ) {
  const char * effective_name;
  size_t temp_name_length;
  char *temp_name;

  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return NULL;
  }

  effective_name = app_name ? app_name : "-";
  temp_name = copy_cstring_with_length( effective_name, &temp_name_length );
  if( !temp_name ) {
    return NULL;
  }

  free_mem( entry->app_name );
  entry->app_name = temp_name;
  entry->app_name_length = temp_name_length;

  clear_error(  );
  return entry;
}

struct stumpless_entry *
stumpless_set_entry_facility( struct stumpless_entry *entry, int facility ) {
  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return NULL;
  }

  if( facility_is_invalid( facility ) ) {
    raise_invalid_facility( facility );
    return NULL;
  }

  entry->prival = get_prival( facility, get_severity( entry->prival ) );

  clear_error(  );
  return entry;
}

struct stumpless_entry *
stumpless_set_entry_msgid( struct stumpless_entry *entry,
                           const char *msgid ) {
  const char *effective_msgid;
  size_t temp_length;
  char *temp_msgid;

  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return NULL;
  }

  effective_msgid = msgid ? msgid : "-";
  temp_msgid = copy_cstring_with_length( effective_msgid, &temp_length );
  if( !temp_msgid ) {
    return NULL;
  }

  free_mem( entry->msgid );
  entry->msgid = temp_msgid;
  entry->msgid_length = temp_length;

  clear_error(  );
  return entry;
}

struct stumpless_entry *
stumpless_set_entry_message( struct stumpless_entry *entry,
                             const char *message,
                             ... ) {
  va_list subs;
  struct stumpless_entry *result;

  va_start( subs, message );
  result = vstumpless_set_entry_message( entry, message, subs );
  va_end( subs );

  return result;
}

struct stumpless_entry *
stumpless_set_entry_priority( struct stumpless_entry *entry,
                              int facility,
                              int severity ) {
  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return NULL;
  }

  if( facility_is_invalid( facility ) ) {
    raise_invalid_facility( facility );
    return NULL;
  }

  if( severity_is_invalid( severity ) ) {
    raise_invalid_severity( severity );
    return NULL;
  }

  entry->prival = get_prival( facility, severity );

  clear_error(  );
  return entry;
}

struct stumpless_entry *
stumpless_set_entry_prival( struct stumpless_entry *entry,
                            int prival ) {
  return stumpless_set_entry_priority( entry,
                                       get_facility( prival ),
                                       get_severity( prival ) );
}

struct stumpless_entry *
stumpless_set_entry_severity( struct stumpless_entry *entry, int severity ) {
  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return NULL;
  }

  if( severity_is_invalid( severity ) ) {
    raise_invalid_severity( severity );
    return NULL;
  }

  entry->prival = get_prival( get_facility( entry->prival ), severity );

  clear_error(  );
  return entry;
}

struct stumpless_entry *
stumpless_set_element( struct stumpless_entry *entry,
                       size_t index,
                       struct stumpless_element *element ) {
  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return NULL;
  }

  if( !element ) {
    raise_argument_empty( "element is NULL" );
    return NULL;
  }

  if( index >= entry->element_count ) {
    raise_index_out_of_bounds( "invalid element index", index );
    return NULL;
  }

  // todo catch duplicate element case

  entry->elements[index] = element;

  clear_error(  );
  return entry;
}

struct stumpless_entry *
stumpless_set_param_by_index_from_entry( struct stumpless_entry *entry,
                                         size_t element_index,
                                         size_t param_index,
                                         struct stumpless_param *param ) {
  return NULL;
}

struct stumpless_entry *
stumpless_set_param_value_by_index_from_entry( struct stumpless_entry *entry,
                                               size_t element_index,
                                               size_t param_index,
                                               const char *param_value ) {
  return NULL;
}

struct stumpless_entry *
stumpless_set_param_value_by_name_from_entry( struct stumpless_entry *entry,
                                              const char *element_name,
                                              const char *param_name,
                                              const char *param_value ) {
  return NULL;
}

struct stumpless_entry *
vstumpless_new_entry( int facility,
                      int severity,
                      const char *app_name,
                      const char *msgid,
                      const char *message,
                      va_list subs ) {
  struct stumpless_entry *entry;
  const char *effective_app_name;
  size_t *app_name_length;
  const char *effective_msgid;
  size_t *msgid_length;
  size_t *message_length;

  clear_error(  );

  if( !entry_cache ) {
    entry_cache = cache_new( sizeof( *entry ), NULL, NULL );

    if( !entry_cache ) {
      goto fail;
    }
  }

  entry = cache_alloc( entry_cache );
  if( !entry ) {
    goto fail;
  }

  effective_app_name = app_name ? app_name : "-";
  app_name_length = &( entry->app_name_length );
  entry->app_name = copy_cstring_with_length( effective_app_name,
                                              app_name_length );
  if( !entry->app_name ) {
    goto fail_app_name;
  }

  effective_msgid = msgid ? msgid : "-";
  msgid_length = &( entry->msgid_length );
  entry->msgid = copy_cstring_with_length( effective_msgid, msgid_length );
  if( !entry->msgid ) {
    goto fail_msgid;
  }

  if( !message ) {
    entry->message = NULL;
    entry->message_length = 0;
  } else {
    message_length = &( entry->message_length );
    entry->message = config_format_string( message, subs, message_length );
    if( !entry->message ) {
      goto fail_message;
    }
  }

  config_initialize_insertion_params( entry );
  config_set_entry_wel_type( entry, severity );

  entry->prival = get_prival( facility, severity );
  entry->elements = NULL;
  entry->element_count = 0;

  return entry;

fail_message:
  free_mem( entry->msgid );
fail_msgid:
  free_mem( entry->app_name );
fail_app_name:
  cache_free( entry_cache, entry );
fail:
  return NULL;
}

struct stumpless_entry *
vstumpless_set_entry_message( struct stumpless_entry *entry,
                              const char *message,
                              va_list subs ) {
  char *formatted_message;
  size_t message_length;

  clear_error(  );

  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return NULL;
  }

  if( !message ) {
    free_mem( entry->message );
    entry->message = NULL;
    entry->message_length = 0;

  } else {
    formatted_message = config_format_string( message, subs, &message_length );
    if( !formatted_message ) {
      return NULL;

    } else {
      free_mem( entry->message );
      entry->message = formatted_message;
      entry->message_length = message_length;

    }
  }

  return entry;
}

/* private functions */

void
entry_free_all( void ) {
  cache_destroy( entry_cache );
  entry_cache = NULL;
}

int
get_prival( int facility, int severity ) {
  return facility | severity;
}

struct strbuilder *
strbuilder_append_app_name( struct strbuilder *builder,
                            const struct stumpless_entry *entry ) {
  return strbuilder_append_buffer( builder,
                                   entry->app_name, entry->app_name_length );
}

struct strbuilder *
strbuilder_append_hostname( struct strbuilder *builder ) {
  char buffer[RFC_5424_MAX_HOSTNAME_LENGTH + 1];

  config_gethostname( buffer, RFC_5424_MAX_HOSTNAME_LENGTH + 1 );

  return strbuilder_append_string( builder, buffer );
}

struct strbuilder *
strbuilder_append_msgid( struct strbuilder *builder,
                         const struct stumpless_entry *entry ) {
  return strbuilder_append_buffer( builder, entry->msgid, entry->msgid_length );
}

struct strbuilder *
strbuilder_append_message( struct strbuilder *builder,
                           const struct stumpless_entry *entry ) {
  return strbuilder_append_buffer( builder,
                                   entry->message, entry->message_length );
}

struct strbuilder *
strbuilder_append_procid( struct strbuilder *builder ) {
  return strbuilder_append_int( builder, config_getpid(  ) );
}

struct strbuilder *
strbuilder_append_structured_data( struct strbuilder *builder,
                                   const struct stumpless_entry *entry ) {
  size_t i;
  size_t j;
  struct stumpless_element *element;
  struct stumpless_param *param;

  if( entry->element_count == 0 ) {
    return strbuilder_append_char( builder, '-' );
  }

  for( i = 0; i < entry->element_count; i++ ) {
    element = entry->elements[i];

    builder = strbuilder_append_char( builder, '[' );
    builder = strbuilder_append_buffer( builder,
                                        element->name, element->name_length );

    for( j = 0; j < entry->elements[i]->param_count; j++ ) {
      param = element->params[j];

      builder = strbuilder_append_char( builder, ' ' );

      builder = strbuilder_append_buffer( builder,
                                          param->name, param->name_length );

      builder = strbuilder_append_char( builder, '=' );
      builder = strbuilder_append_char( builder, '"' );

      builder = strbuilder_append_buffer( builder,
                                          param->value, param->value_length );

      builder = strbuilder_append_char( builder, '"' );
    }

    builder = strbuilder_append_char( builder, ']' );
  }

  return builder;
}

void
unchecked_destroy_entry( const struct stumpless_entry *entry ) {
  config_destroy_insertion_params( entry );

  free_mem( entry->elements );
  free_mem( entry->msgid );
  free_mem( entry->app_name );
  free_mem( entry->message );

  cache_free( entry_cache, entry );
}
