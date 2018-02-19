/*
 * poll_example.cpp
 *
 *  Created on: 11.02.2018
 *      Author: Martin Kaul <martin@familie-kaul.de>
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/poll.h>

int main(int argc, char *argv[])
{
  int fd;
  if( argc < 2 )
  {
    printf( "usage: %s <trigger file>\n", argv[0] );
    return 1;
  }

  fd = open( argv[1], O_RDONLY );
  if( fd < 0 )
  {
    printf( "cannot open trigger file: %s\n", argv[1] );
    return 1;
  }

  for( ;; )
  {
    char buf[2];

    struct pollfd fds;
    fds.fd = fd;
    fds.events = POLLPRI | POLLERR;
    fds.revents = 0;

    pread( fds.fd, buf, sizeof(buf), 0 ); //  dummy reads before the poll() call
    printf( "wait for trigger...\n" );
    int res = poll( &fds, 1, -1 );

    if( res > 0 )
    {
      if( fds.revents & POLLPRI )
      {
        const int n = pread( fds.fd, buf, sizeof(buf), 0 );
        if( n == 2 )
        {
          printf ("...trigger received\n");
        }
      }
    }
  }

  return 0;
}

