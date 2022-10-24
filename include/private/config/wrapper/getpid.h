/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2022 Joel E. Anderson
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


#ifndef __STUMPLESS_PRIVATE_CONFIG_WRAPPER_GETPID_H
#  define __STUMPLESS_PRIVATE_CONFIG_WRAPPER_GETPID_H

#  include "private/config.h"

/* definition of config_getpid */
#  ifdef HAVE_UNISTD_H
#    include "private/config/have_unistd.h"
#    define config_getpid unistd_getpid
#  elif HAVE_WINDOWS_H
#    include "private/config/have_windows.h"
#    define config_getpid windows_getpid
#  else
#    include "private/config/fallback.h"
#    define config_getpid fallback_getpid
#  endif

#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_GETPID_H */
