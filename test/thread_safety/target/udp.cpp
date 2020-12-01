// SPDX-License-Identifier: Apache-2.0

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

#include "test/helper/server.hpp"

#include <cstddef>
#include <cstdlib>
#include <gtest/gtest.h>
#include <stumpless.h>
#include <thread>
#include "test/helper/assert.hpp"
#include "test/helper/usage.hpp"

namespace {
  const int THREAD_COUNT = 16;
  const int MESSAGE_COUNT = 50;

  void
  read_network_target( const struct stumpless_target *target, bool is_udp ) {
    const char *destination;
    const char *port;

    for( size_t i = 0; i < MESSAGE_COUNT; i++ ) {
      destination = stumpless_get_destination( target );
      EXPECT_NO_ERROR;
      port = stumpless_get_transport_port( target );
      EXPECT_NO_ERROR;
      stumpless_target_is_open( target );
      EXPECT_NO_ERROR;

      if( is_udp ) {
        stumpless_get_udp_max_message_size( target );
        EXPECT_NO_ERROR;
      }

      free( ( void * ) destination );
      free( ( void * ) port );
    }

    stumpless_free_thread(  );
  }

  void
  write_network_target( struct stumpless_target *target,
                        const char *destination,
                        bool is_udp ) {
    for( size_t i = 0; i < MESSAGE_COUNT; i++ ) {
      stumpless_set_destination( target, destination );
      EXPECT_NO_ERROR;
      stumpless_set_transport_port( target,
                                    STUMPLESS_DEFAULT_TRANSPORT_PORT );
      EXPECT_NO_ERROR;

      if( is_udp) {
        stumpless_set_udp_max_message_size( target, 3200 );
        EXPECT_NO_ERROR;
      }
    }

    stumpless_free_thread(  );
  }

  void
  run_network_target_tests( struct stumpless_target *target,
                            const char *destination,
                            bool fixture_enabled,
                            bool is_udp ) {
    size_t i;
    std::thread *threads[THREAD_COUNT*3];

    for( i = 0; i < THREAD_COUNT; i++ ) {
      if( fixture_enabled ) {
        threads[i] = new std::thread( add_messages, target, MESSAGE_COUNT );
      }

      threads[THREAD_COUNT + i] = new std::thread( read_network_target,
                                                   target,
                                                   is_udp );
      threads[THREAD_COUNT*2 + i] = new std::thread( write_network_target,
                                                     target,
                                                     destination,
                                                     is_udp );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      if( fixture_enabled ) {
        threads[i]->join(  );
        delete threads[i];
      }

      threads[THREAD_COUNT + i]->join(  );
      delete threads[THREAD_COUNT + i];
      threads[THREAD_COUNT*2 + i]->join(  );
      delete threads[THREAD_COUNT*2 + i];
    }
  }

  void
  receive_from_client( socket_handle_t client_handle ) {
    char buffer[1024];

    while( recv_from_handle( client_handle, buffer, 1024 ) ){
    };

    close_server_socket( client_handle );
  }

  void
  listen_on_socket( socket_handle_t server_handle ) {
    socket_handle_t local_handle;
    std::vector<std::thread *> threads;

    while( true ) {
      local_handle = accept_tcp_connection( server_handle );
      if( local_handle == -1 ) {
        break;
      }

      threads.push_back(new std::thread(receive_from_client, local_handle));
    }

    for(auto it = threads.begin(); it != threads.end(); it++){
      (*it)->join();
      delete (*it);
    }
  }

  TEST( Tcp4WriteConsistency, SimultaneousWrites ) {
    struct stumpless_target *target;
    socket_handle_t handle;
    const char *target_destination = "127.0.0.1";
    std::thread *listener_thread;

    // setting up to receive the sent messages
    handle = open_tcp4_server_socket( target_destination,
                                      STUMPLESS_DEFAULT_TRANSPORT_PORT );
    if( handle == BAD_HANDLE ) {
      std::cout << errno;
      std::cout << "WARNING: " BINDING_DISABLED_WARNING << std::endl;

    } else {
      listener_thread = new std::thread( listen_on_socket, handle );

      // set up the target to log to
      target = stumpless_open_tcp4_target( "test-target",
                                           target_destination,
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
      EXPECT_NO_ERROR;
      ASSERT_NOT_NULL( target );

      // run the tests
      run_network_target_tests( target,
                                target_destination,
                                true,
                                false );

      // cleanup after the test
      stumpless_close_network_target( target );
      EXPECT_NO_ERROR;
      stumpless_free_all(  );

      close_server_socket( handle );
    }
  }

  TEST( Udp4WriteConsistency, SimultaneousWrites ) {
    bool udp_fixtures_enabled = true;
    struct stumpless_target *target;
    socket_handle_t handle;
    const char *target_destination = "127.0.0.1";

    // setting up to receive the sent messages
    handle = open_udp4_server_socket( target_destination,
                                      STUMPLESS_DEFAULT_TRANSPORT_PORT );
    if( handle == BAD_HANDLE ) {
      std::cout << "WARNING: " BINDING_DISABLED_WARNING << std::endl;
      udp_fixtures_enabled = false;
    }

    // set up the target to log to
    target = stumpless_open_udp4_target( "test-target",
                                         target_destination,
                                         STUMPLESS_OPTION_NONE,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    // run the tests
    run_network_target_tests( target,
                              target_destination,
                              udp_fixtures_enabled,
                              true );

    // cleanup after the test
    stumpless_close_network_target( target );
    EXPECT_NO_ERROR;
    stumpless_free_all(  );

    close_server_socket( handle );
  }

  TEST( Udp6WriteConsistency, SimultaneousWrites ) {
    bool udp_fixtures_enabled = true;
    struct stumpless_target *target;
    socket_handle_t handle;
    const char *target_destination = "::1";

    // setting up to receive the sent messages
    handle = open_udp6_server_socket( target_destination,
                                      STUMPLESS_DEFAULT_TRANSPORT_PORT );
    if( handle == BAD_HANDLE ) {
      std::cout << "WARNING: " BINDING_DISABLED_WARNING << std::endl;
      udp_fixtures_enabled = false;
    }

    // set up the target to log to
    target = stumpless_open_udp6_target( "test-target",
                                         target_destination,
                                         STUMPLESS_OPTION_NONE,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    // run the tests
    run_network_target_tests( target,
                              target_destination,
                              udp_fixtures_enabled,
                              true );

    // cleanup after the test
    stumpless_close_network_target( target );
    EXPECT_NO_ERROR;
    stumpless_free_all(  );

    close_server_socket( handle );
  }
}
