#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_NUM 1024

void main(int argc, char **argv){
  int fd, i;
  unsigned int *addr;
  unsigned int offset, count;
  long page_size, map_size;

  if(argc < 2){
    printf("Usage: %s ADDRESS(hex) NUM(dec)\n", argv[0]);
    return;
  }

  fd = open( "/dev/mem", O_RDWR | O_SYNC );
  if( fd == -1 ){
    printf( "Can't open /dev/mem.\n" );
    return;
  }

  offset = strtoul( argv[1], NULL, 16 );
  count  = strtoul( argv[2], NULL, 10 );

  page_size = getpagesize();
  map_size  = page_size * PAGE_NUM;

  // Assign memory map
  addr = mmap( NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset & 0xFFFF0000);
  if( addr == MAP_FAILED ){
    printf( "Error: mmap()\n" );
    return;
  }

  // Read
  for( i = 0; i < count; i++ ){
    printf( "%08X: %08X\n",
            ( (offset & 0xFFFFFFFC) + (i * 4) ),
            ( addr[((offset & 0x0000FFFC) /4 ) + i] ) );
  }

  // Free
  munmap(addr, map_size);
  close(fd);

  return;
}

