// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2021 Joel E. Anderson
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

#include <stddef.h>
#include <stumpless/entry.h>
#include <stumpless/target.h>
#include <stumpless/target/function.h>
#include "private/config/locale/wrapper.h"
#include "private/error.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/function.h"
#include "private/validate.h"

void
stumpless_close_function_target( struct stumpless_target *target ) {
  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return;
  }

  destroy_function_target( target->id );
  destroy_target( target );
  clear_error(  );
}

struct stumpless_target *
stumpless_open_function_target( const char *name,
                                stumpless_log_func_t log_function ) {
  struct stumpless_target *target;

  VALIDATE_ARG_NOT_NULL( name );
  VALIDATE_ARG_NOT_NULL( log_function );

  target = new_target( STUMPLESS_FUNCTION_TARGET, name );

  if( !target ) {
    goto fail;
  }

  target->id = new_function_target( log_function );
  if( !target->id ) {
    goto fail_id;
  }

  stumpless_set_current_target( target );
  return target;

fail_id:
  destroy_target( target );
fail:
  return NULL;
}

/* private definitions */

void
destroy_function_target( struct function_target *target ) {
  free_mem( target );
}

struct function_target *
new_function_target( stumpless_log_func_t log_function ) {
  struct function_target *target;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    return NULL;
  }

  target->log_function = log_function;

  return target;
}

int
send_entry_to_function_target( const struct stumpless_target *target,
                               const struct stumpless_entry *entry ) {
  struct function_target *func_target;
  int result;

  func_target = target->id;

  result = func_target->log_function( target, entry );

  if( result < 0 ) {
    raise_function_target_failure( result );
  }

  return result;
}
