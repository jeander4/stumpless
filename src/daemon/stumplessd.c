/*
 * Copyright 2017, Joel Anderson.
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include "stumpless.h"

static int log_socket=0;
static FILE *outfile=NULL;

void sigint_handler(int signo){
  fclose(outfile);
  close(log_socket);
  unlink(STUMPLESS_SOCKET_NAME);
  
  exit(EXIT_SUCCESS);
}

int main(void){
  struct sockaddr_un log_socket_addr;
  struct sockaddr_un from_addr;
  ssize_t msg_len;
  socklen_t size = 100;
  char buf[1024];
  
  outfile = fopen("stumplessd-out.log", "a");
  if( !outfile ){
    perror("could not open output file");
    return EXIT_FAILURE;
  }

  log_socket_addr.sun_family = AF_UNIX;
  memcpy(&log_socket_addr.sun_path, STUMPLESS_SOCKET_NAME, STUMPLESS_SOCKET_NAME_LENGTH+1);

  if(signal(SIGINT, &sigint_handler) == SIG_ERR){
    perror("could not register signal handler for SIGINT");
    return EXIT_FAILURE;
  }
  
  log_socket = socket(log_socket_addr.sun_family, SOCK_DGRAM, 0);
  if(log_socket < 0){
    perror("could not create socket");
    return EXIT_FAILURE;
  }

  if( bind(log_socket, (struct sockaddr *) &log_socket_addr, sizeof(log_socket_addr.sun_family)+STUMPLESS_SOCKET_NAME_LENGTH+1) < 0 ){
    perror("could not bind socket");
    return EXIT_FAILURE;
  }

  while(1){
    msg_len = recvfrom(log_socket, buf, 1024, 0, (struct sockaddr *) &from_addr, &size);
    if(msg_len < 0){
      perror("message recieve failure");
    } else {
      fprintf(outfile, "%s\n", buf);
      fflush(outfile);
    }
  }

  // this should never be hit
  return EXIT_FAILURE;
}
