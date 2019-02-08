// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019 Joel E. Anderson
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

#include "private/config/wrapper.h"

#include <stddef.h>
#include <string.h>
#include <stumpless/target.h>
#include <stumpless/target/network.h>
#include "private/config/wrapper.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/strhelper.h"
#include "private/target.h"
#include "private/target/network.h"

static
void
destroy_ipv4_target( struct network_target *target ) {

  if( target->transport == STUMPLESS_TCP_TRANSPORT_PROTOCOL ) {
    config_close_tcp4_target( target );

  } else { // STUMPLESS_UDP_TRANSPORT_PROTOCOL
    config_close_udp4_target( target );

  }
}

static
void
destroy_ipv6_target( struct network_target *target ) {

  if( target->transport == STUMPLESS_TCP_TRANSPORT_PROTOCOL ) {
    config_close_tcp6_target( target );

  } else { // STUMPLESS_UDP_TRANSPORT_PROTOCOL
    config_close_udp6_target( target );

  }
}

static
struct network_target *
init_ipv4_target( struct network_target *target ) {

  switch( target->transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      config_init_tcp4( target );
      return target;

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      config_init_udp4( target );
      return target;

    default:
      raise_transport_protocol_unsupported(  );
      return NULL;

  }
}

static
struct network_target *
init_ipv6_target( struct network_target *target ) {

  switch( target->transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      config_init_tcp6( target );
      return target;

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      config_init_udp6( target );
      return target;

    default:
      raise_transport_protocol_unsupported(  );
      return NULL;

  }
}

static
struct network_target *
init_network_target( struct network_target *target ) {

  switch( target->network ) {

    case STUMPLESS_IPV4_NETWORK_PROTOCOL:
      return init_ipv4_target( target );

    case STUMPLESS_IPV6_NETWORK_PROTOCOL:
      return init_ipv6_target( target );

    default:
      raise_network_protocol_unsupported(  );
      return NULL;

  }
}

static
int
ipv4_target_is_open( const struct network_target *target ) {

  if( target->transport == STUMPLESS_TCP_TRANSPORT_PROTOCOL ) {
      return config_tcp4_is_open( target );

  } else { // STUMPLESS_UDP_TRANSPORT_PROTOCOL
      return config_udp4_is_open( target );

  }
}

static
int
ipv6_target_is_open( const struct network_target *target ) {

  if( target->transport == STUMPLESS_TCP_TRANSPORT_PROTOCOL ) {
      return config_tcp6_is_open( target );

  } else { // STUMPLESS_UDP_TRANSPORT_PROTOCOL
      return config_udp6_is_open( target );

  }
}

static
void *
open_ipv4_target( struct network_target *target ) {

  switch( target->transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      return config_open_tcp4_target( target );

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      return config_open_udp4_target( target );

    default:
      raise_transport_protocol_unsupported(  );
      return NULL;

    }
}

static
void *
open_ipv6_target( struct network_target *target ) {

  switch( target->transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      return config_open_tcp6_target( target );

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      return config_open_udp6_target( target );

    default:
      raise_transport_protocol_unsupported(  );
      return NULL;

    }
}

static
void *
reopen_ipv4_target( struct network_target *target ) {

  if( target->transport == STUMPLESS_TCP_TRANSPORT_PROTOCOL ) {
      return config_reopen_tcp4_target( target );

  } else { // STUMPLESS_UDP_TRANSPORT_PROTOCOL
      return config_reopen_udp4_target( target );

  }
}

static
void *
reopen_ipv6_target( struct network_target *target ) {

  if( target->transport == STUMPLESS_TCP_TRANSPORT_PROTOCOL ) {
      return config_reopen_tcp6_target( target );

  } else { // STUMPLESS_UDP_TRANSPORT_PROTOCOL
      return config_reopen_udp6_target( target );

  }
}

static
void *
reopen_network_target( struct network_target *target ) {

  if( target->network == STUMPLESS_IPV4_NETWORK_PROTOCOL ) {
      return reopen_ipv4_target( target );

  } else { // STUMPLESS_IPV6_NETWORK_PROTOCOL
      return reopen_ipv6_target( target );

  }
}

/* public definitions */

void
stumpless_close_network_target( struct stumpless_target *target ) {
  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return;
  }

  destroy_network_target( target->id );
  destroy_target( target );
}

const char *
stumpless_get_destination( const struct stumpless_target *target ) {
  struct network_target *net_target;

  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    goto fail;
  }

  if( target->type != STUMPLESS_NETWORK_TARGET ) {
    raise_target_incompatible( "destination is only valid for network"
                               " targets" );
    goto fail;
  }

  net_target = target->id;
  return net_target->destination;

fail:
  return NULL;
}

const char *
stumpless_get_transport_port( const struct stumpless_target *target ) {
  struct network_target *net_target;

  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    goto fail;
  }

  if( target->type != STUMPLESS_NETWORK_TARGET ) {
    raise_target_incompatible( "transport port is only valid for network"
                               " targets" );
    goto fail;
  }

  net_target = target->id;
  return net_target->port;

fail:
  return NULL;
}

size_t
stumpless_get_udp_max_message_size( struct stumpless_target *target ) {
  struct network_target *net_target;

  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    goto fail;
  }

  if( target->type != STUMPLESS_NETWORK_TARGET ) {
    raise_target_incompatible( "max message size is only valid for network"
                               " targets" );
    goto fail;
  }

  net_target = target->id;
  if( net_target->transport != STUMPLESS_UDP_TRANSPORT_PROTOCOL ) {
    raise_target_incompatible( "max message size is only valid for UDP targets" );
    goto fail;
  }

  return net_target->max_msg_size;

fail:
  return 0;
}

struct stumpless_target *
stumpless_new_network_target( const char *name,
                              enum stumpless_network_protocol network,
                              enum stumpless_transport_protocol transport ) {
  struct stumpless_target *target;

  clear_error(  );

  if( !name ) {
    raise_argument_empty( "name is NULL" );
    goto fail;
  }

  target = new_target( STUMPLESS_NETWORK_TARGET,
                       name,
                       strlen( name ),
                       0,
                       STUMPLESS_FACILITY_USER );
  if( !target ) {
    goto fail;
  }

  target->id = new_network_target( network, transport );
  if( !target->id ) {
    goto fail_id;
  }

  return target;

fail_id:
  destroy_target( target );
fail:
  return NULL;
}

struct stumpless_target *
stumpless_open_network_target( const char *name,
                               const char *destination,
                               enum stumpless_network_protocol network,
                               enum stumpless_transport_protocol transport,
                               int options,
                               int default_facility ) {
  struct stumpless_target *target;

  clear_error(  );

  if( !name ) {
    raise_argument_empty( "name is NULL" );
    goto fail;
  }

  if( !destination ) {
    raise_argument_empty( "destination is NULL" );
    goto fail;
  }

  if( facility_is_invalid( default_facility ) ) {
    raise_invalid_facility(  );
    goto fail;
  }

  target = new_target( STUMPLESS_NETWORK_TARGET,
                       name,
                       strlen( name ),
                       options,
                       default_facility );

  if( !target ) {
    goto fail;
  }

  target->id = open_network_target( destination, network, transport );
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

struct stumpless_target *
stumpless_open_tcp4_target( const char *name,
                            const char *destination,
                            int options,
                            int default_facility ) {

  return stumpless_open_network_target( name,
                                        destination,
                                        STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                        STUMPLESS_TCP_TRANSPORT_PROTOCOL,
                                        options,
                                        default_facility );

}

struct stumpless_target *
stumpless_open_tcp6_target( const char *name,
                            const char *destination,
                            int options,
                            int default_facility ) {

  return stumpless_open_network_target( name,
                                        destination,
                                        STUMPLESS_IPV6_NETWORK_PROTOCOL,
                                        STUMPLESS_TCP_TRANSPORT_PROTOCOL,
                                        options,
                                        default_facility );

}

struct stumpless_target *
stumpless_open_udp4_target( const char *name,
                            const char *destination,
                            int options,
                            int default_facility ) {

  return stumpless_open_network_target( name,
                                        destination,
                                        STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                        STUMPLESS_UDP_TRANSPORT_PROTOCOL,
                                        options,
                                        default_facility );

}

struct stumpless_target *
stumpless_open_udp6_target( const char *name,
                            const char *destination,
                            int options,
                            int default_facility ) {

  return stumpless_open_network_target( name,
                                        destination,
                                        STUMPLESS_IPV6_NETWORK_PROTOCOL,
                                        STUMPLESS_UDP_TRANSPORT_PROTOCOL,
                                        options,
                                        default_facility );

}

struct stumpless_target *
stumpless_set_destination( struct stumpless_target *target,
                           const char *destination ) {
  const char *destination_copy;
  struct network_target *net_target;
  void *result;

  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    goto fail;
  }

  if( !destination ) {
    raise_argument_empty( "destination is NULL" );
    goto fail;
  }

  if( target->type != STUMPLESS_NETWORK_TARGET ) {
    raise_target_incompatible( "transport port is only valid for network"
                               " targets" );
    goto fail;
  }

  destination_copy = copy_cstring( destination );
  if( !destination_copy ) {
    goto fail;
  }

  net_target = target->id;

  free_mem( ( void * ) net_target->destination );
  net_target->destination = destination_copy;

  result = reopen_network_target( net_target );
  if( !result ) {
    goto fail;
  }

  return target;

fail:
  return NULL;
}

struct stumpless_target *
stumpless_set_transport_port( struct stumpless_target *target,
                              const char *port ) {
  struct network_target *net_target;
  const char *port_copy;
  void *result;

  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    goto fail;
  }

  if( !port ) {
    raise_argument_empty( "port is NULL" );
    goto fail;
  }

  if( target->type != STUMPLESS_NETWORK_TARGET ) {
    raise_target_incompatible( "transport port is only valid for network"
                               " targets" );
    goto fail;
  }

  port_copy = copy_cstring( port );
  if( !port_copy ) {
    goto fail;
  }

  net_target = target->id;

  free_mem( ( void * ) net_target->port );
  net_target->port = port_copy;

  result = reopen_network_target( net_target );
  if( !result ) {
    goto fail;
  }

  return target;

fail:
  return NULL;
}

struct stumpless_target *
stumpless_set_udp_max_message_size( struct stumpless_target *target,
                                    size_t max_msg_size ) {
  struct network_target *net_target;

  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    goto fail;
  }

  if( target->type != STUMPLESS_NETWORK_TARGET ) {
    raise_target_incompatible( "max message size is only valid for network"
                               " targets" );
    goto fail;
  }

  net_target = target->id;
  if( net_target->transport != STUMPLESS_UDP_TRANSPORT_PROTOCOL ) {
    raise_target_incompatible( "max message size is only valid for UDP targets" );
    goto fail;
  }

  net_target = target->id;
  net_target->max_msg_size = max_msg_size;

  return target;

fail:
  return NULL;
}

/* private definitions */

void
destroy_network_target( struct network_target *target ) {

  if( target->network == STUMPLESS_IPV4_NETWORK_PROTOCOL ) {
    destroy_ipv4_target( target );

  } else } // STUMPLESS_IPV6_NETWORK_PROTOCOL
    destroy_ipv6_target( target );

  }

  free_mem( ( void * ) target->destination );
  free_mem( ( void * ) target->port );
  free_mem( target );
}

int
network_target_is_open( const struct stumpless_target *target ) {
  const struct network_target *net_target;

  net_target = ( const struct network_target * ) target->id;

  if( net_target->network == STUMPLESS_IPV4_NETWORK_PROTOCOL ) {
    return ipv4_target_is_open( net_target );

  } else { // STUMPLESS_IPV6_NETWORK_PROTOCOL
    return ipv6_target_is_open( net_target );

  }
}

struct network_target *
new_network_target( enum stumpless_network_protocol network,
                    enum stumpless_transport_protocol transport ) {
  struct network_target *target;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  target->destination = NULL;
  target->port = NULL;
  target->network = network;
  target->transport = transport;

  return init_network_target( target );

fail:
  return NULL;
}

struct network_target *
open_network_target( const char *destination,
                     enum stumpless_network_protocol network,
                     enum stumpless_transport_protocol transport ) {
  struct network_target *target;
  const char *destination_copy;
  const char *port_copy;
  void *result;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  destination_copy = copy_cstring( destination );
  if( !destination_copy ) {
    goto fail_destination;
  }

  port_copy = copy_cstring( DEFAULT_PORT );
  if( !port_copy ) {
    goto fail_port;
  }

  target->network = network;
  target->transport = transport;
  target->max_msg_size = STUMPLESS_DEFAULT_UDP_MAX_MESSAGE_SIZE;
  target->destination = destination_copy;
  target->port = port_copy;

  switch( network ) {

    case STUMPLESS_IPV4_NETWORK_PROTOCOL:
      result = open_ipv4_target( target );
      break;

    case STUMPLESS_IPV6_NETWORK_PROTOCOL:
      result = open_ipv6_target( target );
      break;

    default:
      raise_network_protocol_unsupported(  );
      goto fail_protocol;

  }

  if( !result ) {
    goto fail_protocol;
  }

  return target;

fail_protocol:
  free_mem( ( void * ) port_copy );
fail_port:
  free_mem( ( void * ) destination_copy );
fail_destination:
  free_mem( target );
fail:
  return NULL;
}

int
sendto_network_target( struct network_target *target,
                       const char *msg,
                       size_t msg_length ) {
  size_t effective_length;

  if( target->transport == STUMPLESS_UDP_TRANSPORT_PROTOCOL ) {

    if( msg_length > target->max_msg_size ) {
      effective_length = target->max_msg_size;
      raise_argument_too_big( "message is too large to be sent in a single datagram",
                              cap_size_t_to_int( msg_length ),
                              "size of the message that is too large" );
    } else {
      effective_length = msg_length;
    }

    if( target->network == STUMPLESS_IPV4_NETWORK_PROTOCOL ) {
      return config_sendto_udp4_target( target, msg, effective_length );
    } else {
      return config_sendto_udp6_target( target, msg, effective_length );
    }

  } else {

    if( target->network == STUMPLESS_IPV4_NETWORK_PROTOCOL ) {
      return config_sendto_tcp4_target( target, msg, msg_length );
    } else {
      return config_sendto_tcp6_target( target, msg, msg_length );
    }

  }
}
