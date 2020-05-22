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

#include <stddef.h>
#include <stumpless/param.h>
#include "private/error.h"
#include "private/memory.h"
#include "private/strhelper.h"

void
stumpless_destroy_param( struct stumpless_param *param );

void
stumpless_destroy_param( struct stumpless_param *param ) {
  clear_error(  );

  if( !param ) {
    return;
  }

  free_mem( param->name );
  free_mem( param->value );
  free_mem( param );
}

const char *
stumpless_get_param_name( const struct stumpless_param *param ) {
  return NULL;
}

const char *
stumpless_get_param_value( const struct stumpless_param *param ) {
  return NULL;
}

struct stumpless_param *
stumpless_new_param( const char *name, const char *value ) {
  struct stumpless_param *param;

  clear_error(  );

  if( !name ) {
    raise_argument_empty( "name is NULL" );
    goto fail;
  }

  if( !value ) {
    raise_argument_empty( "value is NULL" );
    goto fail;
  }

  param = alloc_mem( sizeof( *param ) );
  if( !param ) {
    goto fail;
  }

  param->name = cstring_to_sized_string( name, &( param->name_length ) );
  if( !param->name ) {
    goto fail_name;
  }

  param->value = cstring_to_sized_string( value, &( param->value_length ) );
  if( !param->value ) {
    goto fail_value;
  }

  return param;

fail_value:
  free_mem( param->name );

fail_name:
  free_mem( param );

fail:
  return NULL;
}

struct stumpless_param *
stumpless_set_param_name( struct stumpless_param *param, const char *name ) {
  return NULL;
}

struct stumpless_param *
stumpless_set_param_value( struct stumpless_param *param, const char *value ) {
  return NULL;
}
