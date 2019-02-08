#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_NUM 1024

void main(int argc, char **argv){
  int fd;
  unsigned int *addr;
  unsigned int offset, data;
  long page_size, map_size;

  if(argc < 2){
    printf("Usage: %s ADDRESS(hex) DATA(hex)\n", argv[0]);
    return;
  }

  fd = open( "/dev/mem", O_RDWR );
  if( fd == -1 ){
    printf( "Can't open /dev/mem.\n" );
    return;
  }

  page_size = getpagesize();
  map_size  = page_size * PAGE_NUM;

  offset = strtoul( argv[1], NULL, 16 );
  data   = strtoul( argv[2], NULL, 16 );

  // Assign memory map
  addr = mmap( NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset & 0xFFFF0000);
  if( addr == MAP_FAILED ){
    printf( "Error: mmap()\n" );
    return;
  }

  // Write
  addr[(offset & 0x0000FFFC) / 4] = data;

  // Read
//  printf( "%08X: %08X\n", ( offset & 0xFFFFFFFC ), ( addr[(offset & 0x0000FFFC) /4] ) );

  // Free
  munmap(addr, map_size);
  close(fd);

  return;
}

