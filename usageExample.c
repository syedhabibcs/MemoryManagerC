#include "ObjectManager.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
  char *ptr;
  int i;
  Ref id1,id2,id3;
  
  // initialize pool
  initPool();

  // create object  
  id1= insertObject(100);
  printf("id1 = %lu\n", id1);
  
  // get object
  ptr = (char*)retrieveObject(id1);
  
  // write values to object
  for (i = 0; i < 100; i++)
    ptr[i] = (char)(i%26 + 'A');
  
  // insert another object
  id2 = insertObject(4000);
  // insert another object
  id3 = insertObject(20200);
  // drop reference as assignment id3 another ojbect
  dropReference(id3);
  // insert another object
  id3 = insertObject(10);
  
  // get object
  ptr = (char*)retrieveObject(id1);
  for (i = 0; i < 100; i++)
    fprintf(stderr,"%c",ptr[i]);
  fprintf(stderr,"\n");
  
  dumpPool();
  destroyPool();
  fprintf(stderr,"---\n");
  
  return 0;
}

