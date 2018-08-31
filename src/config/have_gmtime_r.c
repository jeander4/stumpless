// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018 Joel E. Anderson
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

#include <time.h>
#include "private/config/have_gmtime_r.h"

int
gmtime_r_get_now( struct tm *now_tm, struct timespec *now_ts ) {
  int gettime_result;
  struct tm *gmtime_result;

  gettime_result = clock_gettime( CLOCK_REALTIME, now_ts );
  if( gettime_result != 0 ) {
    return gettime_result;
  }

  gmtime_result = gmtime_r( &(now_ts->tv_sec), now_tm );
  if( gmtime_result ) {
    return 0;
  } else {
    return -1;
  }
}
