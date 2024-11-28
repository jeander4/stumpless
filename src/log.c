// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2022 Joel E. Anderson
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
#include <stdlib.h>
#include <string.h>

#include <stumpless/log.h>
#include "private/memory.h"
#include <stumpless/target.h>
#include <stumpless/version.h>

#include "private/target.h"

#ifdef _WIN32
#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
#else
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif

int
stump( const char *message, ... ) {
  int result;
  va_list subs;

  va_start( subs, message );
  result = vstump( message, subs );
  va_end( subs );

  return result;
}

int
stump_str( const char *message ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return -1;
  }

  return stumpless_add_message_str( target, message );
}

int
stump_trace( const char *file,
             int line,
             const char *func,
             const char *message, ... ) {
  int result;
  va_list subs;

  va_start( subs, message );
  result = vstump_trace( file, line, func, message, subs );
  va_end( subs );

  return result;
}

int
stump_trace_str( const char *file,
                 int line,
                 const char *func,
                 const char *message ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return -1;
  }

  return stumpless_trace_message_str( target, file, line, func, message );
}

void
stumplog( int priority, const char *message, ... ) {
  va_list subs;

  va_start( subs, message );
  vstumplog( priority, message, subs );
  va_end( subs );
}

int
stumplog_set_mask( int mask ) {
  struct stumpless_target *target;
  int old_mask;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return 0;
  }

  lock_target( target );
  old_mask = target->mask;
  target->mask = mask;
  unlock_target( target );

  return old_mask;
}

void
stumplog_str( int priority, const char *message ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return;
  }

  stumpless_add_log_str( target, priority, message );
}

void
stumplog_trace( int priority,
                const char *file,
                int line,
                const char *func,
                const char *message, ... ) {
  va_list subs;

  va_start( subs, message );
  vstumplog_trace( priority, file, line, func, message, subs );
  va_end( subs );
}

void
stumplog_trace_str( int priority,
                    const char *file,
                    int line,
                    const char *func,
                    const char *message ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return;
  }

  stumpless_trace_log_str( target, priority, file, line, func, message );
}

int
vstump( const char *message, va_list subs ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return -1;
  }

  return vstumpless_add_message( target, message, subs );
}

int
vstump_trace( const char *file,
              int line,
              const char *func,
              const char *message,
              va_list subs ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return -1;
  }

  return vstumpless_trace_message( target, file, line, func, message, subs );
}

void
vstumplog( int priority, const char *message, va_list subs ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return;
  }

  vstumpless_add_log( target, priority, message, subs );
}

void
vstumplog_trace( int priority,
                 const char * file,
                 int line,
                 const char *func,
                 const char *message,
                 va_list subs ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return;
  }

  vstumpless_trace_log( target, priority, file, line, func, message, subs );
}


char** get_ip_addresses() {
  char **ip_addresses = NULL;
  int ip_addresses_counter = 0;
  char ip[INET6_ADDRSTRLEN];

  #ifdef _WIN32
    WSADATA wsaData;
    if ( WSAStartup( MAKEWORD(2, 2), &wsaData ) != 0 ) {
        perror( "WSAStartup failed" );
        return NULL;
    }

    // Get the list of network interfaces
    ULONG size = 0;
    GetAdaptersAddresses( AF_UNSPEC, 0, NULL, NULL, &size );
    IP_ADAPTER_ADDRESSES *adapterAddresses = (IP_ADAPTER_ADDRESSES *)malloc( size );
    if ( !adapterAddresses ) {
      WSACleanup(); // Cleanup before returning
      return NULL;
    }
      if ( GetAdaptersAddresses( AF_UNSPEC, 0, NULL, adapterAddresses, &size ) == NO_ERROR ) {
        IP_ADAPTER_ADDRESSES *adapter = adapterAddresses;
        while ( adapter ) {
          IP_ADAPTER_UNICAST_ADDRESS *unicast = adapter->FirstUnicastAddress;
          while ( unicast ) {
            if ( unicast->Address.lpSockaddr->sa_family == AF_INET ) {
              struct sockaddr_in *sockaddr_in = (struct sockaddr_in *)unicast->Address.lpSockaddr;
              inet_ntop(AF_INET, &sockaddr_in->sin_addr, ip, sizeof(ip));

              char **temp = realloc( ip_addresses, ( ip_addresses_counter + 1 ) * sizeof(char*) );
              if (!temp) {
                // Reallocation failed, cleanup
                free( adapterAddresses );
                WSACleanup();
                for ( int i = 0; i < ip_addresses_counter; i++ ) {
                  free(ip_addresses[i]);
                }
                free(ip_addresses);
                return NULL;
              }
              ip_addresses = temp;
              ip_addresses[ip_addresses_counter++] = strdup( ip );

            } else if ( unicast->Address.lpSockaddr->sa_family == AF_INET6 ) {
              struct sockaddr_in6 *sockaddr_in6 = (struct sockaddr_in6 *)unicast->Address.lpSockaddr;
              inet_ntop( AF_INET6, &sockaddr_in6->sin6_addr, ip, sizeof( ip ) );

              char **temp = realloc( ip_addresses, ( ip_addresses_counter + 1 ) * sizeof(char*) );
              if ( !temp ) {
                // Reallocation failed, cleanup
                free( adapterAddresses );
                WSACleanup();
                for ( int i = 0; i < ip_addresses_counter; i++ ) {
                  free( ip_addresses[i] );
                }
                free( ip_addresses );
                return NULL;
              }
              ip_addresses = temp;
              ip_addresses[ip_addresses_counter++] = strdup(ip);
            }
            unicast = unicast->Next;
          }
          adapter = adapter->Next;
        }
      }
    free( adapterAddresses );
    WSACleanup();
  #else
    struct ifaddrs *ifaddr, *ifa;

    // Get the list of network interfaces
    if ( getifaddrs( &ifaddr ) == -1 ) {
        perror( "getifaddrs" );
        return NULL;
    }

    // Loop through all the interfaces
    for ( ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next ) {
      if ( ifa->ifa_addr == NULL )
        continue;

      if ( ifa->ifa_addr->sa_family == AF_INET ) {  // IPv4
        struct sockaddr_in *addr = (struct sockaddr_in *)ifa->ifa_addr;
        inet_ntop( AF_INET, &addr->sin_addr, ip, sizeof( ip ) );
        char **temp = realloc( ip_addresses, ( ip_addresses_counter + 1 ) * sizeof(char*) );
        if (!temp) {
          perror("realloc failed");
          freeifaddrs(ifaddr);
          for ( int i = 0; i < ip_addresses_counter; i++ ) {
            free( ip_addresses[i] );
          }
          free( ip_addresses );
          return NULL;
        }
        ip_addresses = temp;
        ip_addresses[ip_addresses_counter++] = strdup( ip );

      } else if ( ifa->ifa_addr->sa_family == AF_INET6 ) {  // IPv6
        struct sockaddr_in6 *addr = (struct sockaddr_in6 *)ifa->ifa_addr;
        inet_ntop( AF_INET6, &addr->sin6_addr, ip, sizeof( ip ) );
        char **temp = realloc( ip_addresses, ( ip_addresses_counter + 1 ) * sizeof( char* ) );
        if ( !temp ) {
          perror( "realloc failed" );
          freeifaddrs( ifaddr );
          for ( int i = 0; i < ip_addresses_counter; i++ ) {
            free( ip_addresses[i] );
          }
          free( ip_addresses );
          return NULL;
        }
        ip_addresses = temp;
        ip_addresses[ip_addresses_counter++] = strdup( ip );
      }
    }

    // Free the memory allocated by getifaddrs
    freeifaddrs(ifaddr);
  #endif

  // Add a NULL terminator to mark the end of the array
  ip_addresses = realloc( ip_addresses, ( ip_addresses_counter + 1 ) * sizeof( char* ) );
  if ( ip_addresses ) {
    ip_addresses[ip_addresses_counter] = NULL;
  }

  return ip_addresses;
}


struct stumpless_element* get_origin_struct_instance( void ) {
  char** ip_addressess = get_ip_addresses();
  int ip_addresses_counter = 0;

  struct stumpless_version* version = stumpless_get_version();

  struct stumpless_element *origin_element = alloc_mem( sizeof( *origin_element ) );
  stumpless_set_element_name( origin_element, "origin structure" );
  stumpless_add_new_param( origin_element, "software", "stumpless" );
  stumpless_add_new_param( origin_element, "swVersion", stumpless_version_to_string( version ) ) ;

  if ( ip_addressess[ ip_addresses_counter ] != NULL ) {
    stumpless_add_new_param( origin_element, "ip", ip_addressess[ ip_addresses_counter ] );

    while ( ip_addressess[ ip_addresses_counter ] != NULL ) {
      free( ip_addressess[ ip_addresses_counter ] );
      ip_addresses_counter++;
    }
    free( ip_addressess );
  }
}
