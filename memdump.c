#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define MAP_LENG 0x00100000

int main(int argc, char **argv){
  int fd, i;
  unsigned int *addr;
  unsigned int offset, count;
  unsigned int ret;

  fd = open( "/dev/mem", O_RDWR | O_SYNC );
  if( fd == -1 ){
    printf( "Can't open /dev/mem.\n" );
    return 0;
  }

  offset = strtol( argv[1], NULL, 16 );
  count = strtol( argv[2], NULL, 10 );

  addr = mmap( NULL, MAP_LENG, 
               PROT_READ | PROT_WRITE,
			   MAP_SHARED, fd, 
			   offset & 0xFFFF0000);
  if( addr == MAP_FAILED ){
    printf( "Error: mmap()\n" );
    return 0;
  }

  printf( "usage: memdump ADRS(hex) LEN(dec)\n" );

  for( i = 0; i < count; i++ ){
    printf( "%08X: %08X\n",
            ( (offset & 0xFFFFFFFC) + (i * 4) ),
            ( addr[((offset & 0x0000FFFC) /4 ) + i] ) );
    ret = ( addr[((offset & 0x0000FFFC) /4 ) + i] );
  }
  printf( "\n" );

  return ret;
}

