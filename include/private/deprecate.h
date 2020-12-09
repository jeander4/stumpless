/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_DEPRECATE_H
#  define __STUMPLESS_PRIVATE_DEPRECATE_H

#  include <stumpless/config.h>

#  ifdef STUMPLESS_DEPRECATION_WARNINGS_ENABLED
#    include <stdio.h>
#    define warn_of_deprecation( WARNING ) printf( "DEPRECATED: " WARNING "\n" )
#  else
#    define warn_of_deprecation( WARNING ) ( ( void ) 0 )
#  endif

#endif /* __STUMPLESS_PRIVATE_DEPRECATE_H */
