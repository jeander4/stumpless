/* SPDX-License-Identifier: Apache-2.0 */

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

#ifndef __STUMPLESS_PRIVATE_TARGET_JOURNALD_H
#  define __STUMPLESS_PRIVATE_TARGET_JOURNALD_H

#  include <stddef.h>
#  include <stumpless/entry.h>
#  include <stumpless/target.h>

/**
 * Gets a journald-compliant field name from a given UTF-8 string.
 *
 * @return the number of bytes written to the flattened buffer.
 */
size_t
get_journald_field_name( char *flattened, const char *raw, size_t size );

void
journald_free_thread( void );

int
send_entry_to_journald_target( const struct stumpless_target *target,
                               const struct stumpless_entry *entry );

#endif /* __STUMPLESS_PRIVATE_TARGET_JOURNALD_H */