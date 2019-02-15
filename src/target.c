// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2019 Joel E. Anderson
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
#include <stumpless/entry.h>
#include <stumpless/target.h>
#include "private/config/wrapper.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/formatter.h"
#include "private/memory.h"
#include "private/strbuilder.h"
#include "private/strhelper.h"
#include "private/target.h"
#include "private/target/buffer.h"
#include "private/target/file.h"
#include "private/target/stream.h"

static struct stumpless_target *current_target = NULL;
static struct stumpless_entry *cached_entry = NULL;

int
stumpless( const char *message, ... ) {
  int result;
  va_list subs;

  va_start( subs, message );
  result = vstumpless( message, subs );
  va_end( subs );

  return result;
}

int
stumpless_add_entry( struct stumpless_target *target,
                     struct stumpless_entry *entry ) {
  struct strbuilder *builder;
  size_t builder_length;
  const char *buffer;
  int result;

  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return -1;
  }

  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return -1;
  }

  if( !target->id ) {
    raise_invalid_id(  );
    return -1;
  }

  // windows targets are not formatted in code
  // instead their formatting comes from message text files
  if( target->type == STUMPLESS_WINDOWS_EVENT_LOG_TARGET ) {
    return config_send_entry_to_wel_target( target->id, entry );
  }

  builder = format_entry( entry );
  if( !builder ) {
    return -1;
  }

  buffer = strbuilder_get_buffer( builder, &builder_length );

  switch ( target->type ) {

    case STUMPLESS_BUFFER_TARGET:
      result = sendto_buffer_target( target->id, buffer, builder_length );
      break;

    case STUMPLESS_FILE_TARGET:
      result = sendto_file_target( target->id, buffer, builder_length );
      break;

    case STUMPLESS_NETWORK_TARGET:
      result = config_sendto_network_target( target->id,
                                             buffer,
                                             builder_length );
      break;

    case STUMPLESS_SOCKET_TARGET:
      result = config_sendto_socket_target( target->id,
                                            buffer,
                                            builder_length );
      break;

    case STUMPLESS_STREAM_TARGET:
      result = sendto_stream_target( target->id, buffer, builder_length );
      break;

    default:
      result = sendto_unsupported_target( target, buffer, builder_length );
  }

  strbuilder_destroy( builder );
  return result;
}

int
stumpless_add_message( struct stumpless_target *target,
                       const char *message,
                       ... ) {
  int result;
  va_list subs;

  va_start( subs, message );
  result = vstumpless_add_message( target, message, subs );
  va_end( subs );

  return result;
}

struct stumpless_target *
stumpless_get_current_target( void ) {
  clear_error(  );

  return current_target;
}

int
stumpless_get_default_facility( const struct stumpless_target *target ) {
  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return -1;
  }

  return get_facility( target->default_prival );
}

int
stumpless_get_option( const struct stumpless_target *target, int option ) {
  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return 0;
  }

  return target->options & option;
}

struct stumpless_target *
stumpless_open_target( struct stumpless_target *target ) {
  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return NULL;
  }

  if( target->type == STUMPLESS_NETWORK_TARGET ) {
    return config_open_network_target( target );

  } else {
    raise_target_incompatible( "this target type cannot be paused" );
    return NULL;

  }
}

void
stumpless_set_current_target( struct stumpless_target *target ) {
  current_target = target;
}

struct stumpless_target *
stumpless_set_default_facility( struct stumpless_target *target,
                                int default_facility ) {
  int old_severity;

  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    goto fail;
  }

  if( facility_is_invalid( default_facility ) ) {
    raise_invalid_facility(  );
    goto fail;
  }

  old_severity = get_severity( target->default_prival );
  target->default_prival = default_facility + old_severity;
  return target;

fail:
  return NULL;
}

struct stumpless_target *
stumpless_set_option( struct stumpless_target *target, int option ) {
  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return NULL;
  }

  target->options |= option;

  return target;
}

struct stumpless_target *
stumpless_set_target_default_app_name( struct stumpless_target *target,
                                       const char *app_name ) {
  size_t *app_name_length;
  char *sized_name;

  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return NULL;
  }

  if( !app_name ) {
    raise_argument_empty( "app_name is NULL" );
    return NULL;
  }

  app_name_length = &( target->default_app_name_length );
  sized_name = cstring_to_sized_string( app_name, app_name_length );
  if( !sized_name ) {
    return NULL;

  } else {
    target->default_app_name = sized_name;
    return target;

  }
}

struct stumpless_target *
stumpless_set_target_default_msgid( struct stumpless_target *target,
                                    const char *msgid ) {
  size_t *msgid_length;
  char *sized_msgid;

  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return NULL;
  }

  if( !msgid ) {
    raise_argument_empty( "msgid is NULL" );
    return NULL;
  }

  msgid_length = &( target->default_msgid_length );
  sized_msgid = cstring_to_sized_string( msgid, msgid_length );
  if( !sized_msgid ) {
    return NULL;

  } else {
    target->default_msgid = sized_msgid;
    return target;

  }
}

const struct stumpless_target *
stumpless_target_is_open( const struct stumpless_target *target ) {
  int is_open;

  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return NULL;
  }

  if( target->type == STUMPLESS_NETWORK_TARGET ) {
    is_open = config_network_target_is_open( target );

  } else {
    is_open = 1;

  }

  if( is_open ) {
    return target;

  } else {
    return NULL;

  }
}

struct stumpless_target *
stumpless_unset_option( struct stumpless_target *target, int option ) {
  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return NULL;
  }

  target->options &= ~option;

  return target;
}

int
vstumpless( const char *message, va_list subs ) {
  struct stumpless_target *target;

  clear_error(  );

  target = stumpless_get_current_target(  );
  if( !target ) {
    return -1;
  }

  return vstumpless_add_message( target, message, subs );
}

int
vstumpless_add_message( struct stumpless_target *target,
                        const char *message,
                        va_list subs ) {
  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return -1;
  }

  if( !cached_entry ) {
    cached_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                        STUMPLESS_SEVERITY_INFO,
                                        "-",
                                        "-",
                                        message );
    if( !cached_entry ) {
      return -1;
    }

  } else {
    stumpless_set_entry_message( cached_entry, message );

  }

  cached_entry->prival = target->default_prival;

  if( target->default_app_name ) {
    cached_entry->app_name = alloc_mem( target->default_app_name_length );
    if( !cached_entry->app_name ) {
      return -1;
    }

    memcpy( cached_entry->app_name, target->default_app_name,
            target->default_app_name_length );
    cached_entry->app_name_length = target->default_app_name_length;
  }

  if( target->default_msgid ) {
    cached_entry->msgid = alloc_mem( target->default_msgid_length );
    if( !cached_entry->msgid ) {
      return -1;
    }

    memcpy( cached_entry->msgid, target->default_msgid,
            target->default_msgid_length );
    cached_entry->msgid_length = target->default_msgid_length;
  }

  return stumpless_add_entry( target, cached_entry );
}

/* private definitions */

void
destroy_target( struct stumpless_target *target ) {
  free_mem( target->default_app_name );
  free_mem( target->default_msgid );
  free_mem( target->name );
  free_mem( target );
}

struct stumpless_target *
new_target( enum stumpless_target_type type,
            const char *name,
            size_t name_len,
            int options,
            int default_facility ) {
  struct stumpless_target *target;
  int default_prival;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  target->name = alloc_mem( name_len + 1 );
  if( !target->name ) {
    goto fail_name;
  }

  memcpy( target->name, name, name_len );
  target->name[name_len] = '\0';
  target->type = type;
  target->options = options;
  default_prival = get_prival( default_facility, STUMPLESS_SEVERITY_INFO );
  target->default_prival = default_prival;
  target->default_app_name = NULL;
  target->default_app_name_length = 0;
  target->default_msgid = NULL;
  target->default_msgid_length = 0;

  return target;

fail_name:
  free_mem( target );
fail:
  return NULL;
}

struct stumpless_target *
open_unsupported_target( struct stumpless_target *target ) {
  ( void ) target;

  raise_target_unsupported( "tried to open an unsupported target type" );
  return NULL;
}

int
send_entry_to_unsupported_target( const struct stumpless_target *target,
                                  const struct stumpless_entry *entry ) {
  ( void ) target;
  ( void ) entry;

  raise_target_unsupported( "attempted to send an entry to an unsupported target type" );
  return -1;
}

int
sendto_unsupported_target( const struct stumpless_target *target,
                           const char *msg,
                           size_t msg_length ) {
  ( void ) target;
  ( void ) msg;
  ( void ) msg_length;

  raise_target_unsupported( "attempted to send a message to an unsupported target type" );
  return -1;
}

int
unsupported_target_is_open( const struct stumpless_target *target ) {
  ( void ) target;

  raise_target_unsupported( "checked to see if an unsupported target type was empty" );
  return 0;
}
