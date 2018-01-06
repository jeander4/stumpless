/*
 * Copyright 2018, Joel Anderson.
 * All Rights Reserved.
 *
 * This file is part of Stumpless.
 * 
 * Stumpless is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 * 
 * Stumpless is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * Stumpless.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stddef.h>
#include <stumpless/version.h>
#include "private/error.h"
#include "private/memory.h"

struct stumpless_version *
get_stumpless_version(){
  struct stumpless_version *version;

  clear_error();

  version = alloc_mem(sizeof(struct stumpless_version));
  if(!version){
    return NULL;
  }

  version->major = STUMPLESS_MAJOR_VERSION;
  version->minor = STUMPLESS_MINOR_VERSION;
  version->patch = STUMPLESS_PATCH_VERSION;

  return version;
}
